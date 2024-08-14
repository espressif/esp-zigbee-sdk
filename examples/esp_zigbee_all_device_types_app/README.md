| Supported Targets | ESP32-H2 | ESP32-C6 |
| ----------------- | -------- | -------- |

# All Device Types App Example

This test code shows how to configure Zigbee device and use it as HA Device Types, such as On/Off Switch, Window Covering, Door Lock, On/Off Light Device and so on.

## Hardware Required
* One development board with ESP32-H2 SoC (loaded with esp_zigbee_all_device_types_app example).
* Another development board with ESP32-H2 SoC as communication peer (loaded with esp_zigbee_all_device_types_app example or other examples).

## Configure the Project

Before project configuration and build, make sure to set the correct chip target using `idf.py set-target <TARGET>` command.

## Erase the NVRAM

Before flash it to the board, it is recommended to erase NVRAM if user doesn't want to keep the previous examples or other projects stored info
using `idf.py -p <PORT> erase-flash`

## Build and Flash

Build the project, flash it to the board by running `idf.py -p <PORT> build flash`.

## Example Output

As you run the example, you will see the following log:

```
I (298) cpu_start: Unicore app
I (298) cpu_start: Pro cpu up.
W (307) clk: esp_perip_clk_init() has not been implemented yet
I (314) cpu_start: Pro cpu start user code
I (314) cpu_start: cpu freq: 96000000 Hz
I (314) cpu_start: Application information:
I (317) cpu_start: Project name:     esp_zigbee_all_device_types_app
I (324) cpu_start: App version:      b8aed66-dirty
I (329) cpu_start: Compile time:     Aug 15 2024 17:38:49
I (335) cpu_start: ELF file SHA256:  d1357f7216520fbf...
I (341) cpu_start: ESP-IDF:          v5.1.3
I (346) cpu_start: Min chip rev:     v0.0
I (351) cpu_start: Max chip rev:     v0.99
I (356) cpu_start: Chip rev:         v0.1
I (360) heap_init: Initializing. RAM available for dynamic allocation:
I (368) heap_init: At 40813A30 len 00039950 (230 KiB): D/IRAM
I (374) heap_init: At 4084D380 len 00002B60 (10 KiB): STACK/DIRAM
I (382) spi_flash: detected chip: generic
I (385) spi_flash: flash io: dio
W (389) spi_flash: Detected size(4096k) larger than the size in the binary image header(2048k). Using the size in the binary image header.
I (403) sleep: Configure to isolate all GPIO pins in sleep state
I (409) sleep: Enable automatic switching of GPIO sleep configuration
I (417) app_start: Starting scheduler on CPU0
I (421) main_task: Started on CPU0
I (421) main_task: Calling app_main()
I (431) esp-zigbee-console: List of ESP Zigbee Console commands:
I (431) esp-zigbee-console:   - Command 'address'
I (441) esp-zigbee-console:   - Command 'bdb_comm'
I (441) esp-zigbee-console:   - Command 'channel'
I (441) esp-zigbee-console:   - Command 'dm'
I (451) esp-zigbee-console:   - Command 'factoryreset'
I (451) esp-zigbee-console:   - Command 'ic'
I (461) esp-zigbee-console:   - Command 'network'
I (461) esp-zigbee-console:   - Command 'panid'
I (471) esp-zigbee-console:   - Command 'radio'
I (471) esp-zigbee-console:   - Command 'reboot'
I (481) esp-zigbee-console:   - Command 'role'
I (481) esp-zigbee-console:   - Command 'start'
I (491) esp-zigbee-console:   - Command 'tl'
I (491) esp-zigbee-console:   - Command 'zcl'
I (501) esp-zigbee-console:   - Command 'zdo'
I (501) esp-zigbee-console:   - Command 'zgp'
I (511) esp-zigbee-console:   - Command 'zha'
I (591) phy: phy_version: 230,2, 9aae6ea, Jan 15 2024, 11:17:12
I (591) phy: libbtbb version: 944f18e, Jan 15 2024, 11:17:25
I (591) ESP_ZB_CONSOLE_APP: Start ESP Zigbee Console

Type 'help' to get the list of commands.
Use UP/DOWN arrows to navigate through command history.
Press TAB when typing command name to auto-complete.
I (601) main_task: Returned from app_main()
esp>
```

When type `help`, you will see the following outputs about the supported commands:

