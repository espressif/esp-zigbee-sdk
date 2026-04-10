# SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD

# SPDX-License-Identifier: CC0-1.0

import time
import random
from constants import ZigbeeCIConstants
from functools import wraps
import logging
from constants import MatchPattern
import re
import pytest
import pexpect
from pytest_embedded_idf.dut import IdfDut

logging.basicConfig(level=logging.INFO)

def clean_buffer(dut: IdfDut) -> None:
    str_length = str(len(dut.expect(pexpect.TIMEOUT, timeout=0.1)))
    dut.expect(rf'[\s\S]{{{str_length}}}', timeout=10)



def mark_chips(*marks):
    def decorator(func):
        # add chip marks
        for mark in marks:
            func = mark(func)
        # add teardown_fixture
        func = pytest.mark.usefixtures("teardown_fixture")(func)
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        return wrapper
    return decorator

generic_chips_zigbee_test = mark_chips(
    pytest.mark.esp32h2,
    pytest.mark.esp32c6,
    pytest.mark.esp32c5,
)

single_chip_gateway = mark_chips(
    pytest.mark.esp32c6,
    pytest.mark.esp32c5,
)

dual_chip_gateway = mark_chips(
    pytest.mark.esp32s3,
)

ota_chip_test = mark_chips(
    pytest.mark.esp32h2,
)

def expect_decorator(pattern, timeout=5):
    def decorator(func):
        @wraps(func)
        def wrapper(self, *args, **kwargs):
            logs = kwargs.pop("logs", None)
            expect_timeout = kwargs.pop("expect_timeout", timeout)
            if logs is not None:
                match_result = re.compile(pattern).search(logs)
            else:
                match_result = self.dut.expect(pattern, timeout=expect_timeout)
            if not match_result:
                assert False, f"No match found for pattern: {pattern}"
            matched_groups = match_result.groups()
            if not matched_groups:
                assert False, f"No groups found in match for pattern: {pattern}"
            decoded_results = tuple(
                match.decode() if isinstance(match, bytes) else match for match in matched_groups)
            return func(self, decoded_results, *args, **kwargs)

        return wrapper

    return decorator


