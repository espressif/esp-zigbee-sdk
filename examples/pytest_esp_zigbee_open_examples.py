# SPDX-FileCopyrightText: 2022-2026 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: CC0-1.0

import pathlib
import pytest
import time
from constants import ZigbeeCIConstants, MatchPattern
from zigbee_common import Common, ExampleDevice, CliDevice, clean_buffer
from zigbee_common import generic_chips_zigbee_test, dual_chip_gateway, ota_chip_test
import logging

logging.basicConfig(level=logging.INFO)

OTA_CURRENT_DIR_CLIENT = str(pathlib.Path(__file__).parent) + '/ota_upgrade/ota_client'
OTA_CURRENT_DIR_SERVER = str(pathlib.Path(__file__).parent) + '/ota_upgrade/ota_server'
ota_pytest_build_dir = OTA_CURRENT_DIR_CLIENT + '|' + OTA_CURRENT_DIR_SERVER

CLI_CURRENT_DIR_CLIENT = str(pathlib.Path(__file__).parent) + '/all_device_types_app'
SLEEP_CURRENT_DIR_SERVER = str(pathlib.Path(__file__).parent) + '/sleepy_devices/light_sleep_end_device'
sleep_pytest_build_dir = CLI_CURRENT_DIR_CLIENT + '|' + SLEEP_CURRENT_DIR_SERVER

INITIATOR_CURRENT_DIR_SERVER = str(pathlib.Path(__file__).parent) + '/touchlink/touchlink_target'
TARGET_CURRENT_DIR_CLIENT = str(pathlib.Path(__file__).parent) + '/touchlink/touchlink_initiator'
touchlink_pytest_build_dir = INITIATOR_CURRENT_DIR_SERVER + '|' + TARGET_CURRENT_DIR_CLIENT

DEEP_SLEEP_CURRENT_DIR_SERVER = str(pathlib.Path(__file__).parent) + '/sleepy_devices/deep_sleep_end_device'
deep_sleep_pytest_build_dir = CLI_CURRENT_DIR_CLIENT + '|' + DEEP_SLEEP_CURRENT_DIR_SERVER

GATEWAY_CURRENT_DIR_CLIENT = str(pathlib.Path(__file__).parent) + '/zigbee_gateway'
gateway_pytest_build_dir = CLI_CURRENT_DIR_CLIENT + '|' + GATEWAY_CURRENT_DIR_CLIENT

HA_DIMMABLE_LIGHT_CURRENT_DIR = str(pathlib.Path(__file__).parent) + '/home_automation_devices/color_dimmable_light'
HA_DIMMABLE_SWITCH_CURRENT_DIR = str(pathlib.Path(__file__).parent) + '/home_automation_devices/color_dimmer_switch'
ha_dimmable_light_pytest_build_dir = HA_DIMMABLE_LIGHT_CURRENT_DIR + '|' + HA_DIMMABLE_SWITCH_CURRENT_DIR

HA_ON_OFF_LIGHT_CURRENT_DIR = str(pathlib.Path(__file__).parent) + '/home_automation_devices/on_off_light'
HA_ON_OFF_SWITCH_CURRENT_DIR = str(pathlib.Path(__file__).parent) + '/home_automation_devices/on_off_switch'
ha_on_off_light_pytest_build_dir = HA_ON_OFF_LIGHT_CURRENT_DIR + '|' + HA_ON_OFF_SWITCH_CURRENT_DIR

HA_TEMPERATURE_SENSOR_CURRENT_DIR = str(pathlib.Path(__file__).parent) + '/home_automation_devices/temperature_sensor'
HA_THERMOSTAT_CURRENT_DIR = str(pathlib.Path(__file__).parent) + '/home_automation_devices/thermostat'
ha_thermostat_pytest_build_dir = HA_THERMOSTAT_CURRENT_DIR + '|' + HA_TEMPERATURE_SENSOR_CURRENT_DIR

DATA_PRODUCER_CURRENT_DIR = str(pathlib.Path(__file__).parent) + '/customized_devices/data_producer'
DATA_CONSUMER_CURRENT_DIR = str(pathlib.Path(__file__).parent) + '/customized_devices/data_consumer'
data_producer_pytest_build_dir = DATA_PRODUCER_CURRENT_DIR + '|' + DATA_CONSUMER_CURRENT_DIR