```
address
  Get/Set the (extended) address of the node

bdb_comm
  Perform BDB Commissioning

channel
  Get/Set 802.15.4 channels for network

dm
  ZigBee Cluster Library data model management

factoryreset
  Reset the device to factory new

ic
  Install code configuration

network
  Network configuration

panid
  Get/Set the (extended) PAN ID of the node

radio
  Enable/Disable the radio

reboot
  Reboot the device

role
  Get/Set the Zigbee role of a device

start
  Start Zigbee stack

tl
  TouchLink configuration

zcl
  ZigBee Cluster Library management

zdo
  Zigbee Device Object management

zgp
  ZigBee Green Power Profile management

zha
  ZigBee Home Automation Profile

help
  Print the list of registered commands
```

For most of the commands, you can execute them without any parameters to see the usage:

```
esp> zdo
zdo: Zigbee Device Object management
    request         Request information from node
    annce           Announce current node
    match           Get matched devices
    bind            Request the node to bind to device
    nwk_open        Request the node to open the network
    nwk_leave       Request the node to leave the network
```
```
esp> zdo match
Usage: zdo match [-i <u16:CID>]... [-o <u16:CID>]... [-p <u16:PID>] -d <hex:ADDR>
  -i, --in=<u16:CID>        in cluster ID
  -o, --out=<u16:CID>       out cluster ID
  -p, --profile=<u16:PID>   profile id (PID) to match, defaule: HA
  -d, --dst-addr=<hex:ADDR> network address this request is to
```

For more information about the supported commands and usages, please refer to [ESP-Zigbee-Console Reference](../../components/esp-zigbee-console/README.md)

## Play with All Device Type Example
This section demonstrate the process to create HA on_off_light and on_off_switch devices.

### Start Node 1 as on_off_light

Create and register the HA standard on_off_light data model:

```bash
esp> zha add 1 on_off_light
I (518033) cli_cmd_zha: on_off_light created with endpoint_id 1
esp> dm register
esp>
```

Form the network and open the network for joining:

```bash
esp> bdb_comm start form
I (839703) cli_cmd_bdb: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (839703) cli_cmd_bdb: Zigbee stack initialized
W (842093) cli_cmd_bdb: Network(0x79d0) closed, devices joining not allowed.
I (842103) cli_cmd_bdb: Formed network successfully (Extended PAN ID: 0x744dbdfffe602dfd, PAN ID: 0x79d0, Channel:11, Short Address: 0x5fd5)
esp> network open -t 200
I (860763) cli_cmd_bdb: Network(0x79d0) is open for 200 seconds
```

### Start Node 2 as on_off_switch

Create and register the HA standard on_off_switch data model:

```bash
esp> zha add 2 on_off_switch
I (914051) cli_cmd_zha: on_off_switch created with endpoint_id 2
esp> dm register
esp>
```

Joining the network:

```bash
esp> bdb_comm start steer
I (930721) cli_cmd_bdb: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (930721) cli_cmd_bdb: Zigbee stack initialized
W (933611) cli_cmd_bdb: Network(0x79d0) closed, devices joining not allowed.
I (933981) cli_cmd_bdb: Network(0x79d0) is open for 180 seconds
I (933991) cli_cmd_bdb: Joined network successfully (Extended PAN ID: 0x744dbdfffe602dfd, PAN ID: 0x79d0, Channel:11, Short Address: 0x0935)
```

### Control the light using switch

Get the light on/off status by reading the attribute from the switch:

```bash
esp> zcl send_gen read -d 0x5fd5 --dst-ep 1 -e 2 -c 6 -a 0
I (1347151) cli_cmd_zcl: Read response: endpoint(2), cluster(0x06)
I (1347161) cli_cmd_zcl: attribute(0x00), type(0x10), data size(1)
I (1347171) : 0x40818c02   00                                                |.|
```

Send "On" command from the switch:

```bash
esp> zcl send_raw -d 0x5fd5 --dst-ep 1 -e 2 -c 6 --cmd 0x01
W (1405221) ESP_ZB_CONSOLE_APP: Receive Zigbee action(0x1005) callback
```

Check the light status again:

```bash
esp> zcl send_gen read -d 0x5fd5 --dst-ep 1 -e 2 -c 6 -a 0
I (1420021) cli_cmd_zcl: Read response: endpoint(2), cluster(0x06)
I (1420021) cli_cmd_zcl: attribute(0x00), type(0x10), data size(1)
I (1420031) : 0x40818ca6   01                                                |.|
```

## Troubleshooting

For any technical queries, please open an [issue](https://github.com/espressif/esp-zigbee-sdk/issues) on GitHub. We will get back to you soon
