# SPDX-FileCopyrightText: 2023-2024 Espressif Systems (Shanghai) CO LTD

# SPDX-License-Identifier: CC0-1.0

import pathlib
import pytest
import time
from constants import ZigbeeCIConstants, MatchPattern
from examples.zigbee_common import Common, ExampleDevice, CliDevice
import logging

logging.basicConfig(level=logging.INFO)

BASIC_CURRENT_DIR_CLIENT = str(pathlib.Path(__file__).parent) + '/esp_zigbee_customized_devices/customized_client'
BASIC_CURRENT_DIR_SERVER = str(pathlib.Path(__file__).parent) + '/esp_zigbee_customized_devices/customized_server'
basic_pytest_build_dir = BASIC_CURRENT_DIR_CLIENT + '|' + BASIC_CURRENT_DIR_SERVER

OTA_CURRENT_DIR_CLIENT = str(pathlib.Path(__file__).parent) + '/esp_zigbee_ota/ota_client'
OTA_CURRENT_DIR_SERVER = str(pathlib.Path(__file__).parent) + '/esp_zigbee_ota/ota_server'
ota_pytest_build_dir = OTA_CURRENT_DIR_CLIENT + '|' + OTA_CURRENT_DIR_SERVER

CLI_CURRENT_DIR_CLIENT = str(pathlib.Path(__file__).parent) + '/esp_zigbee_all_device_types_app'
SLEEP_CURRENT_DIR_SERVER = str(pathlib.Path(__file__).parent) + '/esp_zigbee_sleep/light_sleep'
sleep_pytest_build_dir = CLI_CURRENT_DIR_CLIENT + '|' + SLEEP_CURRENT_DIR_SERVER

SWITCH_CURRENT_DIR_SERVER = str(pathlib.Path(__file__).parent) + '/esp_zigbee_touchlink/touchlink_switch'
LIGHT_CURRENT_DIR_CLIENT = str(pathlib.Path(__file__).parent) + '/esp_zigbee_touchlink/touchlink_light'
touchlink_pytest_build_dir = LIGHT_CURRENT_DIR_CLIENT + '|' + SWITCH_CURRENT_DIR_SERVER

DEEP_SLEEP_CURRENT_DIR_SERVER = str(pathlib.Path(__file__).parent) + '/esp_zigbee_sleep/deep_sleep'
deep_sleep_pytest_build_dir = CLI_CURRENT_DIR_CLIENT + '|' + DEEP_SLEEP_CURRENT_DIR_SERVER

GATEWAY_CURRENT_DIR_CLIENT = str(pathlib.Path(__file__).parent) + '/esp_zigbee_gateway'
gateway_pytest_build_dir = CLI_CURRENT_DIR_CLIENT + '|' + GATEWAY_CURRENT_DIR_CLIENT


# Case 5: Zigbee network connection basic test
@pytest.mark.order(5)
@pytest.mark.esp32h2
@pytest.mark.esp32c6
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all', [(2, basic_pytest_build_dir, 'y'), ], indirect=True, )
@pytest.mark.usefixtures('teardown_fixture')
def test_zb_basic(dut, count, app_path, erase_all):
    client = ExampleDevice(dut[0])
    server = ExampleDevice(dut[1])

    Common.check_zigbee_network_status(client, server)
    status_value, address_value, endpoint_value = client.get_match_desc_response_values()
    assert status_value == address_value == '0'
    assert endpoint_value == '10'

    status_value, endpoint_count_value = client.get_active_endpoint_response_values()
    assert status_value == '0'
    # release/v1.0.8 change endpoint_count to 2
    assert endpoint_count_value == '2'

    status_value, device_id_value, app_version_value, profile_id_value, endpoint_id_value = \
        client.get_simple_desc_response_values()

    assert status_value == app_version_value == '0'
    assert device_id_value == '256'
    assert profile_id_value == '104'
    assert endpoint_id_value == '10'

    address_value, endpoint_value, status_value = client.get_bind_response_values()
    assert address_value == status_value == '0'
    assert endpoint_value == '1'

    address, src_endpoint, dst_endpoint, cluster = client.get_received_report_values()
    assert address == '0'
    assert src_endpoint == '10'
    assert dst_endpoint == '1'
    assert cluster == '6'


# Case 6: Zigbee ota test
@pytest.mark.order(6)
@pytest.mark.esp32h2
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all', [(2, ota_pytest_build_dir, 'y'), ], indirect=True, )
@pytest.mark.usefixtures('teardown_fixture')
def test_zb_ota(dut, count, app_path, erase_all):
    client = ExampleDevice(dut[0])
    server = ExampleDevice(dut[1])
    Common.check_zigbee_network_status(client, server)
    assert (str(server.dut.expect(r'OTA client address: (0x[0-9a-fA-F]+)', timeout=3)[1].decode())
            not in ZigbeeCIConstants.default_id)
    ota_version, image_type, manufacturer_code = server.get_ota_information()
    assert ota_version == ZigbeeCIConstants.ota_version
    assert image_type == ZigbeeCIConstants.image_type
    assert manufacturer_code == ZigbeeCIConstants.manufacturer_code
    client_address, progress, total = server.get_ota_transmits_data()
    assert client_address != '0x0'
    assert progress != '0'
    assert total == ZigbeeCIConstants.ota_total_package
    progress, total = client.get_ota_receives_data()
    assert progress != '0'
    assert total == ZigbeeCIConstants.ota_total_package


