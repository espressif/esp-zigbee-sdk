# SPDX-FileCopyrightText: 2022-2024 Espressif Systems (Shanghai) CO LTD

# SPDX-License-Identifier: CC0-1.0

import pathlib
import pytest
from constants import MatchPattern
import time
from examples.constants import ZigbeeCIConstants
from examples.zigbee_common import CliDevice, Common
from examples.zigbee_common import generic_chips_zigbee_test

CLI_CURRENT_DIR_CLIENT = str(pathlib.Path(__file__).parent) + '/esp_zigbee_all_device_types_app'
cli_build_dir = CLI_CURRENT_DIR_CLIENT + '|' + CLI_CURRENT_DIR_CLIENT


# Case 1: Zigbee network connection
@pytest.mark.order(1)
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all', [(2, cli_build_dir, 'y'), ], indirect=True, )
@generic_chips_zigbee_test
def test_zb_cli_zb_connection(dut, count, app_path, erase_all) -> None:
    switch_device = CliDevice(dut[0])
    light_device = CliDevice(dut[1])

    Common.cli_create_and_verify_network_connection(switch_device, light_device, 'on_off_switch',
                                                    'on_off_light', 'c')

    # ieee address and short address identify
    switch_device.zdo_request_and_check('ieee_addr', light_device.short_address)
    light_device_ieee_addr = switch_device.get_cli_comm_return_value(MatchPattern.ieee_addr)[0]
    assert light_device_ieee_addr == light_device.ieee_address

    switch_device.zdo_request_and_check('nwk_addr', light_device.ieee_address)
    short_address_return = switch_device.get_cli_comm_return_value(MatchPattern.nwk_address)[0]
    assert short_address_return == light_device.short_address


# Case 2: Zigbee network finding-binding
@pytest.mark.order(2)
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all', [(2, cli_build_dir, 'y'), ], indirect=True, )
@generic_chips_zigbee_test
def test_zb_cli_zc_finding_binding(dut, count, app_path, erase_all) -> None:
    # config coordinator and light
    switch_device = CliDevice(dut[0])
    light_device = CliDevice(dut[1])

    Common.cli_create_and_verify_network_connection(switch_device, light_device, 'on_off_switch',
                                                    'on_off_light', 'c')

    # zdo request ieee_addr
    switch_device.zdo_request_and_check('ieee_addr', light_device.short_address)
    light_device_ieee_addr = switch_device.get_cli_comm_return_value(MatchPattern.ieee_addr)[0]
    assert light_device_ieee_addr == light_device.ieee_address

    # zdo request node_desc
    switch_device.zdo_request_and_check('node_desc', light_device.short_address)

    # zdo request active_ep
    switch_device.zdo_request_and_check('active_ep', light_device.short_address)
    light_device_endpoint = switch_device.get_cli_comm_return_value(MatchPattern.active_ep)[0]
    assert light_device_endpoint == str(light_device.endpoint)

    # zdo request simple_desc
    switch_device.zdo_request_and_check('simple_desc', light_device.short_address, light_device.endpoint)
    switch_device.check_response(MatchPattern.on_off_light_in_clusters)

    # zdo bind
    cluster_id = ZigbeeCIConstants.on_off_cluster_id
    switch_device.zdo_bind_and_check(cluster_id, switch_device.endpoint, light_device.endpoint,
                                     switch_device.short_address, light_device.ieee_address)
    switch_device.zdo_request_and_check('bindings', switch_device.short_address)
    switch_device.check_response(fr'\|\s*0\s*\|\s*{switch_device.ieee_address}\s*\|\s*'
                                 fr'{switch_device.endpoint}\s*\|\s*{ZigbeeCIConstants.on_off_cluster_id:#06x}\s*\|\s*{light_device.ieee_address}\s*\|\s*{light_device.endpoint}\s*\|')

    # bind check
    switch_device.zcl_send_raw_and_check(switch_device.endpoint, cluster_id, '0x01')
    light_device.check_hex_response('01')
    switch_device.zcl_send_gen_and_check('read', switch_device.endpoint, cluster_id, attr=0)
    switch_device.check_hex_response('01')

    # zdo bind remove
    switch_device.zdo_bind_and_check(cluster_id, switch_device.endpoint, light_device.endpoint,
                                     switch_device.short_address, light_device.ieee_address, remove=True)
    switch_device.zdo_request_and_check('bindings', switch_device.short_address)
    switch_device.check_response(MatchPattern.empty_binding_table)


