# SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
import pathlib
import time
import pytest
from constants import ZigbeeCIConstants
from functools import wraps

BASIC_CURRENT_DIR_CLIENT = str(pathlib.Path(__file__).parent) + '/esp_zigbee_customized_devices/customized_client'
BASIC_CURRENT_DIR_SERVER = str(pathlib.Path(__file__).parent) + '/esp_zigbee_customized_devices/customized_server'
basic_pytest_build_dir = BASIC_CURRENT_DIR_CLIENT + '|' + BASIC_CURRENT_DIR_SERVER

OTA_CURRENT_DIR_CLIENT = str(pathlib.Path(__file__).parent) + '/esp_zigbee_ota/ota_client'
OTA_CURRENT_DIR_SERVER = str(pathlib.Path(__file__).parent) + '/esp_zigbee_ota/ota_server'
ota_pytest_build_dir = OTA_CURRENT_DIR_CLIENT + '|' + OTA_CURRENT_DIR_SERVER

CLI_CURRENT_DIR_CLIENT = str(pathlib.Path(__file__).parent) + '/esp_zigbee_cli'
SLEEP_CURRENT_DIR_SERVER = str(pathlib.Path(__file__).parent) + '/esp_zigbee_sleep/light_sleep'
sleep_pytest_build_dir = CLI_CURRENT_DIR_CLIENT + '|' + SLEEP_CURRENT_DIR_SERVER

SWITCH_CURRENT_DIR_SERVER = str(pathlib.Path(__file__).parent) + '/esp_zigbee_touchlink/touchlink_switch'
LIGHT_CURRENT_DIR_CLIENT = str(pathlib.Path(__file__).parent) + '/esp_zigbee_touchlink/touchlink_light'
touchlink_pytest_build_dir = SWITCH_CURRENT_DIR_SERVER + '|' + LIGHT_CURRENT_DIR_CLIENT

HA_CURRENT_DIR_SERVER = str(pathlib.Path(__file__).parent) + '/esp_zigbee_cli'
GATEWAY_CURRENT_DIR_CLIENT = str(pathlib.Path(__file__).parent) + '/esp_zigbee_gateway'
gateway_pytest_build_dir = HA_CURRENT_DIR_SERVER + '|' + GATEWAY_CURRENT_DIR_CLIENT

DEEP_SLEEP_CURRENT_DIR_SERVER = str(pathlib.Path(__file__).parent) + '/esp_zigbee_sleep/deep_sleep'
deep_sleep_pytest_build_dir = CLI_CURRENT_DIR_CLIENT + '|' + DEEP_SLEEP_CURRENT_DIR_SERVER


def expect_decorator(pattern):
    def decorator(func):
        @wraps(func)
        def wrapper(dut, *args, **kwargs):
            match_result = dut.expect(pattern, timeout=5)
            if not match_result:
                assert False, f"No match found for pattern: {pattern}"
            matched_groups = match_result.groups()
            if not matched_groups:
                assert False, f"No groups found in match for pattern: {pattern}"
            decoded_results = tuple(match.decode() if isinstance(match, bytes) else match for match in matched_groups)
            return func(decoded_results, *args, **kwargs)

        return wrapper

    return decorator


@expect_decorator(r"Extended PAN ID: ((?:[0-9a-fA-F]{2}:){7}[0-9a-fA-F]{2}), "
                  r"PAN ID: (0x[a-fA-F0-9]{4}), "
                  r"Channel:(\d+), "
                  r"Short Address: (0x[a-fA-F0-9]{4})")
def get_formed_network_parameters(matched_values):
    extended_pan_id, pan_id, channel, short_address = matched_values
    print(f"Extended PAN ID: {extended_pan_id}, PAN ID: {pan_id},"
          f" Channel: {channel}, Short Address: {short_address}")
    return matched_values


@expect_decorator(r"Match desc response: status\((\d+)\),\s*address\(0x([0-9a-fA-F]+)\),\s*endpoint\((\d+)\)")
def get_match_desc_response_values(matched_values):
    status_value, address_value, endpoint_value = matched_values
    print(f"Status: {status_value}, Address: {address_value}, Endpoint: {endpoint_value}")
    return matched_values


@expect_decorator(r"OTA version: (0x[0-9a-fA-F]+), image type: (0x[0-9a-fA-F]+), manufacturer code: (\d+)")
def get_ota_information(matched_values):
    ota_version, image_type, manufacturer_code = matched_values
    print(f"OTA Version: {ota_version}, Image Type: {image_type}, Manufacturer Code: {manufacturer_code}")
    return matched_values


