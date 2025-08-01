# SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD

# SPDX-License-Identifier: CC0-1.0

import pathlib
import pytest
import time
import os
from examples.zigbee_common import Common, ExampleDevice, CliDevice, MatchPattern
import logging

logging.basicConfig(level=logging.INFO)

IDF_PATH = os.environ.get("IDF_PATH")
CLI_CURRENT_DIR_CLIENT = str(pathlib.Path(__file__).parent) + '/esp_zigbee_all_device_types_app'
IDF_EXAMPLE_ON_OFF_LIGHT = str(IDF_PATH) + '/examples/zigbee/light_sample/HA_on_off_light'
IDF_EXAMPLE_ON_OFF_SWITCH = str(IDF_PATH) + '/examples/zigbee/light_sample/HA_on_off_switch'
IDF_EXAMPLE_GATEWAY = str(IDF_PATH) + '/examples/zigbee/esp_zigbee_gateway'
IDF_EXAMPLE_OT_RCP = str(IDF_PATH) + '/examples/openthread/ot_rcp'
idf_example_on_off_light_build_dir = CLI_CURRENT_DIR_CLIENT + '|' + IDF_EXAMPLE_ON_OFF_LIGHT
idf_example_on_off_switch_build_dir = IDF_EXAMPLE_ON_OFF_SWITCH + '|' + IDF_EXAMPLE_ON_OFF_LIGHT
idf_example_gateway_single_chip_build_dir = CLI_CURRENT_DIR_CLIENT + '|' + IDF_EXAMPLE_GATEWAY
idf_example_gateway_dual_chip_build_dir = CLI_CURRENT_DIR_CLIENT + '|' + IDF_EXAMPLE_OT_RCP + '|' + IDF_EXAMPLE_GATEWAY

# Case 12: IDF zigbee example on-off-light test
@pytest.mark.order(12)
@pytest.mark.esp32h2
@pytest.mark.esp32c6
@pytest.mark.idf_example
@pytest.mark.parametrize('count, app_path, erase_all', [(2, idf_example_on_off_light_build_dir, 'y'), ],
                         indirect=True, )
@pytest.mark.usefixtures('teardown_fixture')
def test_idf_example_on_off_light(dut):
    cli = CliDevice(dut[0])
    light_device = ExampleDevice(dut[1])
    light_device.check_response('Start network steering')
    cli.create_coordinator('on_off_switch', network_type='c')
    cli.get_device_network_info(coordinator=True)
    cli.network_open()
    light_device.get_example_device_network_info(coordinator=False)
    Common.check_network_matched(cli.network_info, light_device.network_info)
    # light on
    Common.cli_light_control_and_check(cli, light_device, on=True)
    time.sleep(1)
    # light off
    Common.cli_light_control_and_check(cli, light_device, on=False)


# Case 13: IDF zigbee example on-off-switch test
@pytest.mark.order(13)
@pytest.mark.esp32h2
@pytest.mark.esp32c6
@pytest.mark.idf_example
@pytest.mark.parametrize('count, app_path, erase_all', [(2, idf_example_on_off_switch_build_dir, 'y'), ],
                         indirect=True, )
@pytest.mark.usefixtures('teardown_fixture')
def test_idf_example_on_off_switch(dut):
    switch_device = ExampleDevice(dut[0])
    switch_device.get_example_device_network_info(coordinator=True)
    light_device = ExampleDevice(dut[1])
    light_device.get_example_device_network_info(coordinator=False)
    switch_device.check_response('Bound successfully')
    Common.check_network_matched(switch_device.network_info, light_device.network_info)

# Case 14: idf example dual-chip gateway test
@pytest.mark.order(14)
@pytest.mark.esp32s3
@pytest.mark.idf_example
@pytest.mark.dual_chip_gateway
@pytest.mark.parametrize('count, app_path, target, erase_all', [(3, idf_example_gateway_dual_chip_build_dir, 'esp32h2|esp32h2|esp32s3','y'), ],
                         indirect=True, )
@pytest.mark.usefixtures('teardown_fixture', 'erase_esp32s3_port')
def test_idf_example_gateway_dual_chip(dut):
    gateway_device = ExampleDevice(dut[2])
    gateway_device.check_response("Initialize Zigbee stack", timeout=100)
    gateway_device.get_example_device_network_info(coordinator=True)
    gateway_device.check_response(r'Network\([^)]*\) is open', timeout=10)
    # dut[1] is rcp
    cli = CliDevice(dut[0])
    cli.create_router('on_off_switch', network_type='c')
    cli.check_response(MatchPattern.joined_network, timeout=10)
    cli.get_device_network_info(coordinator=False)
    Common.check_network_matched(cli.network_info, gateway_device.network_info)
    Common.check_connection_status(cli, gateway_device.short_address)


# Case 15: idf example gateway single chip test reuses Case 11
@pytest.mark.order(15)
@pytest.mark.esp32c6
@pytest.mark.idf_example
@pytest.mark.parametrize('count, app_path, erase_all', [(2, idf_example_gateway_single_chip_build_dir, 'y'), ],
                         indirect=True, )
@pytest.mark.usefixtures('teardown_fixture')
def test_idf_example_gateway_single_chip(dut):
    gateway_device = ExampleDevice(dut[1])
    gateway_device.check_response("Initialize Zigbee stack", timeout=50)
    gateway_device.get_example_device_network_info(coordinator=True)
    gateway_device.check_response(r'Network\([^)]*\) is open', timeout=10)
    time.sleep(2)
    cli = CliDevice(dut[0])
    cli.create_router('on_off_switch', network_type='c')
    joined = False 
    # Wi-Fi coexistence with 802.15.4 causes difficulties in Zigbee transmission and reception. Increase the number of
    # network joining attempts to ensure successful network formation.
    for _ in range(10):
        try:
            cli.check_response(MatchPattern.joined_network, timeout=10)
            joined = True
            break
        except Exception:
            cli._start_bdb_comm('steer')
    assert joined, f"Device failed to join the network after 10 retries"
    cli.get_device_network_info(coordinator=False)
    Common.check_network_matched(cli.network_info, gateway_device.network_info)
    Common.check_connection_status(cli, gateway_device.short_address)
