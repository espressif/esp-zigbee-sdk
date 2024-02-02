# SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD

# SPDX-License-Identifier: CC0-1.0

import pathlib
import pytest
import time
import pexpect
from typing import Tuple
from pytest_embedded import Dut

CURRENT_DIR_CLI = str(pathlib.Path(__file__).parent) + '/esp_zigbee_cli'
CURRENT_DIR_COLOR_DIMM_LIGHT = str(pathlib.Path(__file__).parent) + '/esp_zigbee_HA_sample/HA_color_dimmable_light'
pytest_build_dir = CURRENT_DIR_CLI + '|' + CURRENT_DIR_COLOR_DIMM_LIGHT


# pre-requisite to config Zigbee network
def config_zigbee_network(cli: Dut, light: Dut) -> Tuple[bool, str]:
    # set channel to default 13
    channel_number = 13
    time.sleep(3)
    cli.expect('Command history disabled', timeout=5)
    cli.write('bdb -r zc')
    channel_set = 'bdb -c ' + str(channel_number)
    cli.write(channel_set)
    time.sleep(1)
    cli.write('bdb -c get')
    time.sleep(1)
    cli.expect(r'channel\(s\): ' + str(channel_number), timeout=3)
    cli.write('bdb -s')
    cli.write('bdb -i policy disable')
    time.sleep(1)
    cli.write('bdb -a init')
    time.sleep(1)
    cli.write('bdb -a form')
    time.sleep(2)
    cli.expect('ESP_ZB_CLI: Formed network successfully', timeout=6)
    cli.write('bdb -e get')
    # get the cli expanid (same as ieee address)
    cli_node_expanid = cli.expect(r'extpanid: 0x([a-z0-9]+:?)', timeout=2)[1].decode()
    # get the light node network address
    light_nwk_addr = cli.expect(r'New device commissioned or rejoined \(short: 0x([a-z0-9]+)', timeout=30)[1].decode()
    light.expect('ESP_ZB_COLOR_DIMM_LIGHT: Joined network successfully', timeout=20)
    light_node_got_expanid = light.expect(r'PAN ID: (([a-z0-9]{2}:?){8})', timeout=3)[1].decode()
    light_node_got_expanid = light_node_got_expanid.replace(":", "")
    # make sure the light node join the network that cli formed (same expanid)
    if light_node_got_expanid == cli_node_expanid:
        return True, str(light_nwk_addr)
    return False, ''


# Case 1: Zigbee network connection
@pytest.mark.order(1)
@pytest.mark.esp32h2
@pytest.mark.esp32c6
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize(
    'count, app_path, erase_all', [
        (2, pytest_build_dir, 'y'),
    ],
    indirect=True,
)
@pytest.mark.usefixtures('teardown_fixture')
def test_zb_cli_zc_connection(dut: Tuple[Dut, Dut]) -> None:
    light = dut[1]
    cli = dut[0]
    result = config_zigbee_network(cli, light)
    light_nwk_addr = str(result[1])
    assert bool(result[0])
    cli.write('zdo -i ' + light_nwk_addr)
    light_node_ieee_address = cli.expect(r'([a-z0-9]{16})', timeout=5)[1].decode()
    cli.write('zdo -n ' + str(light_node_ieee_address))
    got_nwk_address = cli.expect(r'nwk_addr:([a-z0-9]{4})', timeout=5)[1].decode()
    # make sure the light network address align with its own ieee address
    assert (light_nwk_addr == str(got_nwk_address))


