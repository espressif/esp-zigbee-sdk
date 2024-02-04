#!/usr/bin/env python
#
# SPDX-FileCopyrightText: 2018-2022 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0
#

"""
Script to generate Zigbee factory NVS partition image.
"""

import os
import sys
import logging
import binascii
import argparse
import re
from ctypes import *
import struct
import csv
from future.moves.itertools import zip_longest


try:
    idf_path = os.environ['IDF_PATH']
    sys.path.insert(0, idf_path + '/tools/mass_mfg/')
    import mfg_gen
except Exception as e:
    print(e)
    sys.exit('Please check IDF_PATH')


try:
    import esp_idf_nvs_partition_gen.nvs_partition_gen as nvs_partition_gen
except Exception as e:
    print(e)
    sys.exit('Please check IDF_PATH')


is_output_header_file_style = False
# tx power threshold define
TX_POWER_MIN_VALUE_DBM = -40
TX_POWER_MAX_VALUE_DBM = 50
ZB_INVALID_TX_POWER_VALUE = 0x7F
# APS channel page size
ZB_PROD_CFG_APS_CHANNEL_LIST_SIZE = 5 
ZB_PROD_CFG_MAC_TX_POWER_CHANNEL_N = 27
# Install code Size
ZB_CCM_KEY_SIZE = 16
ZB_CCM_KEY_CRC_SIZ = 2
# RET CODE
RET_EMPTY = 0
RET_ERROR = 1
RET_NOT_FOUND = 2
RET_AGAIN = 3
RET_OK = 4
# product config version
ZB_PRODUCTION_CONFIG_SIZE = 1024
ZB_PRODUCTION_CONFIG_VERSION_1_0 = 0x01
ZB_PRODUCTION_CONFIG_VERSION_2_0 = 0x02
ZB_PRODUCTION_CONFIG_CURRENT_VERSION = ZB_PRODUCTION_CONFIG_VERSION_2_0
APP_PROD_CFG_CURRENT_VERSION = 0x0001


class zb_production_config_ver_2_t(Structure):
    APS_channel_page_size= ZB_PROD_CFG_APS_CHANNEL_LIST_SIZE * ZB_PROD_CFG_MAC_TX_POWER_CHANNEL_N
    install_code_size = ZB_CCM_KEY_SIZE + ZB_CCM_KEY_CRC_SIZ
    _fields_ = [("crc", c_uint), 
                ("len", c_ushort),
                ("version", c_ushort), # hdr (crc + len + version = 8 bytes)
                ("aps_channel_mask_list", c_uint * ZB_PROD_CFG_APS_CHANNEL_LIST_SIZE), # 5*4= 20 bytes
                ("mac_address", c_ubyte * 8), # (8 bytes)
                ("mac_tx_power", c_byte * APS_channel_page_size), # (5*27 = 135 bytes)
                ("options", c_ubyte),
                ("install_code", c_ubyte * install_code_size), # (16+2= 18 bytes)
                ]


class zb_manufacturer_config_t(Structure):
    _fields_ = [("version", c_ushort),
                ("manuf_code", c_ushort),
                ("manuf_name", c_wchar_p), 
                ]


def set_manufacturer_param(manufacturer_data, key, value):
    manufacturer_data.version = APP_PROD_CFG_CURRENT_VERSION
    if key == "manufacturer_name":
        if len(value) > 16: #  manufacturer_name length
            print('error : manufacturer name too log')
            return RET_ERROR
        else:
            manufacturer_data.manuf_name = value
    elif key == "manufacturer_code":
        manuf_code = int(value, 16)
        manuf_code = restrict_value(manuf_code, 0, 0xFFFF)
        manufacturer_data.manuf_code = manuf_code
    else:
        return RET_NOT_FOUND
    return RET_OK;  


def restrict_value(value, lower, upper):
  if value > upper:
    return upper
  elif value < lower:
    return lower
  return value


