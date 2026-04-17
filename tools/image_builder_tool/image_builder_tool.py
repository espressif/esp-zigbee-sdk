#!/usr/bin/env python3

#
# SPDX-FileCopyrightText: 2025-2026 Espressif Systems (Shanghai) CO LTD
#
# SPDX-License-Identifier: CC0-1.0
#

import argparse
import functools
import struct
import os

# ---------------- Generate ----------------
def generate_ota_file(**kwargs):
    file_id        = int(kwargs.get("file_id") or 0x0BEEF11E)
    header_version = int(kwargs.get("header_version") or 0x0100)
    manuf_id       = kwargs["manuf_id"]
    image_type     = kwargs["image_type"]
    file_version   = kwargs["file_version"]
    stack_version  = int(kwargs.get("stack_version") or 0x0002)
    header_string  = kwargs.get("header_string", "")

    sec_cred  = kwargs.get("security_credentials")
    upgrade_dest = kwargs.get("upgrade_dest")
    min_hw_ver = kwargs.get("min_hw_ver")
    max_hw_ver = kwargs.get("max_hw_ver")

    # ---------------- Tags ----------------
    tags = kwargs.get("tags", [])

    tag_blocks = []
    for item in tags:
        if not os.path.isfile(item['tag_file']):
            raise FileNotFoundError(f"Tag file not found: {item['tag_file']}")
        with open(item['tag_file'], "rb") as f:
            data = f.read()

        if item['tag_length'] is None:
            item['tag_length'] = int(len(data))
        else:
            item['tag_length'] = int(item['tag_length'])
            data = data[:item['tag_length']]

        tag_block = struct.pack("<H", item["tag_id"]) + struct.pack("<I", item['tag_length']) + data
        tag_blocks.append(tag_block)

    image_data = b"".join(tag_blocks)

    # ---------------- Header String ----------------
    header_str = header_string.encode("ascii")
    if len(header_str) > 32:
        raise ValueError("Header string requires max 32 bytes")
    header_str = header_str.ljust(32, b"\x00")

    # ---------------- Header Field Control ----------------
    if upgrade_dest:
        upgrade_dest = bytes.fromhex(upgrade_dest.replace(":", "").lower())
        if len(upgrade_dest) != 8:
            raise ValueError("upgrade-dest SHALL be 8-byte EUI64")

    field_ctrl = 0
    if sec_cred      is not None: field_ctrl |= 0x0001
    if upgrade_dest  is not None: field_ctrl |= 0x0002
    if min_hw_ver    is not None and max_hw_ver is not None: field_ctrl |= 0x0004

    # ---------------- Header ----------------
    # Optional Fields
    opt = b""
    if sec_cred      is not None: opt += struct.pack("<B", sec_cred)
    if upgrade_dest  is not None: opt += upgrade_dest
    if min_hw_ver    is not None: opt += struct.pack("<H", min_hw_ver)
    if max_hw_ver    is not None: opt += struct.pack("<H", max_hw_ver)
    # header length = fixed header + optional fields + 4 bytes Total Image Size
    header_len = 4+2+2+2+2+2+4+2+32+4+len(opt)  # fixed + optional
    total_len = header_len + len(image_data)

    print(f"File size: {total_len} bytes")
    header = struct.pack(
        "<I H H H H H I H 32s I",
        file_id,
        header_version,
        header_len,
        field_ctrl,
        manuf_id,
        image_type,
        file_version,
        stack_version,
        header_str,
        total_len
    )

    return header + opt + image_data

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Create Zigbee OTA file",
        epilog="Reads a firmware image file and outputs an OTA file"
    )

    any_int = functools.wraps(int)(functools.partial(int, base=0))

    # TODO: Consider Byte-Endian
    parser.add_argument("-d", "--file-id", type=any_int, help="OTA upgrade file identifier")
    parser.add_argument("-r", "--header-version", type=any_int, help="OTA Header version")
    parser.add_argument("-m", "--manuf-id", type=any_int, required=True, help="Manufacturer code")
    parser.add_argument("-i", "--image-type", type=any_int, required=True, help="Image type")
    parser.add_argument("-v", "--file-version", type=any_int, required=True, help="File version")
    parser.add_argument("-s", "--stack-version", type=any_int, default=2, help="Zigbee stack version")
    parser.add_argument("-g", "--header-string", type=str, default="", help="OTA Header string")
    parser.add_argument("--security-credentials", type=any_int, help="Security credentials (optional)")
    parser.add_argument("--upgrade-dest", type=str, help="Destination EUI64 (optional)")
    parser.add_argument("--min-hw-ver", type=any_int, help="Minimum hardware version (optional)")
    parser.add_argument("--max-hw-ver", type=any_int, help="Maximum hardware version (optional)")
    parser.add_argument(
        "--tag",
        action="append",
        nargs='+',
        metavar="TAG",
        help="Append a sub-element tag: TAG_ID [TAG_LENGTH] TAG_FILE (TAG_LENGTH optional)",
    )

    args = parser.parse_args()

    tag_list = []
    if args.tag:
        for t in args.tag:
            if len(t) == 2:
                tag_id, tag_file = t
                tag_length = None
            elif len(t) == 3:
                tag_id, tag_length, tag_file = t
            else:
                raise ValueError("Invalid number of arguments for --tag")
            tag_list.append({
                "tag_id": int(tag_id, 0),
                "tag_length": int(tag_length, 0) if tag_length is not None else None,
                "tag_file": tag_file,
            })
    args.tags = tag_list

    output = f"{args.manuf_id:04X}-{args.image_type:04X}-{args.file_version:08X}-ota-file.zigbee"

    #  Generate OTA data
    data = generate_ota_file(**vars(args))

    #  Write OTA file
    with open(output, "wb") as f:
        f.write(data)

    print(f"Generated OTA file: {output}")