# #Case 2: Zigbee network finding-binding
@pytest.mark.order(2)
@pytest.mark.esp32h2
@pytest.mark.esp32c6
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize(
    'count, app_path, erase_all', [
        (2, pytest_build_dir, 'y'),
    ],
    indirect=True,
)
@pytest.mark.usefixtures('teardown_fixture')
def test_zb_cli_zc_finding_binding(dut: Tuple[Dut, Dut]) -> None:
    light = dut[1]
    cli = dut[0]
    result = config_zigbee_network(cli, light)
    light_nwk_addr = str(result[1])
    assert bool(result[0])
    # get active ep
    cli.write('zdo -a 0x' + light_nwk_addr)
    assert (light_nwk_addr == str(cli.expect(r'src_addr=([a-z0-9]{4})', timeout=3)[1].decode()))
    light_endpoint = cli.expect(r'ep=([0-9]+)', timeout=3)[1].decode()
    # simple descriptor request
    cli.write('zdo -c 0x' + light_nwk_addr + ' ' + str(light_endpoint))
    cli.expect('in clusters|out clusters', timeout=3)
    # find on_off (cluster id =0x0006) level control (cluster id =0x0008) color control (cluster id =0x0300)
    cli.write(
        'zdo -m ' + light_nwk_addr + ' ' + light_nwk_addr + ' ' + '0x0104 ' + '3 ' + '0x0006 ' + '0x0008 ' + '0x0300 ' + '0')
    assert (light_nwk_addr == str(cli.expect(r'src_addr=([a-z0-9]{4})', timeout=3)[1].decode()))
    assert (light_endpoint == str(cli.expect(r'ep=([0-9]*)', timeout=3)[1].decode()))
    # get ieee_address of the light
    cli.write('zdo -i ' + light_nwk_addr)
    light_node_ieee_address = str(cli.expect(r'([a-z0-9]{16})', timeout=5)[1].decode())
    # bind (bind identify cluster 0x0003 remote(client) to local(server))
    cli.write('zdo -e')
    cli_node_ieee_address = str(cli.expect(r'([a-z0-9]{16})', timeout=2)[1].decode())
    cli.write('zdo -a 0x0000')
    cli_endpoint = str(cli.expect(r'ep=([0-9]+)', timeout=2)[1].decode())
    cli.write(
        'zdo -b on ' + light_node_ieee_address + ' ' + light_endpoint + ' ' + cli_node_ieee_address + ' ' + cli_endpoint + ' 0x0003 ' + light_nwk_addr)
    cli.expect('Done', timeout=3)


