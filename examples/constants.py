class ZigbeeCIConstants:
    default_id = ['0x0000', '0xffff']
    invalid_device_addr = ['0xfff8', '0xfff9', '0xfffa', '0xfffb', '0xfffc', '0xfffd', '0xfffe', '0xffff']
    invalid_panid = ['0x0000', '0xffff']
    coordinator_addr = '0x0000'
    channel_min = 11
    channel_max = 26
    channel = 13
    ota_total_package = '618486'
    ota_version = '0x1010100'
    image_type = '0x1011'
    manufacturer_code = '1001'
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
    joined_network = (r'Joined network successfully \(Extended PAN ID: (?:[0-9a-fA-F]{2}:){7}[0-9a-fA-F]{2}, '
                      r'PAN ID: 0x[0-9A-Fa-f]+, Channel:\d+, Short Address: 0x[0-9A-Fa-f]+\)')
    active_ep = r'active ep: \[(\d+), \d+]'
    status = r'status:\s*(\d+)'
    empty_binding_table = r'\|Dst_E\|(?!.*\|\s*0\s*\|)'
    on_off_light_in_clusters = r'in: \[0x0000, 0x0003, 0x0004, 0x0005, 0x0006]'
    left_network = 'Left network successfully'