'''
 * Calculate CRC-16 checksum using classic algorithm based on polynomial arithmetic.
 * Use the standard CRC-16/X-25 config.
'''
def zb_crc_16(data, crc, length):
    data = binascii.unhexlify(data)
    for i in range(length):
        crc ^= data[i]
        for j in range(8):
            if crc & 0x0001 == 1:
                crc = (crc >> 1) ^ 0x8408
            else:
                crc >>= 1
    return crc


'''
 * Calculate CRC-32 checksum using classic algorithm based on polynomial arithmetic.
 * Use the polynomial x^32+x^26+x^23+x^22+x^16+x^12+x^11+x^10+x^8+x^7+x^5+x^4+x^2+x+1 (CRC-32).
 '''
def zb_crc32(p_buffer, length):
    # Initialize CRC with fixed value 
    crc = 0xFFFFFFFF
    for i in range(length):
        crc = crc ^ p_buffer[i]
        for j in range(8):
            if (crc & (1<<0)) != 0:
                mask = ~(0) & 0xFFFFFFFF
            else:
                mask = 0
            crc = (crc >> 1) ^ (0xEDB88320 & mask)
    return ~crc & 0xffffffff


def zb_calculate_production_config_crc(prod_cfg_ptr, prod_cfg_size):
    return zb_crc32(prod_cfg_ptr, prod_cfg_size)


def zb_pro_cfg_convert_to_byte_list(data, data_type, data_len):
    data_arry = []
    data_list = []
    if data_len == 1:
        data_list.append(data)
    else:
        data_list = data
    for i in range(len(data_list)):
        data_bytes = b''
        if data_type == 'c_ushort':
            data_bytes = struct.pack("<H", data_list[i]) #  < little type storge
        elif data_type == 'c_uint':
            data_bytes = struct.pack("<I", data_list[i]) #  < little type storge
        elif data_type == 'c_uchar' or data_type == 'c_char' or data_type == 'c_ubyte' or data_type == 'c_byte':
            data_bytes = struct.pack("<B", data_list[i]) #  < little type storge
        elif data_type == 'c_wchar_p':
            for k in range(len(data_list[i])):
                data =  struct.pack("<B", ord(data_list[i][k])) #  < little type storge
                data_bytes = data_bytes + data
        for j in range(len(data_bytes)):
            data_arry.append(int(data_bytes[j]))
    return data_arry

 
def table_list_convert_to_byte_list(data_list):
    g_pro_cfg_data = []
    for i in range(len(data_list)):
        g_pro_cfg_data += zb_pro_cfg_convert_to_byte_list(data_list[i][0], data_list[i][1], data_list[i][2])
    return g_pro_cfg_data


def zb_pro_cfg_byte_list_add(zb_pro_cfg_struct):
    data_list = [[zb_pro_cfg_struct.len, 'c_ushort', 1],
                [zb_pro_cfg_struct.version, 'c_ushort', 1],
                [zb_pro_cfg_struct.aps_channel_mask_list, 'c_uint', ZB_PROD_CFG_APS_CHANNEL_LIST_SIZE],
                [zb_pro_cfg_struct.mac_address, 'c_ubyte', 8],
                [zb_pro_cfg_struct.mac_tx_power, 'c_ubyte', ZB_PROD_CFG_APS_CHANNEL_LIST_SIZE * ZB_PROD_CFG_MAC_TX_POWER_CHANNEL_N],
                [zb_pro_cfg_struct.options, 'c_ubyte', 1],
                [zb_pro_cfg_struct.install_code, 'c_ubyte', ZB_CCM_KEY_SIZE + ZB_CCM_KEY_CRC_SIZ],
                ]
    data_arry = table_list_convert_to_byte_list(data_list)
    return data_arry


def zb_application_byte_list_add(app_data_struct):
    data_list = [[app_data_struct.version, 'c_ushort', 1],
    [app_data_struct.manuf_code, 'c_ushort', 1],
    [app_data_struct.manuf_name, 'c_wchar_p', 1],
    ]
    data_arry = table_list_convert_to_byte_list(data_list)
    return data_arry