@expect_decorator(r"data from 0x0 to (0x[0-9a-fA-F]+): progress \[(\d+)/(\d+)\]")
def get_ota_transmits_data(matched_values):
    client_address, progress, total = matched_values
    print(f"OTA client_address: {client_address}, progress: {progress}, total: {total}")
    return matched_values


@expect_decorator(r"receives data: progress \[(\d+)/(\d+)\]")
def get_ota_receives_data(matched_values):
    progress, total = matched_values
    print(f"progress: {progress}, total: {total}")
    return matched_values


@expect_decorator(r'status\((\d+)\) and endpoint count\((\d+)\)')
def get_active_endpoint_response_values(matched_values):
    status_value, endpoint_count_value = matched_values
    print(f"Status: {status_value}, Endpoint Count: {endpoint_count_value}")
    return matched_values


@expect_decorator(r"status\((\d+)\), "
                  r"device_id\((\d+)\), "
                  r"app_version\((\d+)\), "
                  r"profile_id\(0x([0-9a-fA-F]+)\), "
                  r"endpoint_ID\((\d+)\)")
def get_simple_desc_response_values(matched_values):
    status_value, device_id_value, app_version_value, profile_id_value, endpoint_id_value = matched_values
    print(f"Status: {status_value}, Device ID: {device_id_value}, App Version: {app_version_value}, "
          f"Profile ID: {profile_id_value}, Endpoint ID: {endpoint_id_value}")
    return matched_values


@expect_decorator(r"Bind response from address\(0x([0-9a-fA-F]+)\), endpoint\((\d+)\) with status\((\d+)\)")
def get_bind_response_values(matched_values):
    address_value, endpoint_value, status_value = matched_values
    print(f"Address: {address_value}, Endpoint: {endpoint_value}, Status: {status_value}")
    return matched_values


@expect_decorator(r"address\(0x([0-9a-fA-F]+)\) src endpoint\((\d+)\) "
                  r"to dst endpoint\((\d+)\) cluster\(0x([0-9a-fA-F]+)\)")
def get_received_report_values(matched_values):
    address, src_endpoint, dst_endpoint, cluster = matched_values
    print(f"Address: {address}, Source Endpoint: {src_endpoint}, Destination Endpoint: {dst_endpoint}, "
          f"Cluster: {cluster}")
    return matched_values


def check_zigbee_network_status(client, server, sleep_time=10):
    extended_pan_id_server, pan_id_server, channel_server, short_address_server = get_formed_network_parameters(server)

    assert extended_pan_id_server.strip('0:') != ''
    assert pan_id_server != ZigbeeCIConstants.default_id
    assert ZigbeeCIConstants.channel_min <= int(channel_server) <= ZigbeeCIConstants.channel_max
    assert short_address_server == ZigbeeCIConstants.default_id

    # sleep to wait client join the network
    time.sleep(sleep_time)
    extended_pan_id_client, pan_id_client, channel_client, short_address_client = get_formed_network_parameters(client)
    assert extended_pan_id_client.strip('0:') != ''
    assert pan_id_client != ZigbeeCIConstants.default_id
    assert ZigbeeCIConstants.channel_min <= int(channel_client) <= ZigbeeCIConstants.channel_max
    assert short_address_client != ZigbeeCIConstants.default_id

    assert extended_pan_id_client == extended_pan_id_server
    assert pan_id_client == pan_id_server
    assert channel_client == channel_server
    time.sleep(0.5)
    server.expect(r'New device commissioned or rejoined', timeout=5)
    return {
        'server': {
            'extended_pan_id': extended_pan_id_server,
            'pan_id': pan_id_server,
            'channel': channel_server,
            'short_address': short_address_server
        },
        'client': {
            'extended_pan_id': extended_pan_id_client,
            'pan_id': pan_id_client,
            'channel': channel_client,
            'short_address': short_address_client
        }
    }


def check_zigbee_sleep_intervals(dut):
    sleep_pattern = r'ESP_ZB_SLEEP: Zigbee can sleep'
    last_time = None
    start_time = time.time()
    while time.time() - start_time < 10:
        match = dut.expect(sleep_pattern, timeout=5)
        current_time = time.time()
        if match is not None and last_time is not None:
            interval = current_time - last_time
            assert interval <= 5, f"Interval between 'Zigbee can sleep' entries exceeds 5 seconds: {interval} " \
                                  f"seconds"
        last_time = current_time


