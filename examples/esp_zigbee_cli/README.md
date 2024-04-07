# ESP Zigbee CLI Reference

The Zigbee CLI exposes configuration and management APIs via a command line interface. Manipulate Zigbee stack related function by using CLI, which can also be used with additional application code.  

## Parameter Explanation

The command argument description uses the following convention:  
command **[arg]** : square brackets mean that an argument is optional.  
command **<d:arg1> <h:arg2>**: a single letter before an argument name defines the format of the argument:  
&nbsp;&nbsp;&nbsp;&nbsp;h: hexadecimal strings (arg2),  
&nbsp;&nbsp;&nbsp;&nbsp;d: decimal values (arg1).  
command **<d/h:arg> ...** : the ellipsis after an argument means that the preceding argument can be repeated several times.  

## Zigbee CLI Command List
- [radio](#radio)  
- [role](#role)
- [extpanid](#extpanid)
- [panid](#panid)
- [channel](#channel)
- [channel_mask](#channel_mask)
- [start](#start)
- [commissioning](#commissioning)
- [ic](#ic)
- [legacy](#legacy)
- [nwktype](#nwktype)
- [nwkkey](#nwkkey)
- [nwkstate](#nwkstate)
- [factory](#factory)
- [child](#child)
- [touchlink](#touchlink)
- [active_ep](#active_ep)
- [simple](#simple)
- [match](#match)
- [bind_on](#bind_on)
- [bind_off](#bind_off)
- [mgmt_bind](#mgmt_bind)
- [mgmt_lqi](#mgmt_lqi)
- [nwk_addr](#nwk_addr)
- [ieee_addr](#ieee_addr)
- [eui64](#eui64)
- [short](#short)
- [mgmt_leave](#mgmt_leave)
- [device_announcement](#device_announcement)
- [zcl_command](#zcl_command)
- [attr_read](#attr_read)
- [attr_write](#attr_write)
- [subscribe_on](#subscribe_on)
- [subscribe_off](#subscribe_off)
- [ping](#ping)
- [reset](#reset)


## Zigbee CLI Command Details

### radio
Configure the IEEE802154 radio state of device.

*bdb -d <on/off>*   
- <on/off>: Turn on(default) or off IEEE802154 radio

Get help
```bash
on: turn on radio
off: turn off radio
I (52374) : Done
```
Set radio to off
```bash
> bdb -d off
I (116954) : IEEE802154 radio off
I (116954) : Done
```
Set radio to on
```bash
> bdb -d on
I (142464) : IEEE802154 radio on
I (142464) : Done
```

get radio state
```bash
> bdb -d get
I (239694) : Radio is on
I (239694) : Done
```

### role
Configure the role of device in zigbee network.

*bdb -r <zc/zr/zed>*   
- <zc/zr>: The role indicates Zigbee coordinator or Zigbee router.

**Note**
- Set action only before bdb start. Read action only after bdb start.
- The zed role is the router with zed functionality.

Set the `coordinator` or `router` role to the Zigbee device.
```bash
> bdb -r zc
Coordinator role set. 
```
```bash
> bdb -r zr
Router role set.
```

Get Zigbee role of a device.

*bdb -r get*
```bash
> bdb -r get
zr
```

### extpanid
Configure the extended personal area network ID(panid) for zigbee to find network.

*bdb -e <h:extpanid>*   
- <h:extpanid>: The 64-bit extended panid of Zigbee device.

**Note**
- Set action only before bdb start. Read action only after bdb start.

Set Zigbee `extended panid` value.
```bash
> bdb -e 1122334455667788
I (605714) : set extpanid: 0x1122334455667788
```

Get Zigbee `extended panid` value.

*bdb -e get*  
```bash
> bdb -e get
I (611644) : get extpanid: 0x1122334455667788
```

### panid
Configure the personal area network ID(panid) for zigbee to find the device.

*bdb -p <h:panid>*  
- <h:panid>: The 2 bytes panid of Zigbee device.

**Note**
- Set action only before bdb start. Read action only after bdb start.

Set Zigbee `panid` value.
```bash
> bdb -p 1122
I (977414) : set panid: 0x1122
```

Get Zigbee `panid` value.

*bdb -p get*  
```bash
> bdb -p get
I (983554) : get panid: 0x1122
```

### channel
Configure the 2.4GHz `channel` for Zigbee to establish communication.

*bdb -c <d:n>*  
- <d:n>: A integer type ranges from 11 to 26, Oherwise, treat n as bitmask.

**Note**
- Set action only before bdb start. Read action only after bdb start.

Set Zigbee `channel` to 24.
```bash
> bdb -c 24
I (977414) : Setting channel to 24
```

Get Zigbee 2.4GHz channel:   

*bdb -c get*   
```bash
> bdb -c get
I (1064419) : Primary channel(s): 24
I (1064429) : Secondary channel(s): 24
```

### channel_mask
Configure the 2.4GHz `channel` for Zigbee to establish communication.

*bdb -h <x:channel_mask> <x:channel_mask>*  
- <x:primary_channel_mask>: A integer type ranges from 0x00000800 to 0x07FFF800 for the secondary channel, Oherwise, treat as bitmask.
- <x:secondary_channel_mask>: A integer type ranges from 0x00000800 to 0x07FFF800 for the secondary channel, Oherwise, treat as bitmask.

**Note**
- Set action only before bdb start. Read action only after bdb start.

Set Zigbee `channel`
```bash
> bdb -h help
I (55834) : 
Primary and Secondary channel is range from 0x00000800 to 0x07FFF800
I (55834) : Done
> bdb -h 0x00000800
I (73034) : Set primary channel: 0x00000800
I (73034) : Done
> bdb -h 0x00000800 0x07FFF800
I (85624) : Set primary channel: 0x00000800
I (85634) : Set secondary channel: 0x07fff800
I (85634) : Done
> bdb -h get
I (94244) : 
Primary: 0x00000800
Secondary: 0x07fff800
I (94254) : Done
```

### commissioning
Configure the commissioning mode for Zigbee to establish network.

*bdb -a <mode>*  
- <mode>: Zigbee commissioning mode

**Note**
- Set action only after bdb start.

Set Zigbee `commissioning mode` to establish network
```bash
 bdb -s
I (16124) : Started router
I (16134) : Done
I (16144) ESP_ZB_CLI: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (16144) ESP_ZB_CLI: Zigbee stack startup
> bdb -a help
I (18774) : 
init: network initialized
steering: network steering
form: network formation
binding: finding N binding                      
initiator: touchlink initiator commissioning
target: touchlink target commissioning
I (18774) : Done
> bdb -a init
I (20704) : Done
I (20714) ESP_ZB_CLI: Device started up in  factory-reset mode
> bdb -a steering
I (33974) : Done
> W (34164) ESP_ZB_CLI: Not found network
> bdb -a form
I (48494) : Done
> W (48664) ESP_ZB_CLI: Network(0x5e2e) closed, devices joining not allowed.
I (48674) ESP_ZB_CLI: Join or form distributed network
I (48674) ESP_ZB_CLI: Formed network successfully (Extended PAN ID: 60:55:f9:ff:fe:f7:2e:46, PAN ID: 0x5e2e, Channel:11, Short Address: 0x552c)
```

### start
Start the commissioning process.

```bash
> bdb -s
I (1748414) : Started coordinator
I (1748494) : Done
```

### ic
Configure the install code of Zigbee for device to join network.

*bdb -i set <h:install code>*
- <h:install code>:  an ASCII-encoded hex that includes CRC-16/X-25, which will be set into the production device.

*bdb -i add <h:install code> <h:eui64>*
- <h:install code>:  an ASCII-encoded hex that includes CRC-16/X-25, which will be added into the production device.
- <h:eui64>:  An 64-bit [extended unique identifier](#eui64) for the Zigbee node.

*bdb -i policy <enable|disable>*
- <enable|disable>: Enable or disable code policy install for the trust center.

**Note**
- Set and define policy only before bdb start. Add action only after bdb start.
- bdb ic set must only be used on a joining device(ZR/ZED).
- bdb ic add must only be used on a coordinator. For <h:eui64>, use the address of the joining device.
- bdb ic policy must only be used on a coordinator.
- Provide the `install code` as an ASCII-encoded hex that includes CRC-16/X-25.
- For production devices, an install code must be installed by the production configuration present in flash.

Set `install code` on the Zigbee device; 

Add information about the `install code` to trust center and set the trust center `install code` policy in Zigbee Router and Zigbee End Device.
```bash
> bdb -i set 83FED3407A939723A5C639B26916D505C3B5
I (53407914) : IC:83fed3407a939723a5c639b26916d505 CRC:c3b5
I (53407914) : Done
> bdb -i policy enable
I (53744964) : Done
> 
> bdb -r zr
I (53744964) : Done
>  
> bdb -s 
I (53763424) : Done
```

In Zigbee Coordinator
```bash
> bdb -i policy enable
I (53744964) : Done
> 
> bdb -r zc
I (53744964) : Done
> 
> bdb -s 
I (53763424) : Done
> bdb -i add 83FED3407A939723A5C639B26916D505C3B5 0B010E2F79E9DBFA
I (53805304) : IC:83fed3407a939723a5c639b26916d505 CRC:c3b5
I (53805304) : eui64::fadbe9792f0e010b
I (53805304) : Done
```

### legacy
Configure the legacy option for Zigbee device.

*bdb -l <enable/disable>*
- <enable/disable>: Enable or disable the legacy device support.

**Note**
- Set action only before bdb start.

```bash
> bdb -l enable
I (54039534) : Done
> bdb -l disable
I (54046354) : Done
```

### nwktype
Set the type for zigbee network.

*bdb -t <type>*
- <h:key>:  An 16-Byte for network key of zigbee.

**Note**
- Set action only before bdb start.
bdb
```bash
> bdb -t help
I (368414) : 
c: centralized network
d: distributed network
I (368414) : Done
> bdb -t c
I (394314) : Set centralized network
I (394314) : Done
> bdb -t get
I (398334) : Centralized network
I (398334) : Done
>
```


### nwkkey
Set the network key for zigbee device to encrypt network message.

*bdb -n <h:key>*
- <h:key>:  An 16-Byte for network key of zigbee.

**Note**
- Set action only before bdb start.


```bash
> bdb -n 00112233445566778899aabbccddeeff
Set key:00112233445566778899aabbccddeeff
I (14364) : Done
```

### nwkstate
Set the state for zigbee network.

*bdb -t <state>*
- <state>:  The state of zigbee network

**Note**
- Set action only after bdb start.

Set the zigbee network state
```bash
> bdb -o help
I (248234) : 
close: Close network
open x: open network x seconds
I (248234) : Done
> bdb -o open 112
I (260774) : Open network 112 seconds
I (260784) : Done
> bdI (261654) ESP_ZB_CLI: Network(0x5e2e) is open for 112 seconds
> bdb -o close
I (267444) : Close network
I (267444) : Done
> W (268274) ESP_ZB_CLI: Network(0x5e2e) closed, devices joining not allowed.
>
```

### factory
Perform a factory reset via local action.

*bdb -f <level>*
- <level>: The level of factory reset

```bash
> bdb -f help
I (411844) : 
0: reset_local
1: restart
2: earse_nvram
I (411844) : Done
> bdb -f 1
I (450534) : Restart
```

### child
Set the amount of child devices.  

*bdb -m <d:number>*  
- <d:number>: The supported number of children on Zigbee device.

**Note**
- Setting only before bdb start.

Set the max amount of children to 1 for Zigbee device.
```bash
> bdb -m 1
I (226424) : Setting max children to: 1
```

### touchlink
Zigbee Touchlink commands list

*tlk -t <d:timeout>*
- <d:timeout>: Configure Touchlink target timeout.

*tlk -r <d:rssi>* 
- <d:rssi> Configure RSSI threshold of touchlink.

*tlk -k <n:key>*  
- <n:key> Configure master key of touchlink.


**Note**
- Setting only before bdb start.

The process of using cli to establish Zigbee network
- Initiator
```bash
> bdb -r zr
I (79294) : Router role set
> bdb -t d
I (82504) : Set distributed network
I (82504) : Done
> bdb -c 11
I (89614) : Setting channel to 11
I (89614) : Done
> tlk -k 00112233445566778899aabbccddeeff
I (146654) : 
Set touchlink key:00112233445566778899aabbccddeeff
I (146654) : Done
I (146654) : Done
> bdb -s
I (180994) : Started router
I (181004) : Done
I (181014) ESP_ZB_CLI: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (181014) ESP_ZB_CLI: Zigbee stack startup
> bdb -i init
> bdb -a init
I (192764) : Done
I (192774) ESP_ZB_CLI: Device started up in  factory-reset mode
> bdb -a initiator
I (198484) : Done
> I (202344) ESP_ZB_CLI: Touchlink initiator receives the response for started network
I (202344) ESP_ZB_CLI: Response is from profile: 0x0104, endpoint: 64, address: 0x6055f9fffef72e16
W (203464) ESP_ZB_CLI: Network(0xe3f5) closed, devices joining not allowed.
I (203464) ESP_ZB_CLI: Commissioning successfully, network information (Extended PAN ID: 60:55:f9:ff:fe:f7:2e:16, PAN ID: 0xe3f5, Channel:11, Short Address: 0x09f9)
I (203474) ESP_ZB_CLI: Touchlink target commissioning finished
```

- Target
```bash
> bdb -r zr
I (4221) : Router role set
> bdb -t d
I (7741) : Set distributed network
I (7741) : Done
> bdb -c 11
I (9491) : Setting channel to 11
I (9491) : Done
> tlk -t help
I (34341) : Duration of Touchlink target commissioning
I (34341) : Done
> tlk -t 60
I (40471) : Duration: 60 seconds
I (40471) : Done
> tlk -r help
I (47351) : RSSI threshold(default -64) of Touchlink target, which ranges from -127 to 127
I (47351) : Done
> tlk -r -54
I (60801) : RSSI: -54
I (60801) : Done
> tlk -r get
I (68151) : RSSI: -54
I (68151) : Done
> bdb -s
I (154411) : Started router
I (154421) : Done
I (154431) ESP_ZB_CLI: ZDO signal: ZDO Config Ready (0x17), status: ESP_FAIL
I (154431) ESP_ZB_CLI: Zigbee stack startup
> bdb -a init
I (159071) : Done
I (159081) ESP_ZB_CLI: Device started up in  factory-reset mode
> bdb -a target
I (169831) : Done
I (169851) ESP_ZB_CLI: Touchlink target is ready, awaiting commissioning
> W (198441) ESP_ZB_CLI: Network(0xe3f5) closed, devices joining not allowed.
I (198451) ESP_ZB_CLI: Commissioning successfully, network information (Extended PAN ID: 60:55:f9:ff:fe:f7:2e:16, PAN ID: 0xe3f5, Channel:11, Short Address: 0xdc73)
I (198461) ESP_ZB_CLI: Touchlink target commissioning finished
I (200771) ESP_ZB_CLI: ZDO signal: ZDO Device Update (0x30), status: ESP_OK
I (200851) ESP_ZB_CLI: New device commissioned or rejoined (short: 0x09f9)
```

### active_ep
Send an active endpoint request to the node addressed by the [destination address](#short).

*zdo -a <h:16-bit destination address>*  
- <h:16-bit destination address>: A short 16-bit address of zigbee device.

**Note**
- All active endpoints of the device will be returned as the result with the destination address.

Send the `active endpoint request` to the Zigbee node with `short address(0x78D9)`.
```bash
>  zdo -a 0x78D9
I (749364) : src_addr=78D9
I (749364) : ep=10,242
Done
```

### simple
Send a simple descriptor request to obtain the profile ID, input clusters, output clusters, application device ID and application device version of Zigbee node addressed by the [destination address](#short) and [endpoint](#active_ep).

*zdo -c <h:16-bit destination address> <d:endpoint>*  
- <h:16-bit destination address>: The 16-bit short address is the destination address for the request.
- <d:endpoint>: The endpoint ID of destination device for the request.

Send a `simple descriptor request` to the `endpoint ID(10)` of Zigbee node with `short address(0xefba)`.
```bash
> zdo -c 0xefba 10
> src_addr=0xEFBA ep=10 profile_id=0x0102 app_dev_id=0x0 app_dev_ver=0x5
  in clusters=0x0000,0x0003,0x0004,0x0005,0x0006,0x0008,0x0300 out clusters=0x0300
I (1180874) : Done
> 
```

### match
Send a match descriptor request to the destination address node that is a query about the requested address node of the  [endpoint](#active_ep).


*zdo -m <h:16-bit destination address>  
&emsp;&emsp;&emsp;&nbsp;<h:requested address/type>  
&emsp;&emsp;&emsp;&nbsp;<h:profile ID>  
&emsp;&emsp;&emsp;&nbsp;<d:number of input clusters>  
&emsp;&emsp;&emsp;&nbsp;<d:number of output clusters> [<h:output cluster IDs>...]  
&emsp;&emsp;&emsp;&nbsp;[timeout]*  
- <h:16-bit destination address>: The match descriptor request's destination address, which is a 16-bit short of Zigbee device. It is used for IEEE address mapping.
- <h:requested address/type>: The NWK address of internet is the same as destination address generally.
- <h:profile ID>: The value will be matched at the destination.
- <d:number of input clusters>: The number of input clusters provided for matching within the inputting cluster list.
- [<h:input cluster IDs>]: The inputting cluster list will be matched at the destination.
- <d:number of output clusters>: The number of output clusters provided for matching within the outputting cluster list.
- [<h:output cluster IDs>]: The outputting cluster list will be matched at the destination.
- [timeout]: The match descriptor request will be delayed `timeout` seconds, the default value is 5 seconds.

**Note**
- The number of input clusters or number of output clusters must be at least one.

Send a match descriptor request to the Zigbee node with a `short address (0xfffd)`, specifying an `input cluster` of 6 and an `output cluster` of 0 within the `Home Automation Profile (0x0104)`.
```bash
> zdo -m 0xfffd 0xfffd 0x0104 1 6 0
I (1180864) : dst addr:fffd
I (1180864) : req addr:fffd
I (1180864) : profile id:104
I (1180864) : num_in_clusters:1
I (1180874) : num_out_clusters:0
I (1180874) : Sending broadcast request.
I (1180874) : src_addr=fffd ep=10
I (1180874) : Done
```

### bind_on
Create a binding between two endpoints on two nodes.  

*zdo -b on <h:source eui64> <d:source ep> <h:destination addr>  
&emsp;&emsp;&emsp;&emsp;&nbsp;<d:destination ep> <h:source cluster id> <h:request dst addr>*  
- <h:source eui64>: A 64-bit IEEE address for the source node.
- <d:source ep>: The source endpoint provided for the binding entry.
- <h:destination addr>: A 64-bit IEEE destination provided for the binding entry.
- <d:destination ep>: The destination endpoint provided for the binding entry.
- <h:source cluster id>: The identifier of the cluster on the source device that is bound to the destination.
- <h:request dst addr>: A 16-bit short address of destination device.

Create bound connection between a device identified by  `source eui64(f4ce36840d75b6dc)` and `source enpoint(64)`, and a device identified by `destination addrress(f4ce36b6ba35bed1)` and `destination endpoint(64)`. The connection is created for ZCL commands and attributes assigned to the ZCL cluster `source cluster id(3)` on the `request destination address(C698)` node.
```bash
> zdo -b on f4ce36840d75b6dc 64 f4ce36b6ba35bed1 64 3 C698
Done
```

### bind_off
Remove a binding between two endpoints on two nodes.

*zdo -b off <h:source eui64> <d:source ep> <h:destination eui64>  
&emsp;&emsp;&emsp;&emsp;&nbsp;<d:destination ep> <h:source cluster id> <h:request dst addr>*  
- <h:source eui64>: A 64-bit IEEE address for the source node.
- <d:source ep>: The source endpoint provided for the binding entry.
- <h:destination addr>: A 64-bit IEEE destination provided for the binding entry.
- <d:destination ep>: The destination endpoint provided for the binding entry.
- <h:source cluster id>: The identifier of the cluster on the source device that is bound to the destination.
- <h:request dst addr>: A 16-bit short address of destination device.

Remove the bound connection between a device identified by `source eui64(f4ce36840d75b6dc)` and `source enpoint(64)`, and a device identified by `destination addrress(f4ce36b6ba35bed1)` and `destination endpoint(64)`. The connection is created for ZCL commands and attributes assigned to the ZCL cluster `source cluster id(3)` on the `request destination address(C689)` node.
```bash
> zdo -b off f4ce36840d75b6dc 64 f4ce36b6ba35bed1 64 3 C698
Done
```

### mgmt_bind
Read the binding table from a node.  

*zdo -d <h:16-bit dst_addr> [d:start_index]*
- <h:16-bit dst_addr>: A 16-bit short address of binding node.
- [d:start_index]: The index of the first entry in the binding table where the reading starts. It is zero by default.

Send a request to the remote node identified by `short address(C698)` to read the binding table through zdo mgmt bind request.
```bash
> zdo -d C698
[idx] src_address       src_endp cluster_id  dst_addr_mode  dst_addr          dst_endp
[  0] f4ce36840d75b6dc     64      0x003           3        f4ce36b6ba35bed1     64
Total entries for the binding table: 1
Done
```

### mgmt_lqi
Read the a neighbor table for a node.

*zdo -l <h:short_addr> [d:start index]*  
- <h:16-bit dst_addr>: A 16-bit short address of binding node.
- [d:start_index]: The index of the first entry in the binding table where the reading starts. It is zero by default.

Send a ZDO mgmt lqi Request command to a `short address(0xC698)` of remote node and ask it to return its neighbor table.
```bash
> zdo -q 0xC698
I (28711) : [idx] ext_pan_id            ext_addr     short_addr flags permit_join depth     lqi
I (28711) : [   0] 74fa0801a003f784 74fa0801a003f784 0x0000      0x84     1       0         255
I (28711) : [   1] 74fa0801a003f784 f4ce36b6ba35bed1 0x4eaa      0x25     0       2         255
I (28731) : ZDO request 161480 complete
> Done
```

### nwk_addr
Resolve the network short address by a EUI64 address.

*zdo -n <h:eui64>*
- <h:eui64>: The 64-bit IEEE network address provided for returning its network short address.

Get the `short address` by resolving the `EUI64`.
```bash
> zdo -n f4ce36840d75b6dc 
I (122147) : nwk_addr:7655
Done
```

### ieee_addr
Resolve the EUI64 address by sending the short address request.

*zdo -i <h:short_addr>*  
- <h:short_addr>: The 16-bit network short address provided for returning its network EUI64 address.

Get the `EUI64` by resolving the `short address`.
```bash
>  zdo -i 7655
I (166117) : f4ce36840d75b6dc
Done
```

### eui64
Get the EUI64 address of the Zigbee device.  

*zdo -e*  

```bash
> zdo -e 
I (201817) : 74fa0801a003f784
Done
```

### short
Get the short 16-bit address of the Zigbee device.  

*zdo -s*  

```bash
> zdo -s
0000
Done
```

### mgmt_leave
Send a zdo mgmt leave request to a remote device to leave the network.

*zdo -l <h:16-bit dst_addr> [h:device_address eui64] [children] [rejoin]*
- <h:16-bit dst_addr>: The 16-bit short address of remote device.
- [h:device_address eui64]: The IEEE network address of remote device. If it is omitted or has value 0000000000000000, the remote device at address `<h:16-bit dst_addr>` will remove itself from the network; If the value has other value, it must be a long address corresponding to address `<h:16-bit dst_addr>` or a long address of child node of address `<h:16-bit dst_addr>`;
- [children]: Remove the all children at the destination device.
- [rejoin]: Remove itself and perform the rejoin.

**Note:**
The request is sent with Remove `children` and `rejoin` flags set to 0 by default.
Use options `children` or `rejoin` do change the respective flags to 1.

Send a mgmtleave request to the device with the `short address(0x4eaa)`, and ask it to remove itself from the network.
```bash
> zdo -l 0x4eaa
Done
```

Send a mgmt leave request to the device with the `short address(0x4eaa)`, and ask it to remove itself from the network and perform rejoin.
```bash
> zdo -l 0x4eaa rejoin
Done
```

Send a mgmt leave request to the device with the `short address(0x4eaa)`, and ask it to remove device addressed with `74fa0801a003f784` from the network. If the target device with the `short address(0x4eaa)` has also a long address `74fa0801a003f784`, it will remove itself from the network, If the target device with the `short address(0x4eaa)` has a child with `long address(74fa0801a003f784)`, it will remove the child from the network.
```bash
> zdo -l 0x4eaa 74fa0801a003f784
Done
```

Send a mgmt leave request to the device with the `short address(0x4eaa)`, and ask it to remove itself and all its children from the network.
```bash
> zdo -l 0x4eaa children
Done
```

### device_announcement
Send a zdo device announcement command

*zdo -t*

```bash
> zdo -t
Done
```

### zcl_command
Send a general command to the remote Zigbee node.  

*zcl -c <h:dst_addr> <d:ep> <h:cluster>  
&emsp;&emsp;&ensp;<h:cmd_ID> [profile h:profile] [payload h:payload]  [default]*  
- <h:dst_addr>: The 16-bit destination short address of remote node.
- <d:ep>: The 8-bit endpoint ID of remote node.
- <h:cluster>:  The 16-bit cluster ID provided for the command entry which resides on the endpoint .
- <h:cmd_ID>: The command ID provided by the cluster's attribute support.
- [profile h:profile]: The 16-bit profile ID provided for matching the cluster, by default, it is set to Home Automation Profile(0x0104).
- [payload h:payload]: The string type serves for command, whose length is from 0 to 50, by default, it is empty.
- [default]: If the field is set, the default response will be requested.

**Note**
- Send general command with ID 'cmd_ID' with payload 'payload' to the cluster 'cluster'. The cluster belongs to the profile 'profile', which resides on the endpoint 'ep' of the remote node 'dst_addr'. Optional default response can be set with '-d'.
- By default profile is set to Home Automation Profile
- By default payload is empty
- To send via binding table, set 'dst_addr' and 'ep' to 0.

Send the `factory reset command(0)` to the `endpoint(64)`'s `basic cluster(0x0000)` of Zigbee node with `short address(0xC6498)`.
```bash
> zcl -c 6498 64 0x0000 0
I (154047) : Default Response received, Command: 0, Status: 0
I (154057) : Done

> zcl -c 6498 64 0x0000 0 profile 0x0104
I (328077) : Default Response received, Command: 0, Status: 0
I (328087) : Done

> zcl -c 6498 64 0x0000 0 profile 0x0104 payload 20
I (338727) : Default Response received, Command: 0, Status: 0
I (338737) : Done

> zcl -c 6498 64 0x0000 0 profile 0x0104 payload 20 default
I (344757) : Default Response received, Command: 0, Status: 0
I (344767) : Done
> 
```

### attr_read
Retrieve the attribute value of the remote Zigbee node.

*zcl -a read <h:dst_addr> <d:ep> <h:cluster> <h:profile> <h:attr_id> [switch]*  
- <h:dst_addr>: The 16-bit destination short address of remote node.
- <d:ep>: The 8-bit endpoint ID of remote node.
- <h:cluster>: The 16-bit cluster ID resides on the endpoint.
- <h:profile>: The 16-bit profile ID provided for locating the Zigbee cluster.
- <h:attr_id>: The 16-bit attribute ID's value will be return as result.
- [switch]: The field indicates the command sent from client/server to server/client, by default, sending command to server.

**Note**
- Read the value of the attribute attr_id in the cluster cluster. The cluster belongs to the profile profile, which resides on the endpoint ep of the remote node dst_addr. If the attribute is on the client role side of the cluster, use the "switch" change.

Read the attribute `Reset to Factory Defaults(0x00)` value from the `Home Automation Profile(0x0104)`'s `basic cluster(0x0000)` of Zigbee node with `short address(0x6498)`.
```bash
> zcl -a read 6498 64 0x0000 0x0104 0 
I (688567) : ID: 0 Type: 0x20 Value: 2
I (688577) : Done 
```

### attr_write
Write the attribute value to the remote Zigbee node.  
*zcl -a write <h:dst_addr> <d:ep> <h:cluster> <h:profile> <h:attr_id>   
&emsp;&emsp;&emsp;&emsp;&emsp;<h:attr_type> <h:attr_value> [switch]*
- <h:dst_addr>: The 16-bit destination short address of remote node.
- <d:ep>: The 8-bit endpoint ID of remote node.
- <h:cluster>: The 16-bit cluster ID resides on the endpoint.
- <h:profile>: The 16-bit profile ID provided for locating the Zigbee cluster.
- <h:attr_id>: The 16-bit attribute ID's value will be writen.
- <h:attr_type>: The type of attribute is refered to ZCL spec Table 2-10.
- <h:attr_value>: The max 32-byte value will be set to the relating value of remote node's attribute ID.
- [switch]: The field indicates the command sent from client/server to server/client, by default, sending command to server.

**Note**
- Read the value of the attribute 'attr_id' in the cluster 'cluster'. The cluster belongs to the profile 'profile', which resides on the endpoint 'ep' of the remote node 'dst_addr'. If the attribute is on the client role side of the cluster, use the 'switch' change.

Write the `ZB_ZCL_ATTR_TYPE_U8(0x21)` type `value(0)` to the attribute `Identify(0)` of `Identify cluster(0x0003)` in the `Home Automation Profile(0x0104)` of Zigbee node with `short address(0x6498)`.
```bash
> zcl -a write 6498 64 0x0003 0x0104 0 0x21 0
I (961517) : Done
```

### subscribe_on
Subscribe to the attribute changes on the remote Zigbee node.   
*zcl -s on <h:addr> <d:ep> <h:cluster> <h:profile>  
&emsp;&emsp;&emsp;&emsp;<h:attr_id> <d:attr_type>  
&emsp;&emsp;&emsp;&emsp;[<d:min interval (s)>] [<d:max interval (s)>]*  
- <h:addr>: The 16-bit destination short address of remote node.
- <d:ep>: The 8-bit endpoint ID of remote node, which is of interest to.
- <h:cluster>: The 16-bit cluster ID resides on the endpoint.
- <h:profile>: The 16-bit profile ID provided for locating the Zigbee cluster.
- <h:attr_id>: The 16-bit attribute ID is of interest to you, which will be subscribed.
- <d:attr_type>: The type of attribute is refered to ZCL spec Table 2-10.
- [<d:min interval (s)>] [<d:max interval (s)>]: The interval of report for the attribute changes.

**Note**
- Enable reporting on the node identified by the address addr, with the endpoint ep that uses the profile profile of the attribute attr ID with the type attr type in the cluster.
- The reports must be generated in intervals not shorter than min interval (1 second by default) and not longer than max interval (60 seconds by default).

Subscribe the `ZB_ZCL_ATTR_TYPE_BOOL(0x10)` type attribute `OnOff(0x0000)` of `On/Off(0x0006) cluster` in the `Home Automation Profile(0x0104)` of Zigbee node with `short address(0x6498)`.
```bash
> zcl -s on 6498 64 0x0006 0x0104 0 0x10
I (961517) : Done
```

### subscribe_off
Unsubscribe from the attribute reports.  
*zcl -s off <h:addr> <d:ep> <h:cluster> <h:profile> <h:attr ID> <d:attr type>*    
- <h:addr>: The 16-bit destination short address of remote node.
- <d:ep>: The 8-bit endpoint ID of remote node, which is of interest to.
- <h:cluster>: The 16-bit cluster ID resides on the endpoint.
- <h:profile>: The 16-bit profile ID provided for locating the Zigbee cluster.
- <h:attr_id>: The 16-bit attribute ID is of interest to you, which will be unsubscribed.
- <d:attr_type>: The type of attribute is refered to ZCL spec Table 2-10.

Note:  
Disable reporting on the node identified by the address addr, with the endpoint ep that uses the profile profile of the attribute attr ID with the type attr type in the cluster cluster.  

```bash
> zcl -s off 6498 64 0x0006 0x0104 0 0x10
I (961517) : Done
```
### ping
Issue a ping over ZCL.

*zcl -p <h:dst_addr> <d:payload size>*
- <h:dst_addr>: The 16-bit destination short address of remote node.
- <d:payload size>: The payload size must be less than 79 bytes.

Note:
Issue a ping-style command to another CLI device of the address dst_addr by using payload_size bytes of payload.  
```
Ping with echo, without the APS acknowledgement:  
|----App 1--------|Node 1|---------Node 2--|  
|----ping-->------|---ping request->-------|   (command ID: 0x02 - ping request without the APS acknowledgement)   
|-----------------|--<-MAC ACK-------------|  
|-----------------|--<-ping reply----------|   (command ID: 0x01 - ping reply)    
|-----------------|---MAC ACK->------------|   
|--------<-Done---|------------------------|    
```
The ping command measures the time needed for a Zigbee frame to travel between two nodes in the network. The command uses a custom ZCL frame, which is constructed as a ZCL frame of the new custom ping ZCL cluster.  

```bash
> zcl -p 6498 32
I (2847037) : Ping Request frame send successfully
I (2847057) : Ping time: 61 ms
I (2847057) : Done
```

### reset
Perform device reset.  

```bash
> reset
Done
```