def set_common_section_parameter(zb_pro_cfg_section_data, key, value):
    if  key.find('channel_mask_page') != -1:
        # channel page
        channel_page = key.split('channel_mask_page')[1]
        channel_page_number = int(channel_page, 10)
        # channel mask
        mask = int(value, 16)
        ZB_TRANSCEIVER_ALL_CHANNELS_MASK = 0x07FFF800 # 0000.0111 1111.1111 1111.1000 0000.0000
        if channel_page_number == 0:
            zb_pro_cfg_section_data.aps_channel_mask_list[0] = (mask & ZB_TRANSCEIVER_ALL_CHANNELS_MASK)
        elif (channel_page_number == 28):
            zb_pro_cfg_section_data.aps_channel_mask_list[1] = (28<<27) | (mask & 0x7ffffff)
        elif (channel_page_number == 29):
            zb_pro_cfg_section_data.aps_channel_mask_list[2] = (29<<27) | (mask & 0x1f)
        elif (channel_page_number == 30):
            zb_pro_cfg_section_data.aps_channel_mask_list[3] = (30<<27) | (mask & 0x7ffffff)
        elif (channel_page_number == 31):
            zb_pro_cfg_section_data.aps_channel_mask_list[4] = (31<<27) | (mask & 0x7ffffff)
        else:
            print("Unknown channel page:"+ channel_page_number)
            return RET_ERROR
    elif key == 'mac_address':
        if value == 'NULL':  # installcode is NULL
            return RET_OK
        if len(value) == 16:
            data = re.findall(r'\w{2}',value) # len = 2 split the hex string
            for i in range(8):
                zb_pro_cfg_section_data.mac_address[7-i] = int(data[i], 16)
        else:
            print("extended address invaild")
            return RET_ERROR
    elif key == 'default_mac_tx_power':
        default_tx_power = int(value, 10)
        if default_tx_power != ZB_INVALID_TX_POWER_VALUE:
            tx_power = restrict_value(default_tx_power, TX_POWER_MIN_VALUE_DBM, TX_POWER_MAX_VALUE_DBM)
           
        for i in range(ZB_PROD_CFG_APS_CHANNEL_LIST_SIZE):
            for j in range(ZB_PROD_CFG_MAC_TX_POWER_CHANNEL_N):
                zb_pro_cfg_section_data.mac_tx_power[i * ZB_PROD_CFG_MAC_TX_POWER_CHANNEL_N + j] = tx_power     
    elif key == 'default_mac_tx_power_page':
        channel_page = key.split('default_mac_tx_power_page')[1]
        channel_page_number = int(channel_page, 10)
        default_tx_power = int(value, 10)
        if default_tx_power != ZB_INVALID_TX_POWER_VALUE:
            tx_power = restrict_value(default_tx_power, TX_POWER_MIN_VALUE_DBM, TX_POWER_MAX_VALUE_DBM)
        
        channel_page_index = 0
        if channel_page_number > 0:
            channel_page_index = channel_page_number - 27
        
        if channel_page_index < ZB_PROD_CFG_APS_CHANNEL_LIST_SIZE:
            for j in range(ZB_PROD_CFG_MAC_TX_POWER_CHANNEL_N):
                zb_pro_cfg_section_data.mac_tx_power[channel_page_index * ZB_PROD_CFG_MAC_TX_POWER_CHANNEL_N + j] = tx_power     
        else:
            print("bad channel page")
            return RET_ERROR
    elif key == 'mac_tx_power':
        data = value.split(',')
        if len(data) == 3:
            channel_page_number = int(data[0], 10)
            channel_index = int(data[1], 10)
            tx_power = int(data[2], 10)

            if tx_power != ZB_INVALID_TX_POWER_VALUE:
                tx_power = restrict_value(tx_power, TX_POWER_MIN_VALUE_DBM, TX_POWER_MAX_VALUE_DBM)
            
            channel_page_index = 0
            if channel_page_number > 0:
                channel_page_index = channel_page_number - 27
            
            if channel_page_index < ZB_PROD_CFG_APS_CHANNEL_LIST_SIZE:
                if channel_index >=0 and channel_index < 27:
                    zb_pro_cfg_section_data.mac_tx_power[channel_page_index * ZB_PROD_CFG_MAC_TX_POWER_CHANNEL_N + channel_index] = tx_power     
            else:
                print("bad channel page")   
                return RET_ERROR     
        else:
            print("bad tx power parameters")    
            return RET_ERROR   
    elif key == 'installcode':
        if value == 'NULL':  # installcode is NULL
            return RET_OK

        ic_length = int(len(value)/2 - 2) # Length in bytes: 1 byte == 2 char symbols; ic length: total_len - 2 bytes CRC 
        ic_type_table = [6, 8, 12 ,16]

        is_ic_type = ic_type_table.count(ic_length) # ic type in ic type table?
        if is_ic_type:
            ic_type = ic_type_table.index(ic_length)
        else:
            print("ic type error")    
            return RET_ERROR
        install_code_raw = [[]] * (ZB_CCM_KEY_SIZE + ZB_CCM_KEY_CRC_SIZ)
        data = re.findall(r'\w{2}',value) # len = 2 split the hex string
        for i in range(len(data)):
            install_code_raw[i] = int(data[i], 16)

        calculated_crc = ~zb_crc_16(value, 0xffff, ic_length) & 0xffff
        read_crc = install_code_raw[ic_length] +  (install_code_raw[ic_length + 1] << 8)
        if calculated_crc != read_crc:
            print("ic crc error")   
            return RET_ERROR
        zb_pro_cfg_section_data.options |= ic_type

        for i in range(ic_length + 2):
            zb_pro_cfg_section_data.install_code[i] = install_code_raw[i]
        for i in range(ZB_CCM_KEY_SIZE - ic_length):
            zb_pro_cfg_section_data.install_code[ic_length + ZB_CCM_KEY_CRC_SIZ + i] = 0
    else:
        return RET_NOT_FOUND