def coordinator_init_and_form_network(dut):
    dut.write('bdb -r zc')
    dut.expect('Coordinator role set', timeout=6)
    dut.write(f'bdb -c {ZigbeeCIConstants.channel}')
    dut.expect(f'Setting channel to {ZigbeeCIConstants.channel}', timeout=6)
    dut.write('bdb -i policy disable')
    dut.expect('Done', timeout=6)
    dut.write('bdb -s')
    dut.expect('Started coordinator', timeout=6)
    time.sleep(2)
    dut.write('bdb -a init')
    time.sleep(1)
    dut.write('bdb -a form')
    time.sleep(2)


def coordinator_operate_router(dut, hlp_dut, device_short_address):
    dut.write(f'zcl -c {device_short_address} 10 0x0006 0x01')
    time.sleep(5)
    hlp_dut.expect('Light sets to On')
    dut.write(f'zcl -a read {device_short_address} 10 0x0006 0x0104 0 ')
    time.sleep(5)
    dut.expect('ID: 0 Type: 0x10 Value: True')
    dut.write(f'zcl -c {device_short_address} 10 0x0006 0x00')
    time.sleep(5)
    hlp_dut.expect('Light sets to Off')
    dut.write(f'zcl -a read {device_short_address} 10 0x0006 0x0104 0 ')
    time.sleep(5)
    dut.expect('ID: 0 Type: 0x10 Value: False')


# Case 5: Zigbee network connection basic test
@pytest.mark.order(5)
@pytest.mark.esp32h2
@pytest.mark.esp32c6
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all', [(2, basic_pytest_build_dir, 'y'), ], indirect=True, )
@pytest.mark.usefixtures('teardown_fixture')
def test_zb_basic(dut, count, app_path, erase_all):
    client = dut[0]
    server = dut[1]

    check_zigbee_network_status(client, server)

    status_value, address_value, endpoint_value = get_match_desc_response_values(client)
    assert status_value == address_value == '0'
    assert endpoint_value == '10'

    status_value, endpoint_count_value = get_active_endpoint_response_values(client)
    assert status_value == '0'
    # release/v1.0.8 change endpoint_count to 2
    assert endpoint_count_value == '2'

    status_value, device_id_value, app_version_value, profile_id_value, endpoint_id_value = \
        get_simple_desc_response_values(client)

    assert status_value == app_version_value == '0'
    assert device_id_value == '256'
    assert profile_id_value == '104'
    assert endpoint_id_value == '10'

    address_value, endpoint_value, status_value = get_bind_response_values(client)
    assert address_value == status_value == '0'
    assert endpoint_value == '1'

    address, src_endpoint, dst_endpoint, cluster = get_received_report_values(client)
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
    client = dut[0]
    server = dut[1]

    check_zigbee_network_status(client, server)

    assert (ZigbeeCIConstants.default_id != str(server.expect(r'OTA client address: (0x[0-9a-fA-F]+)',
                                                              timeout=3)[1].decode()))
    ota_version, image_type, manufacturer_code = get_ota_information(server)
    assert ota_version == ZigbeeCIConstants.ota_version
    assert image_type == ZigbeeCIConstants.image_type
    assert manufacturer_code == ZigbeeCIConstants.manufacturer_code
    client_address, progress, total = get_ota_transmits_data(server)
    assert client_address != '0x0'
    assert progress != '0'
    assert total == ZigbeeCIConstants.ota_total_package

    progress, total = get_ota_receives_data(client)
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
    cli = dut[0]
    sleep_device = dut[1]
    coordinator_init_and_form_network(cli)
    network_params = check_zigbee_network_status(sleep_device, cli)
    sleep_device_short_address = network_params['client']['short_address']
    check_zigbee_sleep_intervals(sleep_device)
    coordinator_operate_router(cli, sleep_device, sleep_device_short_address)