class ExampleDevice:

    def __init__(self, dut):
        self.dut = dut
        self.channel = ZigbeeCIConstants.channel
        self.short_address = None
        self.pan_id = None
        self.extended_pan_id = None
        self.network_info = None

    # Matches: PAN ID(0x%04hx, EXT: 0x%llx), Channel(%d), Short Address(0x%04hx)
    @expect_decorator(
        r"PAN ID\((0x[a-fA-F0-9]{4}),\s*EXT:\s*(0x[a-fA-F0-9]+)\),\s*"
        r"Channel\((\d+)\),\s*Short Address\((0x[a-fA-F0-9]{4})\)"
    )
    def get_formed_network_parameters(self, matched_values, expect_timeout=15):
        self.pan_id, self.extended_pan_id, self.channel, self.short_address = matched_values
        logging.info(
            f"Extended PAN ID: {self.extended_pan_id}, PAN ID: {self.pan_id},"
            f" Channel: {self.channel}, Short Address: {self.short_address}"
        )
        return self.extended_pan_id, self.pan_id, self.channel, self.short_address

    @expect_decorator(r"Match desc response: status\((\d+)\),\s*address\(0x([0-9a-fA-F]+)\),\s*endpoint\((\d+)\)")
    def get_match_desc_response_values(self, matched_values):
        status_value, address_value, endpoint_value = matched_values
        logging.info(f"Status: {status_value}, Address: {address_value}, Endpoint: {endpoint_value}")
        return matched_values

    @expect_decorator(r"manuf_code=(0x[0-9a-fA-F]+), image_type=(0x[0-9a-fA-F]+), file_version=(0x[0-9a-fA-F]+)")
    def get_ota_information(self, matched_values):
        manufacturer_code, image_type, ota_version = matched_values
        logging.info(f"OTA Version: {ota_version}, Image Type: {image_type}, Manufacturer Code: {manufacturer_code}")
        return matched_values

    @expect_decorator(r"In progress: \[(\d+) / (\d+)\]")
    def get_ota_transmits_data(self, matched_values):
        progress, total = matched_values
        logging.info(f"OTA progress: {progress}, total: {total}")
        return matched_values

    @expect_decorator(r"In progress: \[(\d+) / (\d+)\]")
    def get_ota_receives_data(self, matched_values):
        progress, total = matched_values
        logging.info(f"progress: {progress}, total: {total}")
        return matched_values

    @expect_decorator(r"status\((\d+)\) and endpoint count\((\d+)\)")
    def get_active_endpoint_response_values(self, matched_values):
        status_value, endpoint_count_value = matched_values
        logging.info(f"Status: {status_value}, Endpoint Count: {endpoint_count_value}")
        return matched_values

    @expect_decorator(r"status\((\d+)\), "
                      r"device_id\((\d+)\), "
                      r"app_version\((\d+)\), "
                      r"profile_id\(0x([0-9a-fA-F]+)\), "
                      r"endpoint_ID\((\d+)\)")
    def get_simple_desc_response_values(self, matched_values):
        status_value, device_id_value, app_version_value, profile_id_value, endpoint_id_value = matched_values
        logging.info(f"Status: {status_value}, Device ID: {device_id_value}, App Version: {app_version_value}, "
                     f"Profile ID: {profile_id_value}, Endpoint ID: {endpoint_id_value}")
        return matched_values

    @expect_decorator(r"Bind response from address\(0x([0-9a-fA-F]+)\), endpoint\((\d+)\) with status\((\d+)\)")
    def get_bind_response_values(self, matched_values):
        address_value, endpoint_value, status_value = matched_values
        logging.info(f"Address: {address_value}, Endpoint: {endpoint_value}, Status: {status_value}")
        return matched_values

    @expect_decorator(r"address\(0x([0-9a-fA-F]+)\) src endpoint\((\d+)\) "
                      r"to dst endpoint\((\d+)\) cluster\(0x([0-9a-fA-F]+)\)")
    def get_received_report_values(self, matched_values):
        address, src_endpoint, dst_endpoint, cluster = matched_values
        logging.info(f"Address: {address}, Source Endpoint: {src_endpoint}, Destination Endpoint: {dst_endpoint}, "
                     f"Cluster: {cluster}")
        return matched_values

    def get_example_device_network_info(self, coordinator: bool, timeout=15):
        self.get_formed_network_parameters(expect_timeout=timeout)
        assert self.extended_pan_id.strip('0:') != ''
        assert self.pan_id not in ZigbeeCIConstants.invalid_panid
        assert ZigbeeCIConstants.channel_min <= int(self.channel) <= ZigbeeCIConstants.channel_max, (
            f'channel:{self.channel} out of '
            f'range')
        assert (self.short_address == ZigbeeCIConstants.coordinator_addr) if coordinator \
            else (self.short_address not in ZigbeeCIConstants.invalid_device_addr)
        self.network_info = {
            'extended_pan_id': self.extended_pan_id,
            'pan_id': self.pan_id,
            'channel': self.channel,
            'short_address': self.short_address
        }

    def check_response(self, pattern, timeout=6):
        self.dut.expect(pattern, timeout=timeout)