def generate_binary(args, key_value_list):
    g_product_config_len = 0
    bin_ext = '.bin'
    filename, ext = os.path.splitext(args.output)
    if bin_ext not in ext:
        sys.exit('Error: `%s`. Only `.bin` extension allowed.' % args.output)
    args.outdir, args.output = nvs_partition_gen.set_target_filepath(args.outdir, args.output)
    # init parameter
    zb_pro_cfg_data = zb_production_config_ver_2_t()
    zb_manaufacturer_data = zb_manufacturer_config_t()
    # Version is not utilized at the moment
    zb_pro_cfg_data.version = ZB_PRODUCTION_CONFIG_CURRENT_VERSION
    g_product_config_len += 8 + 20 + 8 + 135 + 1 + 18 # zb_production_config_ver_2_t:  len = 190

    for index in range(0, len(key_value_list)):
        try:
            # Check key length
            ret = 0
            key = key_value_list[index][0]
            value = key_value_list[index][1]
            ret = set_common_section_parameter(zb_pro_cfg_data, key, value)
            ret = set_manufacturer_param(zb_manaufacturer_data, key, value)

        except RuntimeError as e:
            print(e)
            sys.exit(-2)

    g_product_config_len += 2 + 2 + len(zb_manaufacturer_data.manuf_name)
    # file data length
    zb_pro_cfg_data.len = g_product_config_len
    g_pro_cfg_buffer = []
    # product config buffer: table storge
    g_pro_cfg_buffer = zb_pro_cfg_byte_list_add(zb_pro_cfg_data)
    g_pro_cfg_buffer += zb_application_byte_list_add(zb_manaufacturer_data)
    # fill prod_cfg_header (crc)
    zb_pro_cfg_data.crc = zb_calculate_production_config_crc(g_pro_cfg_buffer,len(g_pro_cfg_buffer))
    # table change to write binary
    data_crc_list = [[zb_pro_cfg_data.crc, 'c_uint', 1]]
    data_crc_arry = table_list_convert_to_byte_list(data_crc_list)
    g_pro_cfg_buffer = data_crc_arry + g_pro_cfg_buffer  # g_pro_cfg_buffer = hdr(crc len version) + pro_cfg + csk + application
    # fill prod_cfg magic header
    PRODUCTION_CONFIG_HEADER = [0xE7, 0x37, 0xDD, 0xF6]
    g_pro_cfg_buffer = PRODUCTION_CONFIG_HEADER + g_pro_cfg_buffer  # buffer list

    # generate arry config file 
    if is_output_header_file_style:
        filename, ext = os.path.splitext(args.output)
        file_name =  filename  + "-output_product_cfg.h"
        file_out = open(file_name,'wb')
        g_pro_cfg_buffer_file = []
        g_pro_cfg_buffer_file = b'unsigned char production_config[] = {\n'
        for i in range(len(g_pro_cfg_buffer)):
            str_data = '0x' + hex(g_pro_cfg_buffer[i])[2:].zfill(2) + ', '
            if (i+1) % 16 == 0:
                str_data += '\n'
            data_btyes = bytes(str_data, 'utf-8')
            g_pro_cfg_buffer_file += data_btyes
        g_pro_cfg_buffer_file += b'};\nunsigned int production_config_len = %d;'%(len(g_pro_cfg_buffer))
        file_out.write(g_pro_cfg_buffer_file)
        file_out.close()

    # generate binary
    output_file = open(args.output, 'wb')
    g_pro_cfg_buffer_bytes = b''.join(map(lambda x:int.to_bytes(x,1,'little'),g_pro_cfg_buffer)) # little write bytes
    output_file.write(g_pro_cfg_buffer_bytes)
    output_file.close()
    print('\nCreated NVS binary: ===>', args.output)