# Case 8: Zigbee touchlink test
@pytest.mark.order(8)
@pytest.mark.esp32h2
@pytest.mark.esp32c6
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all', [(2, touchlink_pytest_build_dir, 'y'), ], indirect=True, )
@pytest.mark.usefixtures('teardown_fixture')
def test_zb_touch_link(dut, count, app_path, erase_all):
    switch = dut[0]
    light = dut[1]
    switch.expect('Scanning as a Touchlink initiator...')
    time.sleep(5)
    light.expect('Touchlink target is ready, awaiting commissioning')
    extended_pan_id_light, pan_id_light, channel_light, short_address_light = get_formed_network_parameters(light)
    extended_pan_id_switch, pan_id_switch, channel_switch, short_address_switch = get_formed_network_parameters(switch)
    assert extended_pan_id_light == extended_pan_id_switch
    assert pan_id_light == pan_id_switch
    assert channel_light == channel_switch
    time.sleep(5)
    light.expect('Touchlink target commissioning finished')
    switch.expect('Bound successfully!')


# Case 9: Zigbee gateway test
@pytest.mark.order(9)
@pytest.mark.esp32s3
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, target', [(2, gateway_pytest_build_dir, 'esp32h2|esp32s3'), ],
                         indirect=True, )
@pytest.mark.usefixtures('teardown_fixture')
def test_zb_gateway(dut, count, app_path, target):
    gateway_device = dut[1]
    cli_device = dut[0]
    # add sleep time to wait rcp update ready
    time.sleep(15)
    gateway_device.expect(r'\*\*\* MATCH VERSION! \*\*\*', timeout=6)
    # add sleep time to wait gateway Network steering
    time.sleep(10)
    extended_pan_id_server, pan_id_server, channel_server, short_address_server = \
        get_formed_network_parameters(gateway_device)

    assert extended_pan_id_server.strip('0:') != ''
    assert pan_id_server != ZigbeeCIConstants.default_id
    assert ZigbeeCIConstants.channel_min <= int(channel_server) <= ZigbeeCIConstants.channel_max
    assert short_address_server == ZigbeeCIConstants.default_id

    cli_device.write(f'bdb -c {channel_server}')
    cli_device.write('bdb -r zr')
    cli_device.expect('Router role set')
    cli_device.write('bdb -s')
    cli_device.write('bdb -a init')
    cli_device.expect('Device started up in  factory-reset mode')

    for attempt in range(3):
        try:
            cli_device.write('bdb -a steering')
            short_address_cli_get_by_gateway = gateway_device.expect(r"short: (0x[a-fA-F0-9]{4})")[1].decode()
            time.sleep(2)
            cli_device.expect('Joined network successfully')
            cli_device.write('zdo -s')
            short_address_cli = cli_device.expect(r"short addr:(0x[a-fA-F0-9]{4})", timeout=5)[1].decode()
            print(f'short_address_cli_get_by_gateway: {short_address_cli_get_by_gateway}')
            print(f'short_address_cli: {short_address_cli}')
            assert short_address_cli_get_by_gateway == short_address_cli
            cli_device.write('bdb -p get')
            pan_id_cli = cli_device.expect(r"get panid: (0x[a-fA-F0-9]{4})")[1].decode()
            assert pan_id_cli == pan_id_server
            cli_device.write('bdb -c get')
            channel_cli = cli_device.expect(r"Primary channel\(s\): (\d+)")[1].decode()
            assert channel_cli == channel_server
            break
        except Exception as e:
            print(f"An error occurred on attempt {attempt + 1}: {e}. Retrying...")


# Case 10: Zigbee deep sleep test
@pytest.mark.order(10)
@pytest.mark.esp32h2
@pytest.mark.esp32c6
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize('count, app_path, erase_all', [(2, deep_sleep_pytest_build_dir, 'y'), ], indirect=True, )
@pytest.mark.usefixtures('teardown_fixture')
def test_zb_deep_sleep(dut, count, app_path, erase_all):
    cli = dut[0]
    sleep_device = dut[1]
    sleep_device.expect('Not a deep sleep reset')
    sleep_device.expect('Enabling timer wakeup')
    coordinator_init_and_form_network(cli)
    network_params = check_zigbee_network_status(sleep_device, cli)
    sleep_device_short_address = network_params['client']['short_address']
    sleep_device.expect('Start one-shot timer for 5s to enter the deep sleep')
    sleep_device.expect('Enter deep sleep')
    for _ in range(2):
        sleep_device.expect('0x5 \(SLEEP_WAKEUP\)')
        sleep_device.expect('Enabling timer wakeup')
        cli.expect(f'New device commissioned or rejoined \(short: {sleep_device_short_address}')
        time.sleep(5)