class CliDevice:

    def __init__(self, dut):
        self.dut = dut
        self.channel_id = ZigbeeCIConstants.channel
        self.short_address = None
        self.ieee_address = None
        self.pan_id = None
        self.extended_pan_id = None
        self.endpoint = random.randint(1, 9)
        self.network_info = None

    def _set_role(self, role):
        self.dut.write(f'role {role}')
        self.dut.write('role')
        self.dut.expect(role)

    def _set_channel(self, channel):
        self.dut.write(f'channel {channel}')
        self.dut.write('channel')
        channel_mask = Common.channel_to_mask(channel)
        self.dut.expect(f'Allowed Channel: {channel_mask}')

    def _set_network_type(self, network_type):
        self.dut.write(f'network type {network_type}')
        self.dut.write('network type')
        network_type_all = ['centralized', 'distributed']
        self.dut.expect(f'setting: {network_type_all[0] if network_type == "c" else network_type_all[1]}')

    def _create_zha_device(self, device_name, ep):
        self.dut.write(f'zha add {ep} {device_name}')
        self.dut.expect(f'{device_name} created with endpoint_id {ep}')
        self.dut.write('dm register')
        self.dut.write('dm show')

    def _start_bdb_comm(self, mode):
        self.dut.write(f'bdb_comm start {mode}')

    def _execute_comm_and_get_return_value(self, comm, pattern):
        self.dut.write(comm)
        self.dut.expect(comm)
        return self.get_cli_comm_return_value(pattern)[0]

    def _create_zb_device(self, device_name, mode, role, channel, network_type):
        self._set_role(role)
        self._set_channel(channel)
        self._set_network_type(network_type)
        ep = self.endpoint
        self._create_zha_device(device_name, ep)
        match_string = fr'({MatchPattern.join_success}|{MatchPattern.join_failed})'
        if mode == 'steer':
            joined = False
            for _ in range(3):
                self._start_bdb_comm(mode)
                match = self.dut.expect(match_string, timeout=20)
                if not match:
                    assert False, 'Failed to join network in 20 seconds'
                if match.group(1).decode() == MatchPattern.join_success:
                    joined = True
                    break
            else:
                assert joined, 'Failed to join the network in 3 times'
        else:
            self._start_bdb_comm(mode)
        time.sleep(1)

    def get_cli_comm_return_value(self, pattern, timeout=5):
        match_result = self.dut.expect(pattern, timeout=timeout)
        if not match_result:
            assert False, f"No match found for pattern: {pattern}"
        matched_groups = match_result.groups()
        if not matched_groups:
            assert False, f"No groups found in match for pattern: {pattern}"
        decoded_results = tuple(match.decode() if isinstance(match, bytes) else match for match in matched_groups)
        logging.info(f'get return: {decoded_results}')
        return decoded_results

    def create_coordinator(self, device_name, network_type):
        self._create_zb_device(device_name, 'form', 'zc', self.channel_id, network_type)

    def create_router(self, device_name, network_type):
        self._create_zb_device(device_name, 'steer', 'zr', self.channel_id, network_type)

    def create_end_device(self, device_name, network_type):
        self._create_zb_device(device_name, 'steer', 'zed', self.channel_id, network_type)

    def zcl_send_gen_and_check(self, cmd, source_ep, cluster, short_address='', dst_ep='', attr=0):
        comm = f'zcl send_gen {cmd} -e {source_ep} -c {cluster} -a {attr}'
        comm += f' -d {short_address}' if short_address else ''
        comm += f' --dst-ep {dst_ep}' if dst_ep else ''
        self.dut.write(comm)
        self.dut.expect(r'Receive Zigbee action\(0x[0-9A-Fa-f]+\) callback', timeout=6)

    def zcl_send_raw_and_check(self, source_ep, cluster, cmd, short_address='', dst_ep='', payload=''):
        comm = f'zcl send_raw -e {source_ep} -c {cluster} --cmd {cmd}'
        comm += f' -d {short_address}' if short_address else ''
        comm += f' --dst-ep {dst_ep}' if dst_ep else ''
        comm += f' -p {payload}' if payload else ''
        self.dut.write(comm)
        self.dut.expect(r'Receive Zigbee action\(0x[0-9A-Fa-f]+\) callback', timeout=6)

    def zdo_request_and_check(self, info, addr, eid=''):
        comm = f'zdo request {info} -d {addr}' + (f' -e {eid}' if eid else '')
        status_value = self._execute_comm_and_get_return_value(comm, MatchPattern.status)
        assert status_value == '0'

    def zdo_bind_and_check(self, cluster_id, src_ed, dst_ed, src_addr, dst_ieee_addr, remove: bool = False):
        comm = 'zdo bind -c' if not remove else 'zdo bind -r -c'
        comm += f' {cluster_id} -S {src_ed} -D {dst_ed} -s {src_addr} -d {dst_ieee_addr}'
        status_value = self._execute_comm_and_get_return_value(comm, MatchPattern.status)
        assert status_value == '0'

    def zdo_nwk_open(self, addr, duration):
        comm = f'zdo nwk_open -t {duration} -d {addr}'
        status_value = self._execute_comm_and_get_return_value(comm, MatchPattern.status)
        assert status_value == '0'

    def zdo_nwk_leave_and_check(self, addr):
        comm = f'zdo nwk_leave -d {addr}'
        status_value = self._execute_comm_and_get_return_value(comm, MatchPattern.status)
        assert status_value == '0'

    def check_response(self, pattern, timeout=3):
        self.dut.expect(pattern, timeout=timeout)

    def check_status(self):
        self.dut.expect('status: 0', timeout=1)

    def check_hex_response(self, expect_value, timeout=5):
        self.dut.expect(rf'0x[0-9A-Fa-f]+\s+{expect_value}', timeout=timeout)

    def network_open(self):
        time.sleep(0.5)
        self.dut.write('network open -t 180')
        self.dut.expect(r'Network\(0x[0-9A-Fa-f]{4}\) is open for 180 seconds')

    def get_device_network_info(self, coordinator: bool):
        self.pan_id = self._execute_comm_and_get_return_value('panid', MatchPattern.pan_id)
        self.extended_pan_id = self._execute_comm_and_get_return_value('panid -x', MatchPattern.extend_pan_id)
        self.channel_id = self._execute_comm_and_get_return_value('channel', MatchPattern.channel)
        self.short_address = self._execute_comm_and_get_return_value('address', MatchPattern.short_address)
        self.ieee_address = self._execute_comm_and_get_return_value('address -x', MatchPattern.address)
        assert self.pan_id not in ZigbeeCIConstants.invalid_panid
        assert ZigbeeCIConstants.channel_min <= int(self.channel_id) <= ZigbeeCIConstants.channel_max, (
            f'channel:{self.channel_id} out off '
            f'range')
        assert (self.short_address ==ZigbeeCIConstants.coordinator_addr) if coordinator \
            else (self.short_address not in ZigbeeCIConstants.invalid_device_addr)
        self.network_info = {
            'extended_pan_id': self.extended_pan_id,
            'pan_id': self.pan_id,
            'channel': self.channel_id,
            'short_address': self.short_address,
            'ieee_address': self.ieee_address
        }
        logging.info(f"network_info: {self.network_info}")

    def change_attribute_value(self, ep, cluster, attribute, value):
        self.dut.write(f'dm write -e {ep} -c {cluster} -a {attribute} -v {value} -f')
        self.dut.write(f'dm read -e {ep} -c {cluster} -a {attribute}')

    def dm_add(self, endpoint, cluster=None, attr=None, attr_type=None, access=None, value=None, role='S',
            force=False, manuf_code=None):
        cmd = f'dm add -e {endpoint}'
        cmd += f' -c {cluster} -r {role}' if cluster else ''
        cmd += ' -f' if force else ''
        cmd += f' -a {attr}' if attr is not None else ''
        cmd += f' --type {attr_type}' if attr_type is not None else ''
        cmd += f' --access {access}' if access is not None else ''
        cmd += f' -v {value}' if value is not None else ''
        cmd += f' --manuf {manuf_code}' if manuf_code is not None else ''
        self.dut.write(cmd)