# Case 7: Zigbee light sleep test
@pytest.mark.order(7)
@pytest.mark.esp32h2
@pytest.mark.esp32c6
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all', [(2, sleep_pytest_build_dir, 'y'), ], indirect=True, )
@pytest.mark.usefixtures('teardown_fixture')
def test_zb_sleep(dut, count, app_path, erase_all):
    cli = CliDevice(dut[0])
    sleep_device = ExampleDevice(dut[1])
    cli.create_coordinator('on_off_switch', network_type='c')
    cli.get_device_network_info(coordinator=True)
    cli.network_open()
    time.sleep(3)
    sleep_device.get_example_device_network_info(coordinator=False)
    Common.check_network_matched(cli.network_info, sleep_device.network_info)
    Common.check_zigbee_sleep_intervals(sleep_device)

    # light on
    Common.cli_light_control_and_check(cli, sleep_device, on=True)
    # light off
    Common.cli_light_control_and_check(cli, sleep_device, on=False)
    Common.check_zigbee_sleep_intervals(sleep_device)


# Case 8: Zigbee touchlink test
@pytest.mark.order(8)
@pytest.mark.esp32h2
@pytest.mark.esp32c6
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all', [(2, touchlink_pytest_build_dir, 'y'), ], indirect=True, )
@pytest.mark.usefixtures('teardown_fixture')
def test_zb_touch_link(dut, count, app_path, erase_all):
    light = ExampleDevice(dut[0])
    switch = ExampleDevice(dut[1])
    light.check_response('Touchlink target is ready, awaiting commissioning')
    time.sleep(5)
    switch.check_response('Scanning as a Touchlink initiator...')
    # check network connect and return network info
    light.get_example_device_network_info(coordinator=False)
    switch.get_example_device_network_info(coordinator=False)
    Common.check_network_matched(light.network_info, switch.network_info)
    time.sleep(5)
    light.check_response('Touchlink target commissioning finished')
    switch.check_response('Bound successfully!')


# Case 9: Zigbee gateway test
@pytest.mark.order(9)
@pytest.mark.esp32s3
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, target, erase_all', [(2, gateway_pytest_build_dir, 'esp32h2|esp32s3', 'y'), ],
                         indirect=True, )
@pytest.mark.usefixtures('teardown_fixture')
def test_zb_gateway(dut, count, app_path, target):
    gateway_device = ExampleDevice(dut[1])
    cli = CliDevice(dut[0])
    # add sleep time to wait rcp update ready
    gateway_device.check_response(r'\*\*\* MATCH VERSION! \*\*\*', timeout=30)
    # add sleep time to wait gateway Network steering
    time.sleep(10)
    gateway_device.get_example_device_network_info(coordinator=True)
    cli.create_router('on_off_light', network_type='c')
    # wait connect gateway
    joined_short_address = gateway_device.dut.expect(r'New device commissioned or rejoined'
                                                     r' \(short: (0x[a-fA-F0-9]{4})\)', timeout=3)[1].decode()
    cli.check_response(MatchPattern.joined_network)
    cli.get_device_network_info(coordinator=False)
    logging.info(f"gateway_info:{gateway_device.network_info}")
    Common.check_network_matched(gateway_device.network_info, cli.network_info)
    assert cli.short_address == joined_short_address


# Case 10: Zigbee deep sleep test
@pytest.mark.order(10)
@pytest.mark.esp32h2
@pytest.mark.esp32c6
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all', [(2, deep_sleep_pytest_build_dir, 'y'), ], indirect=True, )
@pytest.mark.usefixtures('teardown_fixture')
def test_zb_deep_sleep(dut, count, app_path, erase_all):
    cli = CliDevice(dut[0])
    sleep_device = ExampleDevice(dut[1])
    sleep_device.check_response('Not a deep sleep reset')
    sleep_device.check_response('Enabling timer wakeup')
    cli.create_coordinator('on_off_switch', network_type='c')
    cli.get_device_network_info(coordinator=True)
    cli.network_open()
    sleep_device.get_example_device_network_info(coordinator=False)
    Common.check_network_matched(cli.network_info, sleep_device.network_info)
    sleep_device.check_response('Start one-shot timer for 5s to enter the deep sleep')
    sleep_device.check_response('Enter deep sleep', timeout=6)
    sleep_device.check_response(r'0x5 \(SLEEP_WAKEUP\)', timeout=21)
    sleep_device.check_response('Enabling timer wakeup')
    cli.check_response(fr'New device commissioned or rejoined \(short: {sleep_device.short_address}')


# Case 11: Zigbee gateway single chip test
@pytest.mark.order(11)
@pytest.mark.esp32c6
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all', [(2, gateway_pytest_build_dir, 'y'), ],
                         indirect=True, )
@pytest.mark.usefixtures('teardown_fixture')
def test_gateway_single_chip(dut):
    gateway_device = ExampleDevice(dut[1])
    gateway_device.check_response("Initialize Zigbee stack", timeout=50)
    gateway_device.get_example_device_network_info(coordinator=True)
    gateway_device.check_response("Network steering started")
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
