class ZigbeeCIConstants:
    default_id = ['0x0000', '0xffff']
    invalid_device_addr = ['0xfff8', '0xfff9', '0xfffa', '0xfffb', '0xfffc', '0xfffd', '0xfffe', '0xffff']
    invalid_panid = ['0x0000', '0xffff']
    coordinator_addr = '0x0000'
    channel_min = 11
    channel_max = 26
    channel = 13
    ota_total_package = '501070'
    ota_version = '0x10022000'
    image_type = '0x0001'
    manufacturer_code = '0x131b'
    on_off_cluster_id = 0x0006
    level_control_cluster_id = 0x0008
    color_control_cluster_id = 0x0300


class MatchPattern:
    ieee_addr = 'ieee address: (0x[0-9a-fA-F]{16})'
    pan_id = '(0x[0-9a-fA-F]{4})'
    extend_pan_id = '(0x[0-9a-fA-F]{16})'
    short_address = '(0x[0-9a-fA-F]{4})'
    address = '(0x[0-9a-fA-F]{16})'
    channel = r'Current Channel: (\d{2})'
    nwk_address = 'nwk address: (0x[0-9a-fA-F]{4})'
    form_success = 'Formed network successfully'
    device_commission = 'New device commissioned or rejoined'
    joined_network = ('Joined network successfully PAN ID\(0x[0-9a-fA-F]{4},\s*EXT:\s*(0x[a-fA-F0-9]+)\),\s*Channel\((\d+)\),\s*Short Address\((0x[0-9a-fA-F]{4})\)')
    active_ep = r'active ep: \[\d+, (\d+)]'
    status = r'status:\s*(\d+)'
    empty_binding_table = r'\|Dst_E\|(?!.*\|\s*0\s*\|)'
    on_off_light_in_clusters = r'in: \[0x0006, 0x0005, 0x0004, 0x0003, 0x0000]'
    left_network = 'Left network successfully'
    join_failed = 'Failed to join network'
    join_success = 'Joined network successfully'
    bound_customized_data_producer = 'Bound customized data producer successfully'
    bound_ha_light = 'Bound HA light device successfully'
    bound_ha_dimmable_light = 'Bound HA color dimmable light device successfully'
    ota_sending_block = 'OTA Sending Block'
    ota_receiving_block = 'OTA Receiving Block'
    update_the_rcp_version = 'Update the RCP version'
    initialize_zigbee_stack = 'Initialize Zigbee stack'
    enter_deep_sleep = 'Enter deep sleep for 20 seconds'
    network_open = r'Network\([^)]*\) is open'
    temperature_sensor_measured_value = r'Temperature sensor measured value: \d+\.\d+ degrees Celsius'
    receive_default_rsp = r'Received ZCL Default Response: status\(0x00\)'
    sleep_pd_top = 'PMU_SLEEP_PD_TOP: True'
    sleep_pd_modem = 'PMU_SLEEP_PD_MODEM: True'