# case 5: Zigbee customized devices test

@pytest.mark.order(5)
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all', [(2, data_producer_pytest_build_dir, 'y'), ], indirect=True, )
@generic_chips_zigbee_test
def test_zb_customized_devices(dut, count, app_path, erase_all):
    data_producer_device = ExampleDevice(dut[0])
    data_consumer_device = ExampleDevice(dut[1])
    data_producer_device.get_example_device_network_info(coordinator=True, timeout=20)
    data_consumer_device.get_example_device_network_info(coordinator=False, timeout=30)
    Common.check_network_matched(data_producer_device.network_info, data_consumer_device.network_info)
    data_consumer_device.check_response(MatchPattern.bound_customized_data_producer, timeout=10)

# Case 6: Zigbee ota test
@pytest.mark.order(6)
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all', [(2, ota_pytest_build_dir, 'y'), ], indirect=True, )
@ota_chip_test
def test_zb_ota(dut, count, app_path, erase_all):
    client = ExampleDevice(dut[0])
    server = ExampleDevice(dut[1])
    Common.check_zigbee_network_status(client, server)
    assert (str(server.dut.expect(r'Client: short_addr=(0x[0-9a-fA-F]+)', timeout=3)[1].decode())
            not in ZigbeeCIConstants.default_id)
    server.check_response(MatchPattern.ota_sending_block)
    manufacturer_code, image_type, ota_version = server.get_ota_information()
    assert ota_version == ZigbeeCIConstants.ota_version
    assert image_type == ZigbeeCIConstants.image_type
    assert manufacturer_code == ZigbeeCIConstants.manufacturer_code
    client.check_response(MatchPattern.ota_receiving_block)
    server.check_response(MatchPattern.ota_sending_block)
    progress, total = server.get_ota_transmits_data()
    assert progress != '0'
    assert total == ZigbeeCIConstants.ota_total_package
    progress, total = client.get_ota_receives_data()
    assert progress != '0'
    assert total == ZigbeeCIConstants.ota_total_package


# Case 7: Zigbee light sleep test
@pytest.mark.order(7)
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all, config', [(2, sleep_pytest_build_dir, 'y', 'enable_debug'), ], indirect=True, )
@generic_chips_zigbee_test
def test_zb_sleep(dut, count, app_path, erase_all):
    cli = CliDevice(dut[0])
    sleep_device = ExampleDevice(dut[1])
    cli.create_coordinator('on_off_light', network_type='c')
    cli.check_response(MatchPattern.form_success, timeout=5)
    cli.network_open()
    cli.get_device_network_info(coordinator=True)
    sleep_device.get_example_device_network_info(coordinator=False, timeout=20)
    Common.check_network_matched(cli.network_info, sleep_device.network_info)
    sleep_device.check_response(MatchPattern.sleep_pd_top, timeout=22)
    sleep_device.check_response(MatchPattern.sleep_pd_modem)
    Common.check_connection_status(cli, sleep_device.short_address)


# Case 8: Zigbee touchlink test
@pytest.mark.order(8)
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all', [(2, touchlink_pytest_build_dir, 'y'), ], indirect=True, )
@generic_chips_zigbee_test
def test_zb_touch_link(dut, count, app_path, erase_all):
    target = ExampleDevice(dut[0])
    initiator = ExampleDevice(dut[1])
    # check network connect and return network info
    target.get_example_device_network_info(coordinator=False)
    initiator.get_example_device_network_info(coordinator=False)
    Common.check_network_matched(target.network_info, initiator.network_info)
    initiator.check_response(MatchPattern.bound_ha_light)


# Case 9: Zigbee gateway test
@pytest.mark.order(9)
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, target, erase_all', [(2, gateway_pytest_build_dir, 'esp32h2|esp32s3', 'y'), ],
                         indirect=True, )
