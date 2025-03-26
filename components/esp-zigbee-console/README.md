# ESP-Zigbee-Console Reference

The ESP-Zigbee-Console implements a command line interface to operate the ESP-Zigbee-SDK. The CLI
provides the flexibility to configure and manage the stack at runtime.

## ESP-Zigbee-Console Command Conventions

The commands are consisted as `<main_command> [<sub_command>] [options]`, the `options` part are parsed using
[`argtable3`](https://www.argtable.org/) provided by `console` component in ESP-IDF.
Therefore the `options` follows
[POSIX Utility Conventions](https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/V1_chap12.html).
For most of the command, type the command can display the help strings of the command:

```bash
esp> zdo
zdo: Zigbee Device Object management
    request         Request information from node
    annce           Announce current node
    match           Get matched devices
    bind            Request the node to bind to device
    nwk_open        Request the node to open the network
    nwk_leave       Request the node to leave the network

esp> zdo match
Usage: zdo match [-i <u16:CID>]... [-o <u16:CID>]... [-p <u16:PID>] -d <addr:ADDR>
  -i, --in=<u16:CID>        in cluster ID
  -o, --out=<u16:CID>       out cluster ID
  -p, --profile=<u16:PID>   profile id (PID) to match, defaule: HA
  -d, --dst-addr=<addr:ADDR> network address this request is to
```

The option arguments are shown as `<type:name>` to indicate the argument type and name of the option.
For specific type of argument, correct format should be provided so that it can be correctly parsed.

- `hex`: HEX, start with `0x` prefix.
- `u8`: HEX or NUMBER allowed, in range 0 - 0xFF.
- `u16`: HEX or NUMBER allowed, in range 0 - 0xFFFF.
- `u32`: HEX or NUMBER allowed, in range 0 - 0xFFFFFFFF.
- `eui64`: IEEE address in HEX format, MUST be extactly 64-bit data.
- `addr`: Equivalent to `u16|eui64`, short address or IEEE address determined by the data length.

## ESP-Zigbee-Console Command List

- [`address`](#address): Get/Set the (extended) address of the node.
- [`aps`](#aps): Zigbee Application Support management.
- [`bdb_comm`](#bdb_comm): Perform BDB Commissioning.
- [`channel`](#channel): Get/Set 802.15.4 channels for network
- [`dm`](#dm): Zigbee Cluster Library data model management.
- [`factoryreset`](#factoryreset): Reset the device to factory new.
- [`ic`](#ic): Install code configuration.
- [`iperf`](#iperf): Iperf over Zigbee.
- [`macfilter`](#macfilter): Zigbee stack mac filter management.
- [`neighbor`](#neighbor): Neighbor information.
- [`network`](#network): Network configuration.
- [`panid`](#panid): Get/Set the (extended) PAN ID of the node.
- [`ping`](#ping): Ping over Zigbee.
- [`radio`](#radio): Enable/Disable the radio.
- [`reboot`](#reboot): Reboot the device.
- [`role`](#role): Get/Set the Zigbee role of a device.
- [`route`](#route): Route information.
- [`start`](#start): Start Zigbee stack.
- [`tl`](#tl): TouchLink configuration.
- [`trace`](#trace): Configure Zigbee stack trace log.
- [`zcl`](#zcl): Zigbee Cluster Library management.
- [`zdo`](#zdo): Zigbee Device Object management.
- [`zgp`](#zgp): Zigbee Green Power Profile management.
- [`zha`](#zha): Zigbee Home Automation Profile.


## ESP-Zigbee-Console Command Details

### address
Get/Set the (extended) address of the Zigbee device node.

> **Note:** Set short address is not supported.

#### `address [-x]`
Get the address or extended address of the Zigbee device node.

```bash
esp> address
0x0d29
```

```bash
esp> address -x
0x4831b7fffec02bbc
```

#### `address -x <addr:ADDR>`
Set the extended address of the Zigbee device node.

```bash
esp> address -x 0x0123456789abcdef
```


### aps
Zigbee Application Support management

#### `aps send_raw [options]`
options:
- `-d <addr:ADDR>`: Destination address of the command.
- `--dst-ep <u8:EID>`: Destination endpoint of the command.
- `-e <u8:EID>`: Source endpoint of the command.
- `--profile=<u16:PID>`: Profile id of the command.
- `-c <u16:CID>`: Cluster id of the command.

Destination address mode selection: same as [`zcl`](#zcl)

```bash
esp> aps send_raw -e 2 --dst-ep 3 -c 0x0006 -d 0x33d2 -p 0x11223344
Send aps data frame successful
```

#### `aps dump <open|close>`
Dump APS traffic

Local device start to dump aps traffic.
```bash
esp> aps dump open
```
Remote device send aps data frame.
```bash
esp> aps send_raw -d 0x90eb -e 2 --dst-ep 2 -c 0x0006 -p 0x1122
Send aps data frame successful
```
Local device dump aps data frame.
```bash
Received aps data frame
I (680692) : 0x40817760   11 22                                             |."|
```


### bdb_comm
Perform BDB Commissioning.

#### `bdb_comm channel`
Get primary and secondary channels to perform BDB commissioning. The channels are displayed as channel masks.

Get the operating channels for BDB commissioning.

```bash
esp> bdb_comm channel
Primary Channel: 0x07fff800
Secondary Channel: 0x07fff800
```

#### `bdb_comm channel [-m] <u32:PRIMARY> [<u32:SECONDARY>]`
Set the operating channels for BDB commissioning.

```bash
esp> bdb_comm channel 13 14
esp> bdb_comm channel
Primary Channel: 0x00002000
Secondary Channel: 0x00004000
```

Use `-m` to indicate the channels are given as channel masks.

```bash
esp> bdb_comm channel -m 0x800 0xf800
esp> bdb_comm channel
Primary Channel: 0x00000800
Secondary Channel: 0x0000f800
```

#### `bdb_comm mode`
Get current/last BDB commissioning mode.

Displayed value is a combination of [`esp_zb_bdb_commissioning_mode_mask_t`](https://docs.espressif.com/projects/esp-zigbee-sdk/en/latest/esp32/api-reference/bdb/esp_zigbee_bdb_touchlink.html#_CPPv436esp_zb_bdb_commissioning_mode_mask_s).

```bash
esp> bdb_comm mode
0x04
```

#### `bdb_comm start <MODE> [<MODE>]...`
Start the top level commissioning of BDB.

> **Note:** The command will start the Zigbee stack if it hasn't started.

Supported modes are:

- `steer`: Perform the network steering procedure.
- `form`: Perform the network formation procedure.
- `bind`: Perform finding & binding procedure.
- `initiator`: Perform Touchlink procedure as initiator.
- `target`: Perform Touchlink procedure as target.

```bash
esp> bdb_comm start form
I (15585) cli_cmd_bdb: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (15585) cli_cmd_bdb: Zigbee stack initialized
W (17975) cli_cmd_bdb: Network(0x23ea) closed, devices joining not allowed.
I (17985) cli_cmd_bdb: Formed network successfully (Extended PAN ID: 0x4831b7fffec02bbc, PAN ID: 0x23ea, Channel:26, Short Address: 0x0000)
```

#### `bdb_comm cancel <MODE>`
Cancel commissioning process.

Supported modes are:
- `steer`: Cancel the network steering procedure.
- `form`: Cancel the network formation procedure.
- `target`: Cancel Touchlink procedure as target.


### channel
Get/Set 802.15.4 channels for network.

Get allowed channels and current channel if the device node is on a network:

```bash
esp> channel
Allowed Channel: 0x07fff800
Current Channel: 19
```

Set the allowed channels for network operation:

```bash
esp> channel 13
```

Use `-m` to indicate the channels are provided as channel mask:

```bash
esp> channel -m 0x06ef0000
```


### dm
Zigbee Cluster Library data model management.

The sub-commands operate on the `ep_list` registered/created by `esp_zb_console_manage_ep_list()`:

- [`dm show`](#dm-show)
- [`dm add`](#dm-add)
- [`dm register`](#dm-register)

The sub-commands operate on registered data model:

- [`dm read`](#dm-read)
- [`dm write`](#dm-write)

#### `dm show`
Show current data model.

> **Note:** The command is only available before `dm register`.

```bash
esp> zha add 1 on_off_light
I (13055) cli_cmd_zha: on_off_light created with endpoint_id 1
esp> dm show
+-- ep:1, prfl:0x0104, dev_id:0x0100
    |-- cluster:0x0000, S, manuf:0x0000
    |   |-- attr:0xfffd, type:0x21, access:0x01, manuf:0xffff
    |   |-- attr:0x0000, type:0x20, access:0x01, manuf:0xffff
    |   +-- attr:0x0007, type:0x30, access:0x01, manuf:0xffff
    |-- cluster:0x0003, S, manuf:0x0000
    |   |-- attr:0xfffd, type:0x21, access:0x01, manuf:0xffff
    |   +-- attr:0x0000, type:0x21, access:0x03, manuf:0xffff
    |-- cluster:0x0004, S, manuf:0x0000
    |   |-- attr:0xfffd, type:0x21, access:0x01, manuf:0xffff
    |   +-- attr:0x0000, type:0x18, access:0x01, manuf:0xffff
    |-- cluster:0x0005, S, manuf:0x0000
    |   |-- attr:0xfffd, type:0x21, access:0x01, manuf:0xffff
    |   |-- attr:0x0000, type:0x20, access:0x01, manuf:0xffff
    |   |-- attr:0x0001, type:0x20, access:0x01, manuf:0xffff
    |   |-- attr:0x0002, type:0x21, access:0x01, manuf:0xffff
    |   |-- attr:0x0003, type:0x10, access:0x01, manuf:0xffff
    |   +-- attr:0x0004, type:0x18, access:0x01, manuf:0xffff
    +-- cluster:0x0006, S, manuf:0x0000
        |-- attr:0xfffd, type:0x21, access:0x01, manuf:0xffff
        +-- attr:0x0000, type:0x10, access:0x15, manuf:0xffff
```
#### `dm add`
Add items (endpoint/cluster/attribute) in ZCL data model. The command only creates missing items and skip the
already existed ones.

> **Note:** The command can only be used before data model registered.

Use `-e <u8:EID>` to specify the endpoint id to be added, the options only take effect when `-e` specified:
- `--device <u16:DID>`: The device id of the endpoint.
- `--version=<u8:VER>`: The device version of the endpoint.
- `--profile <u16:PID>`: The profile id of the endpoint.

Use `-c <u16:CID>` to specify the cluster id to be added, the options only take effect when `-c` specified:
- `-r, --role=<ROLE>`: The role of the cluster.
- `--manuf=<u16:CODE>`: The manufacture code of the cluster.

Use `-a <u16:AID>` to specify the attribute id to be added, the options only take effect when `-a` specified:
-  `--access=<mc:R|W|P|S>`: Access of the attribute, default: RW
-  `--type=<u8:TID>`: The type id of the attribute, defined by ZCL specification.
-  `-v, --value=<hex:DATA>`: The default value of the attribute, in HEX format.

Use `-f` to add items as it is specified in the command.

To create an `HA on_off_light` on endpoint 1:

1. Add empty endpoint `1`:
   ```bash
   esp> dm add -e 1
   ```

2. Add `basic` server cluster with mandatory attributes:
   ```bash
   esp> dm add -e 1 -c 0
   ```
   Add optional attribute `ManufacturerName` with value `"\x09""ESPRESSIF"` to `basic` cluster:
   ```bash
   esp> dm add -e 1 -c 0 -a 0x04 -v 0x09455350524553534946
   ```

3. Add all other clusters for `HA on_off_light` device:
   ```bash
   esp> dm add -e 1 -c 3
   esp> dm add -e 1 -c 4
   esp> dm add -e 1 -c 5
   esp> dm add -e 1 -c 6
   ```
   Add optional client cluster:
   ```bash
   esp> dm add -e 1 -c 0x0406 -r C
   ```


#### `dm register`
Register current data model. The data model can't be changed after registration.

```bash
esp> dm register
```

#### `dm read`
Read attribute value in data model.

> **Note:** The command can only be used after the data model registered.

Use `-r <ROLE>` to specify the role of the cluster. `S` for server, `C` for client, default: `S`.
Use `--manuf <u16:CODE>` to specify the manufucture code if any.

```bash
esp> dm read -e 1 -c 6 -a 0
I (43445) : 0x40816308   00                                                |.|
```

#### `dm write`
Write value to attribute in data model.

Use `-f` to skip the access check of the attribute.

> **Note:** The command can only be used after the data model registered.

```bash
esp> dm write -e 1 -c 6 -a 0 -v 0x01
Fail to write attribute: 136
Command returned non-zero error code: 0xffffffff (ESP_FAIL)

esp> dm write -e 1 -c 6 -a 0 -v 0x01 -f
```


### factoryreset
Reset the device to factory new immediately.

```bash
esp> factoryreset
Erasing Erasing NVRAM of Zigbee stack ... Done
Reboot the device
```

### ic
Install code configuration.

#### `ic policy <int:IC policy>`
Set install code policy.

Supported policy values are:
- `0`: Not support install code.
- `1`: Support install code.
- `2`: Require install code.

Set the TC to require use install code by joining devices
```bash
esp> ic policy 2
```

#### `ic add <eui64:EUI64> <IC>`
Add install code for a remote device.

> **Note:**
> - The command should be used after Zigbee stack starts.

```bash
esp> ic add 0xbbbbbbbbbbbbbbbb 0x83FED3407A939723A5C639B26916D505C3B5
```

#### `ic remove <eui64:EUI64>`
Remove install code for a remote device.

```bash
esp> ic remove 0xbbbbbbbbbbbbbbbb
```

#### `ic set <IC>`
Set the install code on local device.

```bash
esp> ic set 0x83FED3407A939723A5C639B26916D505C3B5
```

#### `ic get`
Get the install code configured on local device.

```bash
esp> ic get
I (837619) : 0x4080fa50   83 fe d3 40 7a 93 97 23  a5 c6 39 b2 69 16 d5 05  |...@z..#..9.i...|
I (837619) : 0x4080fa60   c3 b5                                             |..|
```


### iperf
Iperf over Zigbee

> **Note:** ping_iperf_test cluster (0xff01) should be registered with the stack first.

#### `iperf start -d <addr:ADDR> --dst-ep=<u8:EID> -e <u8:EID> -t <u16:TIME> [-i <u16:TIME>] -l <u16:DATA>`
- `-d, --dst-addr=<addr:ADDR>`: Destination address.
- `--dst-ep=<u8:EID>`: Destination endpoint id.
- `-e, --src-ep=<u8:EID>`: Source endpoint id.
- `-t, --iperf-time=<u16:TIME>`: Iperf duration time in second.
- `-i, --iperf-interval=<u16:TIME>`: Iperf interval in millisecond, default: 20.
- `-l, --payload-len=<u16:DATA>`: The payload length in byte of the iperf command.

```bash
esp> iperf start -e 2 --dst-ep 3 -d 0x2cc4 -t 3 -i 50 -l 100
I (379614) ping_iperf_test: throughput: 10.000 kbps, count: 1
```

#### `iperf result [-r <sc:C|S>] -e <u8:EID>`
- `-r, --role=<sc:C|S>`: The role of the iperf cluster, default: S
- `-e, --src-ep=<u8:EID>`: Source endpoint id

```bash
esp> iperf result -r C -e 2
iperf test throughput: 13 kbps
```


### macfilter
Zigbee stack mac filter management.

#### `macfilter add [-i] <addr:ADDR>`
Add device ieee addr for filter in.

```bash
esp> macfilter add 0x0123456789abcdef
```

Use `-i` to filter out short address:
```bash
esp> macfilter add -i 0x1234
```

#### `macfilter clear`
Clear all entries in the filter

```bash
esp> macfilter clear
```


### neighbor
Neighbor information.

#### `neighbor table`
Dump the neighbor table on current node.

```bash
esp> neighbor table
|Index| Age |NwkAddr | MacAddr            |Type |Rel|Depth| LQI | Cost |
+-----+-----+--------+--------------------+-----+---+-----+-----+------+
|   1 |   1 | 0x83a6 | 0x4831b7fffec182eb |  ZR | S |   1 | 255 |  o:1 |
|   2 |   1 | 0xcb75 | 0x4831b7fffec18311 |  ZR | S |   2 | 255 |  o:7 |
```


### network
Network configuration.

#### `network type [<TYPE>]`
Get/Set the network type.

Supported types:
- `c`: Centralized network, need be formed by Zigbee coordinator.
- `d`: Distributed network, need be formed by Zigbee router.

```bash
esp> network type d
```

```bash
esp> network type
setting: distributed
current on: distributed
```

#### `network key [<hex:KEY128>]`
Get/Set the network key.

Set network key:

```bash
network key 0x0123456789abcdeffedcba9876543210
```

Get network key:

```bash
esp> network key
I (77200) : 0x4084f6f4   83 38 66 7a d8 b6 b4 b4  63 17 12 39 0f 83 f8 6a  |.8fz....c..9...j|
```

#### `network legacy`
Enable/Disable legacy device support.

> **Note:** Getting the current state has not been supported yet.

```bash
esp> network legacy enable
```

```bash
esp> network legacy disable
```

#### `network childmax [<u8:CHILD_NUM>]`
Get/Set max children number.

```bash
esp> network childmax 20
```

```bash
esp> network childmax
20
```

#### `network open -t <u8:TIMEOUT>`
Open local network for specified timeout in seconds.

```bash
esp> network open -t 100
esp> I (332981) cli_cmd_bdb: Network(0x34a4) is open for 100 seconds
```

#### `network close`
Close local network immediately.

```bash
esp> network close
esp> W (354641) cli_cmd_bdb: Network(0x34a4) closed, devices joining not allowed.
```

#### `network scan [-m] <u32:CHANNEL> [-t <u8:TIMEOUT>]`
Scan channels for networks (network discovery).

```bash
esp> network scan -m 0x07fff800
|Chnl| PanID  | ExtPanID           |Status |Cap|
+----+--------+--------------------+-------+---+
| 23 | 0x8910 | 0x744dbdfffe602d57 | Close | RE|
| 17 | 0x8a41 | 0x4831b7fffec02bbc | Close | RE|
| 11 | 0xc2ab | 0x6e6ec31131b063da | Close | RE|
```

#### `network ed_scan [-m] <u32:CHANNEL> [-t <u8:TIMEOUT>]`
Perform energy detection scan on channels.

```bash
esp> network ed_scan -m 0x07fff800
|Chnl| RSSI |
+----+------+
| 11 | -112 |
| 12 | -102 |
| 13 | -100 |
| 14 | -113 |
| 15 |  -91 |
| 16 | -105 |
| 17 |  -56 |
| 18 |  -78 |
| 19 |  -77 |
| 20 | -101 |
| 21 |  -91 |
| 22 | -114 |
| 23 | -108 |
| 24 |  -72 |
| 25 |  -75 |
| 26 |  -84 |
```

### panid
Get/Set the (extended) PAN ID of the node.

#### `panid [-x]`
Get the PAN ID or extended PAN ID of the Zigbee device node.

```bash
esp> panid
0x74e5
```

```bash
esp> panid -x
0x744dbdfffe602d57
```

#### `panid [-x] <addr:ADDR>`
Set the PAN ID or extended PAN ID of the Zigbee device node.

```bash
esp> panid 0xabcd
```

```bash
esp> panid -x 0x0123456789abcdef
```


### ping
Ping over Zigbee

> **Note:** ping_iperf_test cluster (0xff01) should be registered with the stack first.

#### `ping -d <addr:ADDR> --dst-ep=<u8:EID> -e <u8:EID> -l <u16:DATA>`
- `-d, --dst-addr=<addr:ADDR>`: Destination address.
- `--dst-ep=<u8:EID>`: Destination endpoint id.
- `-e, --src-ep=<u8:EID>`: Source endpoint id.
- `-l, --payload-len=<u16:DATA>`: Payload length in byte of the ping command.
- `-t, --timeout=<u32:DATA>`: Time to wait for response in millisecond, default: 2000

```bash
esp> ping -e 2 --dst-ep 2 -d 0x5da9 -l 10
I (109594) ping_iperf_test: Request to ping address: 0x5da9
I (109654) ping_iperf_test: Ping request success
I (109664) esp-zigbee-console: Receive Zigbee action(0x1040) callback
I (109664) ping_iperf_test: RECEIVE PING RESPONSE from 0x5da9 with 10 bytes, rtt: 69 ms
```


### reboot
Reboot the device immediately.

```bash
esp> reboot
Reboot the device
```

### role
Get/Set the Zigbee role of a device.

Supported device role:

- `zc`: Zigbee coordinator
- `zr`: Zigbee router
- `zed`: Zigbee end device

Get the role of the Zigbee device.

```bash
esp> role
zr
```

Set the role of the Zigbee device.

```bash
esp> role zc
esp> role
zc
```


### route
Route information.

#### `neighbor table`
Dump the route table in current node.

```bash
|Index|DestAddr|NextHop |Expiry| State  |Flags |
+-----+--------+--------+------+--------+------+
|   1 | 0x3095 | 0x83a6 |   59 | Active | 0x00 |
```


### start
Start Zigbee stack.

```bash
esp> start
Start Zigbee stack
```


### tl
TouchLink configuration.

#### `tl timeout [<u32:TIMEOUT>]`
Set touchlink target timeout.

```bash
esp> tl timeout 100
```

#### `tl rssi [<int:RSSI>]`
Get/Set touchlink target rssi threshold.

```bash
esp> tl rssi
-64
```

> **Note:** To correctly set the RSSI to negative values, please use `--` to indicate the end of options.

```bash
esp> tl rssi -- -53
```

#### `tl key [<hex:KEY128>]`
Set touchlink master key.

```bash
tl key 0x0123456789abcdeffedcba9876543210
```
#### `tl keymask <u16:mask>`
Set touchlink key mask.

Enable master key
```bash
tl keymask 0x10
```

Enable cetification key
```bash
tl keymask 0x8000
```

Enable both master key and cetification key
```bash
tl keymask 0x8010
```

### trace
Configure Zigbee stack trace log.

> **NOTE:** The command only supported when `ZB_DEBUG_MODE` is enabled.

#### `trace <LEVEL> <MASK>`
Configure the minimum level and modules of the trace log to output.

Please refer to [esp_zigbee_trace.h](../esp-zigbee-lib/include/esp_zigbee_trace.h) for available values.

To enable `WARN` level for `MAC` and `NWK` layers:
```bash
esp> trace 1 0x000C
```


### zcl
Zigbee Cluster Library management.

Common options:
- `-d <addr:ADDR>`: Destination address of the command.
- `--dst-ep <u8:EID>`: Destination endpoint of the command.
- `-e <u8:EID>`: Source endpoint of the command.
- `--profile=<u16:PID>`: Profile id of the command.
- `-c <u16:CID>`: Cluster id of the command.
- `-r <ROLE>`: Role of the cluster the command sent to. `S` for server, `C` for client, default: `S`.

Destination address mode selection:
- If neither endpoint nor address of the destination were specified, the destination would be determined
  by bindings. (DstAddrMode 0x00 of APSDE-DATA.request)
- If only the short address is specified, the command will be sent by group addressing.
  (DstAddrMode 0x01 of APSDE-DATA.request)
- If both endpoint and short address is specified, the command will be sent by short address.
  (DstAddrMode 0x02 of APSDE-DATA.request)
- If both endpoint and IEEE address is specified, the command will be sent by IEEE address.
  (DstAddrMode 0x03 of APSDE-DATA.request)

#### `zcl send_gen <CMD> [options]`
Send general command.

Use `-a <u16:AID>` to specify the attribute id the command is operating on.

Use `-t <u8:TID>` to specify the attribute type id.

Use `-v <hex:DATA>` to specify the attribute value, raw data in HEX format.

Supported commands:

- `read`: Read attribute.
  ```bash
  esp> zcl send_gen read -d 0xb55c --dst-ep 1 -e 2 -c 6 -a 0
  I (69915) cli_cmd_zcl: Read response: endpoint(2), cluster(0x06)
  I (69925) cli_cmd_zcl: attribute(0x00), type(0x10), data size(1)
  I (69925) : 0x408188d6   00                                                |.|
  ```
- `write`: Write attribute.
  ```bash
  esp> zcl send_gen write -d 0xb55c --dst-ep 1 -e 2 -c 6 -a 0 -t 0x10 -v 0x01
  I (788775) cli_cmd_zcl: Write response: endpoint(2), cluster(0x06)
  I (788775) cli_cmd_zcl: attribute(0x00), status(0x88)
  ```
- `report`: Report attribute.
  ```bash
  esp> zcl send_gen report -d 0xdc59 --dst-ep 2 -e 1 -c 6 -a 0
  ```
- `config_rp`: Configure reporting.
  ```bash
  esp> zcl send_gen config_rp -d 0xcb9a --dst-ep 1 -e 2 -c 6 -a 0 -t 0x10
  I (277959) cli_cmd_zcl: Config report response: endpoint(2), cluster(0x06)
  I (277959) cli_cmd_zcl: attribute(0xffff), status(0x0), direction(255)
  ```
- `read_rp_cfg`: Read reporting configuration.
  ```bash
  esp> zcl send_gen read_rp_cfg -d 0xcb9a --dst-ep 1 -e 2 -c 6 -a 0
  I (368059) cli_cmd_zcl: Read report configure response: endpoint(2), cluster(0x06), attribute(0x00)
  ```
- `disc_attr`: Discover attributes.
  ```bash
  esp> zcl send_gen disc_attr -d 0xb55c --dst-ep 1 -e 2 -c 6
  I (885865) cli_cmd_zcl: Discover attribute response: endpoint(2), cluster(0x06)
  I (885865) cli_cmd_zcl: attribute(0x00), data type(0x10)
  ```


#### `zcl send_raw [options]`
Send cluster specific raw command.

Use `--cmd <u8:CMD_ID>` to specify the command id.

Use `-p <hex:DATA>` to specify the raw payload data of the command.

Use `-n` to perform a dry run. Do not send the command, just dump the content.

```bash
esp> zcl send_raw -n -d 0x0000 --dst-ep 1 -e 2 -c 2 --cmd 0x00 -p 0x1234567890
Send request:
Mode[2]: e:2 -> e:1, addr:0x0000
prfl:0x0104, c:0x0002, dir:S, cmd:0x00
I (13859) : 0x40815970   12 34 56 78 90                                    |.4Vx.|
```

```bash
esp> zcl send_raw -d 0xb55c --dst-ep 1 -e 2 -c 6 --cmd 0x01
```

### zdo
Zigbee Device Object management.

#### `zdo request <INFO> -d <addr:ADDR> [-e <u8:EID>]`
Request information from Zigbee device node.

Supported information types:

- `node_desc`: Get the node descriptor of a device node.
  ```bash
  esp> zdo request node_desc -d 0x3ed5
  node_desc request to [addr:0x3ed5] status: 0
  I (1335839) : 0x40815b34   01 40 8e 34 12 6c 4d 06  00 2c 4d 06 00           |.@.4.lM..,M..|
  ```
- `active_ep`: Get the list of endpoints on a device node with simple descriptors.
  ```bash
  esp> zdo request active_ep -d 0x3ed5
  active_ep request to [addr:0x3ed5] status: 0
  active ep: [1, 242]
  ```
- `simple_desc`: Get the simple descriptor of a Zigbee device node on a specified endpoint. \
  `-e <u8:EID>` is required to specify the endpoint.
  ```bash
  esp> zdo request simple_desc -e 1 -d 0x3ed5
  simple_desc request to [addr:0x3ed5] status: 0
  ep:1 profile:0x0104 dev:0x100 dev_ver:0x0
  in: [0x0000, 0x0003, 0x0004, 0x0005, 0x0006]
  out: []
  ```
- `nwk_addr`: Get the short address of a device node based on its known 64-bit IEEE address.
  ```bash
  esp> zdo request nwk_addr -d 0x744dbdfffe602d57
  nwk_addr request to [addr:0x2d57] status: 0
  nwk address: 0x4599
  ```
- `ieee_addr`: Get the 64-bit IEEE address of a device node based on its known short address.
  ```bash
  esp> zdo request ieee_addr -d 0x3ed5
  ieee_addr request to [addr:0x3ed5] status: 0
  ieee address: 0x744dbdfffe602d57
  ```
- `neighbors`: Get the Neighbor Table of a device node.

  Neighbor info explanation:
    - If the device type ends with asterisk, then the device is permitting joining.
      Otherwise, the device is not permitting joining.
    - "Rel" stands for relationship, which supports:
        - "P" stands for parent
        - "C" stands for child
        - "S" stands for sibling
        - "O" stands for others
        - "c" stands for previous child
        - "u" stands for unauthenticated child
  ```bash
  esp> zdo request neighbors -d 0x4599
  neighbors request to [addr:0x4599] status: 0
  |Index| ExtPanID           |NwkAddr | MacAddr            |Type |Rel|Depth| LQI |
  +-----+--------------------+--------+--------------------+-----+---+-----+-----+
  |   0 | 0x4831b7fffec02bbc | 0x07ca | 0x4831b7fffec02bbc | ZR* | S |   0 | 255 |
  esp> zdo request neighbors -d 0x07ca
  neighbors request to [addr:0x07ca] status: 0
  |Index| ExtPanID           |NwkAddr | MacAddr            |Type |Rel|Depth| LQI |
  +-----+--------------------+--------+--------------------+-----+---+-----+-----+
  |   0 | 0x4831b7fffec02bbc | 0x4599 | 0x744dbdfffe602d57 | ZR  | S |   1 | 255 |
  ```
- `bindings`: Get the Binding Table of a device node.
  ```bash
  esp> zdo bind -c 6 -S 1 -D 1 -s 0x3ed5 -d 0x744dbdfffe602d57
  bind request to [addr:0x3ed5] status: 0
  esp> zdo bind -c 6 -S 1 -D 1 -s 0x3ed5 -d 0x4831b7fffec02bbc
  bind request to [addr:0x3ed5] status: 0
  esp> zdo request bindings -d 0x3ed5
  bindings request to [addr:0x3ed5] status: 0
  |Index| Src_Addr           |Src_E|Cluster | Dst_Addr           |Dst_E|
  +-----+--------------------+-----+--------+--------------------+-----+
  |   0 | 0x744dbdfffe602d57 |   1 | 0x0006 | 0x744dbdfffe602d57 |   1 |
  |   1 | 0x744dbdfffe602d57 |   1 | 0x0006 | 0x4831b7fffec02bbc |   1 |
  esp>
  ```

#### `zdo annce`
Announce current node (by broadcasting `Device_annce`).

#### `zdo match [-i <u16:CID>]... [-o <u16:CID>]... [-p <u16:PID>] -d <addr:ADDR>`
Get matched devices (supporting a specific simple descriptor criterion).

If there were matched devices, the information would be printed as `matched device: <ADDR>:<ENDPOINT>`.

```bash
esp> zdo match -i 0 -i 3 -i 4 -i 5 -i 6 -p 0xFFFF -d 0xFFFF
match request to [addr:0xffff] status: 0
matched device: 0x3ed5:1
```

#### `zdo bind [-r] -c <u16:CID> -S <u8:EID> [-D <u8:EID>] -s <addr:ADDR> -d <hex:ADDR>`
Request the node to bind/unbind to device.

Use `-r` to remove specific bindings.

If no destination endpoint is specified via (`-D <u8:EID>`) and the destination address provided by
`-d <addr:ADDR>` is short address, the destination address mode of the binding would be set to group
addressing mode.

Assume that we have a pair of device with the following setup:
| Configuration | Remote             | Local              |
| :------------ | -----------------: | -----------------: |
| Short Address | 0x3ed5             | 0x6db5             |
| IEEE Address  | 0x744dbdfffe602d57 | 0x4831b7fffec02bbc |
| Endpoint      | 1                  | 1                  |
| Device on EP  | HA on_off_light    | HA on_off_switch   |
| Endpoint      | 2                  | 2                  |
| Device on EP  | HA on_off_switch   | HA on_off_light    |

Request the remote device bind `on_off cluster(0x06)` on endpoint 1 with that on endpoint 2 at local device:
```bash
esp> zdo bind -c 6 -S 1 -D 2 -s 0x3ed5 -d 0x4831b7fffec02bbc
bind request to [addr:0x3ed5] status: 0
```
Request the remote device bind `on_off cluster(0x06)` on endpoint 1 with that on endpoint 2:
```bash
esp> zdo bind -c 6 -S 1 -D 2 -s 0x3ed5 -d 0x744dbdfffe602d57
bind request to [addr:0x3ed5] status: 0
```
After the two binding requests, check the binding table on remote device:
```bash
esp> zdo request bindings -d 0x3ed5
bindings request to [addr:0x3ed5] status: 0
|Index| Src_Addr           |Src_E|Cluster | Dst_Addr           |Dst_E|
+-----+--------------------+-----+--------+--------------------+-----+
|   0 | 0x744dbdfffe602d57 |   1 | 0x0006 | 0x4831b7fffec02bbc |   2 |
|   1 | 0x744dbdfffe602d57 |   1 | 0x0006 | 0x744dbdfffe602d57 |   2 |
esp>
```

#### `zdo nwk_open [-t <u8:TIMEOUT>] -d <addr:ADDR>`
Request the node to open the network for specific duration.

Use `-t <u8:TIMEOUT>` to specify the duration for network opening.

#### `zdo nwk_leave [-cr] -d <addr:ADDR>`
Request the node to leave the network.

Use `-c` to request the node remove all its children when leaving the network.

Use `-r` to request the node rejoin after leaving the network.


### zgp
Zigbee Green Power Profile management.


### zha
Zigbee Home Automation Profile.

#### `zha add <u8:EID> <device_name>`
Add device by device type name.

Example: [`dm show`](#dm-show)

Supported devices:
- on_off_switch
- configuration_tool
- mains_power_outlet
- door_lock
- door_lock_controller
- on_off_light
- color_dimmable_light
- color_dimmable_switch
- light_sensor
- shade
- shade_controller
- window_covering
- window_covering_controller
- thermostat
- temperature_sensor