def generate_binary_from_csv(args):
    file_identifier_value = '0'
    bin_str = 'bin'
    line = None

    try:
        csv_values_file = open(args.csv, 'r', newline=None)
        # Read header line
        header_key_line = csv_values_file.readline()
        # header_key_line
        header_key_line = header_key_line.strip().split(',')
        # Create new directory(if doesn't exist) to store bin file generated
        output_bin_target_dir = mfg_gen.create_dir(bin_str, args.outdir)

        line = csv_values_file.readline()
        if not isinstance(line, str):
            line = line.encode('utf-8')
        values_data_line = line.strip().split(',')

        keys_in_values_file = header_key_line
        while values_data_line:
            key_value_data = list(zip_longest(keys_in_values_file, values_data_line))
            # Get file identifier value from key_values
            fileid = 'id'
            for key_value in key_value_data:
                if key_value[0] == 'mac_address':
                    if key_value[1] != 'NULL':
                        fileid = 'mac_address'
                        break
            file_identifier_value = mfg_gen.get_fileid_val(fileid, key_value_data, file_identifier_value)  
            # get key-value pair
            key_value_pair = key_value_data[1:]
            # Verify if output bin file does not exist
            bin_filename = file_identifier_value + '.' + bin_str  
            output_bin_file = output_bin_target_dir + bin_filename
            if os.path.isfile(output_bin_file):
                raise SystemExit('Target binary file: %s already exists.`' % output_bin_file)
            # Generate binary
            args.output = os.path.join(bin_str, bin_filename)
            generate_binary(args, key_value_pair)
            # Read next line
            line = csv_values_file.readline()
            if not isinstance(line, str):
                line = line.encode('utf-8')
            values_data_line = line.strip().split(',')
            # # break when value is none
            if len(values_data_line) == 1 and '' in values_data_line:
                break
        print('\nFiles generated in %s ...' % args.outdir)

    except Exception as e:
        print(e)
        exit(1)
    finally:
        csv_values_file.close()