# #Case 3: Zigbee network ZCL command
@pytest.mark.order(3)
@pytest.mark.esp32h2
@pytest.mark.esp32c6
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize(
    'count, app_path, erase_all', [
        (2, pytest_build_dir, 'y'),
    ],
    indirect=True,
)
@pytest.mark.usefixtures('teardown_fixture')
def test_zb_cli_zc_ZCL_command(dut: Tuple[Dut, Dut]) -> None:
    light = dut[1]
    cli = dut[0]
    result = config_zigbee_network(cli, light)
    light_nwk_addr = str(result[1])
    assert bool(result[0])
    cli.write('zdo -a 0x' + light_nwk_addr)
    assert (light_nwk_addr == str(cli.expect(r'src_addr=([a-z0-9]{4})', timeout=3)[1].decode()))
    light_endpoint = cli.expect(r'ep=([0-9]+)', timeout=3)[1].decode()

    #################### ZCL command (on-off 0x0006 cluster) ####################
    light_on = 1
    light_off = 0
    # On command
    cli.write('zcl -c ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0006 01')
    cli.expect('Done', timeout=3)
    time.sleep(2)
    # read on_off attribute
    cli.write('zcl -a read ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0006 0x0104 0')
    time.sleep(2)
    assert str(bool(light_on)) == cli.expect(r'Value: (\w+)', timeout=3)[1].decode()
    # Off command
    time.sleep(2)
    cli.write('zcl -c ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0006 00')
    cli.expect('Done', timeout=3)
    time.sleep(2)
    # read on_off attribute
    cli.write('zcl -a read ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0006 0x0104 0')
    time.sleep(2)
    assert str(bool(light_off)) == cli.expect(r'Value: (\w+)', timeout=3)[1].decode()
    # toggle command
    time.sleep(2)
    cli.write('zcl -c ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0006 02')
    cli.expect('Done', timeout=3)
    time.sleep(2)
    # read on_off attribute
    cli.write('zcl -a read ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0006 0x0104 0')
    assert str(bool(light_on)) == cli.expect(r'Value: (\w+)', timeout=3)[1].decode()

    ################### ZCL command (level-control 0x0008 cluster) ####################
    light_lvl = 5
    # Move to level(with On/Off) command
    time.sleep(2)
    str_length = str(len(light.expect(pexpect.TIMEOUT, timeout=0.1)))
    light.expect(r'[\s\S]{%s}' % str(str_length), timeout=10)
    cli.write('zcl -c ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0008 04 profile 0x0104 payload 05ffff')
    assert str(light_lvl) == light.expect(r'Light level changes to ([0-9])', timeout=3)[1].decode()
    cli.expect('Done', timeout=3)
    # read level_control attribute
    cli.write('zcl -a read ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0008 0x0104 0')
    assert str(light_lvl) == cli.expect(r'Value: (\d+)', timeout=3)[1].decode()
    cli.expect('Done', timeout=3)
    # Move (with On/Off) command
    time.sleep(2)
    cli.write('zcl -c ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0008 05 profile 0x0104 payload 0105')
    time.sleep(2)
    cli.expect('Done', timeout=3)
    # read level_control attribute
    cli.write('zcl -a read ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0008 0x0104 0')
    time.sleep(2)
    cli.expect('Done', timeout=3)
    # Step (with On/Off) command
    time.sleep(2)
    cli.write('zcl -c ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0008 06 profile 0x0104 payload 0005ffff')
    cli.expect('Done', timeout=3)
    # read level_control attribute
    cli.write('zcl -a read ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0008 0x0104 0')
    cli.expect('Done', timeout=3)
    # Stop command
    time.sleep(2)
    cli.write('zcl -c ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0008 07')
    cli.expect('Done', timeout=3)
    # read level_control attribute
    cli.write('zcl -a read ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0008 0x0104 0')
    cli.expect('Done', timeout=3)

    #################### ZCL command (color-control 0x0300 cluster) ####################
    light_color_x = 12440
    light_color_y = 12857
    # Move to color command
    time.sleep(2)
    cli.write('zcl -c ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0300 07 profile 0x0104 payload 983039320000')
    light.expect(r'Light color x changes to 0x', timeout=3)
    light.expect(r'Light color y changes to 0x', timeout=3)
    time.sleep(0.5)
    assert hex(light_color_x) == light.expect(r'Light color x changes to (0x\w+)', timeout=3)[1].decode()
    assert hex(light_color_y) == light.expect(r'Light color y changes to (0x\w+)', timeout=3)[1].decode()
    cli.expect('Done', timeout=3)
    # read color_control_x attribute
    cli.write('zcl -a read ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0300 0x0104 3')
    assert str(light_color_x) == cli.expect(r'Value: (\d+)', timeout=3)[1].decode()
    cli.expect('Done', timeout=3)
    # read color_control_y attribute
    cli.write('zcl -a read ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0300 0x0104 4')
    assert str(light_color_y) == cli.expect(r'Value: (\d+)', timeout=3)[1].decode()
    cli.expect('Done', timeout=3)
    # Move color command
    time.sleep(2)
    cli.write('zcl -c ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0300 08 profile 0x0104 payload 01000100')
    cli.expect('Done', timeout=3)
    # read color_control_x attribute
    cli.write('zcl -a read ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0300 0x0104 3')
    cli.expect('Done', timeout=3)
    # read color_control_y attribute
    cli.write('zcl -a read ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0300 0x0104 4')
    cli.expect('Done', timeout=3)
    # Step color command
    time.sleep(2)
    cli.write('zcl -c ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0300 09 profile 0x0104 payload 010001000100')
    cli.expect('Done', timeout=3)
    # read color_control_x attribute
    cli.write('zcl -a read ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0300 0x0104 3')
    cli.expect('Done', timeout=3)
    # read color_control_y attribute
    cli.write('zcl -a read ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0300 0x0104 4')
    cli.expect('Done', timeout=3)
    # Stop move step command
    time.sleep(2)
    cli.write('zcl -c ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0300 47')
    cli.expect('Done', timeout=3)
    # read color_control_x attribute
    cli.write('zcl -a read ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0300 0x0104 3')
    cli.expect('Done', timeout=3)
    # read color_control_y attribute
    cli.write('zcl -a read ' + light_nwk_addr + ' ' + light_endpoint + ' 0x0300 0x0104 4')
    cli.expect('Done', timeout=3)


# #Case 4: Zigbee network leaving
@pytest.mark.order(4)
@pytest.mark.esp32h2
@pytest.mark.esp32c6
@pytest.mark.zigbee_multi_dut
@pytest.mark.parametrize(
    'count, app_path, erase_all', [
        (2, pytest_build_dir, 'y'),
    ],
    indirect=True,
)
@pytest.mark.usefixtures('teardown_fixture')
def test_zb_cli_zc_check_leaving(dut: Tuple[Dut, Dut]) -> None:
    light = dut[1]
    cli = dut[0]
    result = config_zigbee_network(cli, light)
    light_nwk_addr = str(result[1])
    assert bool(result[0])
    cli.write('zdo -l 0x' + light_nwk_addr)
    assert (light_nwk_addr == str(cli.expect(r'leaving network: 0x([a-z0-9]{4})', timeout=3)[1].decode()))
    cli.write('zdo -l 0x0000')
    cli.expect('leave network, status', timeout=3)