class Common:

    @staticmethod
    def channel_to_mask(channel):
        assert ZigbeeCIConstants.channel_min <= channel <= ZigbeeCIConstants.channel_max
        mask_int = 1 << channel
        # Convert the integer mask to a formatted hexadecimal string with leading zeroes
        mask_str = f"0x{mask_int:08X}"
        return mask_str

    @staticmethod
    def check_network_matched(sever_info, client_info):
        assert sever_info['extended_pan_id'] == client_info['extended_pan_id']
        assert sever_info['pan_id'] == client_info['pan_id']
        assert sever_info['channel'] == client_info['channel']

    @staticmethod
    def check_zigbee_network_status(example_client, example_server, sleep_time=10):
        example_server.get_example_device_network_info(coordinator=True)
        # sleep to wait client join the network
        time.sleep(sleep_time)
        example_client.get_example_device_network_info(coordinator=False)
        time.sleep(0.5)
        example_server.check_response(r'New device commissioned or rejoined', timeout=5)
        Common.check_network_matched(example_client.network_info, example_server.network_info)

    @staticmethod
    def check_zigbee_sleep_intervals(example_dut, min_boot_ms=30000):
        enter_sleep_boot_ms_pat = re.compile(
            r'I \((\d+)\) .*LIGHT_SLEEP_APP'
        )
        warmup_deadline = time.time() + 40
        while time.time() < warmup_deadline:
            match = example_dut.dut.expect(enter_sleep_boot_ms_pat, timeout=11)
            assert match, 'expected Enter Light Sleep line with boot timestamp'
            grp = match.group(1)
            boot_ms = int(grp.decode() if isinstance(grp, bytes) else grp)
            if boot_ms > min_boot_ms:
                break
        else:
            assert False, f'timeout waiting for Enter Light Sleep with boot time > {min_boot_ms} ms'
        logging.info(f'Enter Light Sleep with boot time > {min_boot_ms} ms')

        sleep_start = r'Enter Light Sleep'
        sleep_end = r'Exit Light Sleep'
        match = example_dut.dut.expect(sleep_start, timeout=11)
        assert match, 'expected Enter Light Sleep line'
        start_time = time.time()
        match = example_dut.dut.expect(sleep_end, timeout=11)
        assert match, 'expected Exit Light Sleep line'
        interval = time.time() - start_time
        logging.info(f"Interval: {interval} seconds")
        assert interval > 5 and interval <= 10, f"Interval: {interval} seconds"

    @staticmethod
    def cli_light_control_and_check(cli_switch, example_light, on: bool):
        light_status_log = ['Light sets to Off', 'Light sets to On']
        switch_action = 1 if on else 0
        cluster = ZigbeeCIConstants.on_off_cluster_id
        cli_switch.zcl_send_raw_and_check(source_ep=cli_switch.endpoint, cluster=cluster, cmd=switch_action,
                                          short_address=example_light.short_address, dst_ep=10)
        example_light.check_response(light_status_log[switch_action])
        cli_switch.zcl_send_gen_and_check('read', source_ep=cli_switch.endpoint, cluster=cluster, short_address=example_light.short_address, dst_ep=10)
        cli_switch.check_response(rf'0x[0-9A-Fa-f]+\s+0{switch_action}')

    @staticmethod
    def cli_create_and_verify_network_connection(source_device, destination_device, source_device_name,
                                                 destination_device_name, network_type):
        source_device.create_coordinator(device_name=source_device_name, network_type=network_type)
        source_device.check_response(MatchPattern.form_success, timeout=5)

        source_device.get_device_network_info(coordinator=True)
        source_device.network_open()

        destination_device.create_router(device_name=destination_device_name, network_type=network_type)
        source_device.check_response(MatchPattern.device_commission, timeout=5)

        destination_device.get_device_network_info(coordinator=False)
        Common.check_network_matched(source_device.network_info, destination_device.network_info)

    @staticmethod
    def cli_light_switch_and_check_rsp(switch_device, light_device, cmd, expect_rsp='', send_read=True):
        cluster = ZigbeeCIConstants.on_off_cluster_id
        switch_device.zcl_send_raw_and_check(switch_device.endpoint, cluster, cmd, light_device.short_address,
                                             light_device.endpoint)
        light_device.check_hex_response(expect_rsp)
        time.sleep(1)
        if send_read:
            switch_device.zcl_send_gen_and_check('read', switch_device.endpoint, cluster, light_device.short_address,
                                                 light_device.endpoint, attr=0)
            switch_device.check_hex_response(expect_rsp)
            time.sleep(1)

    @staticmethod
    def cli_level_switch_and_check_rsp(switch_device, light_device, cmd, expect_rsp='', payload='', send_read=True, check_stop_move=False):
        cluster = ZigbeeCIConstants.level_control_cluster_id
        switch_device.zcl_send_raw_and_check(switch_device.endpoint, cluster, cmd, light_device.short_address,
                                             light_device.endpoint, payload=payload)
        if check_stop_move:
            time.sleep(2)
            switch_device.zcl_send_raw_and_check(switch_device.endpoint, cluster, '0x07', light_device.short_address,
                                                 light_device.endpoint)
        light_device.check_hex_response(expect_rsp)
        time.sleep(1)
        if send_read:
            switch_device.zcl_send_gen_and_check('read', switch_device.endpoint, cluster, light_device.short_address,
                                                 light_device.endpoint, attr=0)
            switch_device.check_hex_response(expect_rsp)
            time.sleep(1)

    @staticmethod
    def cli_color_switch_and_check_rsp(switch_device, light_device, cmd, expect_x_value='', expect_y_value='', payload=''):
        cluster = ZigbeeCIConstants.color_control_cluster_id
        switch_device.zcl_send_raw_and_check(switch_device.endpoint, cluster, cmd, light_device.short_address,
                                             light_device.endpoint, payload=payload)

        if cmd == '0x09':
            time.sleep(5)

        if cmd == '0x08':
            time.sleep(2.4)
            switch_device.zcl_send_raw_and_check(switch_device.endpoint, cluster, '0x47', light_device.short_address,
                                                 light_device.endpoint)
        light_device.check_hex_response(expect_x_value)
        light_device.check_hex_response(expect_y_value)

    @staticmethod
    def check_connection_status(src_device, dst_addr):
        src_device.zdo_request_and_check("ieee_addr", dst_addr)