# #Case 3: Zigbee network ZCL command
@pytest.mark.order(3)
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all', [(2, cli_build_dir, 'y'), ], indirect=True, )
@generic_chips_zigbee_test
def test_zb_cli_zcl_command(dut, count, app_path, erase_all) -> None:
    switch_device = CliDevice(dut[0])
    light_device = CliDevice(dut[1])

    Common.cli_create_and_verify_network_connection(switch_device, light_device, 'color_dimmable_switch',
                                                    'color_dimmable_light', 'c')

    # zcl command on off 0x0006 cluster
    # On command
    Common.cli_light_switch_and_check_rsp(switch_device, light_device, '0x01', expect_rsp='01', send_read=True)
    # Off command
    Common.cli_light_switch_and_check_rsp(switch_device, light_device, '0x00', expect_rsp='00', send_read=True)
    # toggle command
    Common.cli_light_switch_and_check_rsp(switch_device, light_device, '0x02', expect_rsp='01', send_read=True)

    # zcl command level-control 0x0008 cluster
    # Move to level(with On/Off) command
    Common.cli_level_switch_and_check_rsp(switch_device, light_device, '0x04', expect_rsp='05', payload='0x05ffff',
                                          send_read=True)
    # Move (with On/Off) command
    Common.cli_level_switch_and_check_rsp(switch_device, light_device, '0x05', expect_rsp='00', payload='0x0105',
                                          send_read=True)
    # Step (with On/Off) command
    Common.cli_level_switch_and_check_rsp(switch_device, light_device, '0x06', expect_rsp='05', payload='0x00053200',
                                          send_read=True)
    # Step (with On/Off) command and Stop command
    Common.cli_level_switch_and_check_rsp(switch_device, light_device, '0x06', expect_rsp='08', payload='0x00051e00',
                                          send_read=True, check_stop_move=True)

    # zcl command color-control 0x0300 cluster
    # Move to color command
    Common.cli_color_switch_and_check_rsp(switch_device, light_device, '0x07', expect_x_value='15 30',
                                          expect_y_value='20 32', payload='0x153020320000')
    # Move color command and check stop move
    Common.cli_color_switch_and_check_rsp(switch_device, light_device, '0x08', expect_x_value='17 30',
                                          expect_y_value='22 32', payload='0x01000100')
    # Step color command x + 3, y + 3 in 5s
    Common.cli_color_switch_and_check_rsp(switch_device, light_device, '0x09', expect_x_value='1a 30',
                                          expect_y_value='25 32', payload='0x030003003200')


# #Case 4: Zigbee network leaving
@pytest.mark.order(4)
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all', [(2, cli_build_dir, 'y'), ], indirect=True, )
@generic_chips_zigbee_test
def test_zb_cli_zc_check_leaving(dut, count, app_path, erase_all) -> None:
    switch_device = CliDevice(dut[0])
    light_device = CliDevice(dut[1])

    Common.cli_create_and_verify_network_connection(switch_device, light_device, 'on_off_switch', 'on_off_light',
                                                    'c')
    time.sleep(2)
    switch_device.zdo_nwk_leave_and_check(light_device.short_address)
    switch_device.check_response(fr'Zigbee Node \({light_device.short_address}\) is leaving network')
    light_device.check_response(MatchPattern.left_network, timeout=2)