@dual_chip_gateway
def test_zb_gateway(dut, count, app_path, target):
    gateway_device = ExampleDevice(dut[1])
    cli = CliDevice(dut[0])
    gateway_device.check_response(MatchPattern.update_the_rcp_version, timeout=30)
    gateway_device.check_response(MatchPattern.initialize_zigbee_stack, timeout=20)
    gateway_device.get_example_device_network_info(coordinator=True)
    gateway_device.check_response(MatchPattern.network_open, timeout=10)
    cli.create_router('on_off_light', network_type='c')
    cli.get_device_network_info(coordinator=False)
    logging.info(f"gateway_info:{gateway_device.network_info}")
    Common.check_network_matched(gateway_device.network_info, cli.network_info)
    Common.check_connection_status(cli, gateway_device.short_address)


# Case 10: Zigbee deep sleep test
@pytest.mark.order(10)
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all', [(2, deep_sleep_pytest_build_dir, 'y'), ], indirect=True, )
@generic_chips_zigbee_test
def test_zb_deep_sleep(dut, count, app_path, erase_all):
    cli = CliDevice(dut[0])
    sleep_device = ExampleDevice(dut[1])
    cli.create_coordinator('on_off_switch', network_type='c')
    cli.check_response(MatchPattern.form_success, timeout=5)
    cli.network_open()
    cli.get_device_network_info(coordinator=True)
    sleep_device.get_example_device_network_info(coordinator=False, timeout=60)
    Common.check_network_matched(cli.network_info, sleep_device.network_info)
    Common.check_connection_status(cli, sleep_device.short_address)

    sleep_device.check_response(MatchPattern.enter_deep_sleep, timeout=10)
    clean_buffer(cli.dut)
    cli.check_response(fr'New device commissioned or rejoined \(short: {sleep_device.short_address}', timeout=21)
    Common.check_connection_status(cli, sleep_device.short_address)


# Case 11: Zigbee HA dimmable light test
@pytest.mark.order(11)
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all', [(2, ha_dimmable_light_pytest_build_dir, 'y'), ], indirect=True, )
@generic_chips_zigbee_test
def test_zb_ha_dimmable_light(dut, count, app_path, erase_all):
    ha_dimmable_light_device = ExampleDevice(dut[0])
    ha_dimmable_switch_device = ExampleDevice(dut[1])
    ha_dimmable_light_device.get_example_device_network_info(coordinator=True, timeout=20)
    ha_dimmable_switch_device.get_example_device_network_info(coordinator=False, timeout=30)
    Common.check_network_matched(ha_dimmable_light_device.network_info, ha_dimmable_switch_device.network_info)
    ha_dimmable_switch_device.check_response(MatchPattern.bound_ha_dimmable_light)


# Case 12: Zigbee HA on off light test
@pytest.mark.order(12)
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all', [(2, ha_on_off_light_pytest_build_dir, 'y'), ], indirect=True, )
@generic_chips_zigbee_test
def test_zb_ha_on_off_light(dut, count, app_path, erase_all):
    ha_on_off_light_device = ExampleDevice(dut[0])
    ha_on_off_switch_device = ExampleDevice(dut[1])
    ha_on_off_light_device.get_example_device_network_info(coordinator=True, timeout=20)
    ha_on_off_switch_device.get_example_device_network_info(coordinator=False, timeout=40)
    Common.check_network_matched(ha_on_off_light_device.network_info, ha_on_off_switch_device.network_info)
    ha_on_off_switch_device.check_response(MatchPattern.bound_ha_light)


# Case 13: Zigbee HA thermostat test
@pytest.mark.order(13)
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all', [(2, ha_thermostat_pytest_build_dir, 'y'), ], indirect=True, )
@generic_chips_zigbee_test
def test_zb_ha_thermostat(dut, count, app_path, erase_all):
    ha_thermostat_device = ExampleDevice(dut[0])
    ha_temperature_sensor_device = ExampleDevice(dut[1])
    ha_thermostat_device.get_example_device_network_info(coordinator=True, timeout=20)
    ha_temperature_sensor_device.get_example_device_network_info(coordinator=False, timeout=30)
    Common.check_network_matched(ha_thermostat_device.network_info, ha_temperature_sensor_device.network_info)
    clean_buffer(ha_thermostat_device.dut)
    clean_buffer(ha_temperature_sensor_device.dut)
    # config report max interval is 10 seconds
    ha_thermostat_device.check_response(MatchPattern.temperature_sensor_measured_value, timeout=15)
    ha_temperature_sensor_device.check_response(MatchPattern.receive_default_rsp, timeout=15)
