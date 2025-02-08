#!/usr/bin/env python3
#
# SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0
#

import os
import sys
import logging

import argparse
import functools

import zigpy.ota

logging.basicConfig(level=logging.DEBUG, format="%(asctime)s - %(name)s - %(levelname)s - %(message)s")
LOGGER = logging.getLogger("OTA_IMAGE")

def create(version, manuf_id, image_type, stack_version, header_string, security_credentials, upgrade_dest, min_hw_ver, max_hw_ver, tag_id, tag_length, tag_file):
	with open(tag_file, "rb") as f:
		data = f.read()

	header=zigpy.ota.image.OTAImageHeader(
			upgrade_file_id=zigpy.ota.image.OTAImageHeader.MAGIC_VALUE,
			header_version=0x0100,
			header_length=0,
			field_control=zigpy.ota.image.FieldControl(0),

			manufacturer_id=manuf_id,
			image_type=image_type,
			file_version=version,

			stack_version=stack_version,
			header_string=header_string[0:32],
			image_size=0,)

	if security_credentials is not None:
		LOGGER.debug("Security Credential Version")
		header.field_control |= zigpy.ota.image.FieldControl.SECURITY_CREDENTIAL_VERSION_PRESENT
		header.security_credential_version = security_credentials

	if upgrade_dest is not None:
		LOGGER.debug("The EUI64 of the device upgrade file destination")
		header.field_control |= zigpy.ota.image.FieldControl.DEVICE_SPECIFIC_FILE_PRESENT
		header.upgrade_file_destination = zigpy.types.EUI64.convert(upgrade_dest)

	if min_hw_ver and max_hw_ver is not None:
		LOGGER.debug("Hardware Versions")
		header.field_control |= zigpy.ota.image.FieldControl.HARDWARE_VERSIONS_PRESENT
		header.minimum_hardware_version = min_hw_ver
		header.maximum_hardware_version = max_hw_ver
	else:
		if min_hw_ver is None:
			LOGGER.debug("Minimum hardware version is missing")
		if max_hw_ver is None:
			LOGGER.debug("Maximum hardware version is missing")

	match tag_id:
		case zigpy.ota.image.ElementTagId.UPGRADE_IMAGE:
			LOGGER.debug("Upgrade Image")
		case x if 0x1<=x<=0x6:
			sys.exit("Unsupported Tag ID")
		case x if 0xf000<=x<0xffff:
			LOGGER.debug("Manufacturer Specific Use")
		case _:
			sys.exit("Reserved Tag ID by Zigbee")

	image = zigpy.ota.image.OTAImage(
		header,
		subelements=[
			zigpy.ota.image.SubElement(
				tag_id=tag_id, data=data,
			)
		],
	)

	image.header.header_length = len(image.header.serialize())
	image.header.image_size = image.header.header_length + len(image.subelements.serialize())
	return image.serialize()

if __name__ == "__main__":
	any_int = functools.wraps(int)(functools.partial(int, base=0))
	parser = argparse.ArgumentParser(description="Create Zigbee OTA file",
		                             epilog="Reads a firmware image file and outputs an OTA file")
	
	parser.add_argument("-c", "--create", type=str, required=True, help="Create OTA file")
	parser.add_argument("-v", "--version", type=any_int, required=True, help="Firmware version")
	parser.add_argument("-m", "--manuf-id", type=any_int, required=True, help="Manufacturer code")
	parser.add_argument("-i", "--image-type", type=any_int, required=True, help="Image type")
	parser.add_argument("-s", "--stack-version", type=any_int, default=2, help="Zigbee stack version (default: 2)")
	parser.add_argument("--header_string", type=str, default="", help="OTA Header string (default: "")")
	parser.add_argument("--security-credentials", type=any_int, help="The security credentials required for this upgrade (optional)")
	parser.add_argument("--upgrade-dest", type=str, help="The EUI64 of the device the file is intended for (optional)")
	parser.add_argument("--min-hw-ver", type=any_int, help="Minimum hardware version (optional)")
	parser.add_argument("--max-hw-ver", type=any_int, help="Maximum hardware version (optional)")

	parser.add_argument("-t", "--tag-id", type=any_int, default=0, help="Tag identifier (default: 0)")
	parser.add_argument("-l", "--tag-length", type=any_int, help="Length of dummy data for tag (optional)")
	parser.add_argument("-f", "--tag-file", type=str, required=True, help="File to include or extract as data with associated tag")

	args = parser.parse_args()
	output = args.create
	del args.create

	data = create(**vars(args))
	with open(output, "wb") as f:
		f.write(data)