def generate(args):
    args.outdir = os.path.join(args.outdir, '')
    # if csv is not present creat a sigle device for generate binary
    file_name = os.getcwd() + '/sigle_device.csv'
    
    # The input key value do not through csv file
    if args.csv is None:
        csv_values_file = open(file_name, 'w')
        key = ['id', 'installcode', 'mac_address', 'channel_mask_page0', 'manufacturer_name', 'manufacturer_code']
        value = [1, args.installcode, args.mac_address, hex(args.channel_mask), args.manufacturer_name, hex(args.manufacturer_code)]
        sigle_device_csv = csv.writer(csv_values_file)
        sigle_device_csv.writerow(key)
        sigle_device_csv.writerow(value)
        csv_values_file.close()
        args.csv = file_name

    generate_binary_from_csv(args)
    os.remove(file_name)       


def validate_args(args):
    # # csv and installcode/mac_address/channel_mask/manufacturer_name/manufacturer_code both should not present
    if (args.csv and args.installcode != 'NULL' and args.mac_address != 'NULL'):
        logging.error("csv and installcode/mac_address/channel_mask/manufacturer_name/ manufacturer_code should not be both present or none")
        sys.exit(1)
    # csv, first line is heder
    if args.csv is not None:
        count = len(open(args.csv, 'r').readlines())
        if count < 2:
            logging.error('Invalid csv:' + (args.csv))
            sys.exit(1)
    # Validate the installcode
    if args.installcode is not None:
        if args.installcode != 'NULL':
            ic_type = [6, 8, 12, 16]
            crc_len = 2
            install_code_len = len(args.installcode)
            if ((install_code_len/2)-crc_len  not in ic_type)  :
                logging.error('Invalid installcode:' + (args.installcode))
                sys.exit(1)
    # Validate the mac address
    if (args.mac_address is not None) :
        if args.mac_address != 'NULL':
            if (len(args.mac_address)/2 != 8):
                logging.error('Invalid mac_address:' + str(args.mac_address))
                sys.exit(1)
    # Validate the channle mask
    if (args.channel_mask is not None) and args.channel_mask not in range(0, 0xFFFFFFFF):
        logging.error('Invalid channle mask:' + hex(args.channel_mask))
        sys.exit(1)
    # Validate the manufacturer name 
    if (args.manufacturer_name is not None) and len(args.manufacturer_name) > 15:
        logging.error('Invalid manufacturer name :' + (args.manufacturer_name))
        sys.exit(1)
    # Validate the manufacturer code 
    if (args.manufacturer_code is not None) and args.manufacturer_code not in range(0, 0xFFFF):
        logging.error('Invalid manufacturer code :' + hex(args.manufacturer_code))
        sys.exit(1)


def get_args():
    def any_base_int(s): return int(s, 0)
    parser = argparse.ArgumentParser(description='ESP Zigbee Manufacturing Utility')
    parser.add_argument('--csv',type=str, help='CSV file containing the partition key-values specified by the user.')
    parser.add_argument('-i', '--installcode', default='NULL', type=str, help='The installcode.')
    parser.add_argument('-m', '--mac_address', default='NULL', type=str, help='The mac address.')
    parser.add_argument('-c', '--channel_mask', default=0x07FFF800, type=any_base_int, help='The channel mask page0, default channel mask=0x8000, channel:11~26.')
    parser.add_argument('-mn', '--manufacturer_name', default='Espressif', type=str, help='The manufacturer name.')
    parser.add_argument('-mc', '--manufacturer_code', default=0x131B, type=any_base_int, help='The manufacturer code.')
    parser.add_argument('--outdir', default=os.getcwd(), help='Output directory to store files created (Default: current directory)')
    return parser.parse_args()


def main():
    args = get_args()
    validate_args(args)
    generate(args)


if __name__ == '__main__':
    main()
