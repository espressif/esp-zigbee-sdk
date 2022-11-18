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
- [role](#role)
- [extpanid](#extpanid)
- [panid](#panid)
- [channel](#channel)
- [start](#start)
- [ic](#ic)
- [legacy](#legacy)
- [nwkkey](#nwkkey)
- [factory](#factory)
- [child](#child)
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
- [zcl_command](#zcl_command)
- [attr_read](#attr_read)
- [attr_write](#attr_write)
- [subscribe_on](#subscribe_on)
- [subscribe_off](#subscribe_off)
- [ping](#ping)
- [reset](#reset)


## Zigbee CLI Command Details

### role
Set a Zigbee role to the device.  
*bdb -r <zc/zr>*   

Note:  
Set action only before bdb start. Read action only after bdb start.  

```bash
> bdb -r zc
Coordinator role set. 
```
```bash
> bdb -r zr
Router role set.
```
Get Zigbee role of a device.
```bash
> bdb -r get
zr
```

### extpanid
Set Zigbee extpanid value.  
*bdb -e <h:extpanid>*   

Note:  
Set action only before bdb start. Read action only after bdb start.  

```bash
> bdb -e 1122334455667788
I (605714) : set extpanid: 0x1122334455667788
```
Get Zigbee extpanid value.  
*bdb -e get*  
```bash
> bdb -e get
I (611644) : get extpanid: 0x1122334455667788
```

### panid
Set Zigbee panid value.  
*bdb -p <h:panid>*  

Note:  
Set action only before bdb start. Read action only after bdb start.  

```bash
> bdb -p 1122
I (977414) : set panid: 0x1122
```
Get Zigbee panid value:  
*bdb -p get*  
```bash
> bdb -p get
I (983554) : get panid: 0x1122
```

### channel
Set Zigbee 2.4GHz channel.  
Channel parameter:    
If n is in[11:26] range, set to that channel; Oherwise, treat n as bitmask.  
*bdb -c <d:n>*  

Note:  
Set action only before bdb start.   

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

### start
Start the commissionings proces.

```bash
> bdb -s
I (1748414) : Started coordinator
I (1748494) : Done
```

### ic
Set install code on the device; add information abort the install code on trust center; set the trust center install code policy.  
*bdb -i set <h:install code>  
bdb -i add <h:install code> <h:eui64>  
bdb -i policy <enable|disable>*  

Note: 
Set and define policy only before bdb start. Add action only after bdb start.  
bdb ic set must only be used on a joining device(ZR/ZED).  
bdb ic add must only be used on a coordinator. For <h:eui64>, use the address of the joining device.  
bdb ic policy must only be used on a coordinator.  
Provide the install code as an ASCII-encoded hex that includes CRC-16/X-25.  
For production devices, an install code must be installed by the production configuration present in flash.  

Zigbee Router and Zigbee End Device  
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

Zigbee Coordinator  
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
Enable or disable the legacy device support.  
*bdb -l <enable/disable>*

```bash
> bdb -l enable
I (54039534) : Done
> bdb -l disable
I (54046354) : Done
```

### nwkkey
Start the commissionings process.  
*bdb -n <h:key>*

Note:  
Set action only before bdb start.  

```bash
> bdb -n 00112233445566778899aabbccddeeff
Set key:00112233445566778899aabbccddeeff
I (14364) : Done
```

### factory
Perform a factory reset via local action.  
*bdb -f*  
```bash
> bdb -f 
I (95824) : Done
```

### child
Set the amount of child devices.  

*bdb -m <d:number>*  
```bash
> bdb -m 1
I (226424) : Setting max children to: 1
```

### active_ep
Send Active Endpoint Request to the node addressed by the short address.  
*zdo -a <h:16-bit destination address>*  

```bash
>  zdo -a 0x78D9
I (749364) : src_addr=78D9
I (749364) : ep=10,242
Done
```

### simple
Send Simple Descriptor Request.  
*zdo -c <h:16-bit destination address> <d:endpoint>*  

```bash
> zdo -c 0xefba 10
> src_addr=0xEFBA ep=10 profile_id=0x0102 app_dev_id=0x0 app_dev_ver=0x5
  in_clusters=0x0000,0x0003,0x0004,0x0005,0x0006,0x0008,0x0300 out_clusters=0x0300
I (1180874) : Done
> 
```

### match
Send match descriptor request.  
*zdo -m <h:16-bit destination address>  
&emsp;&emsp;&emsp;&nbsp;<h:requested address/type>  
&emsp;&emsp;&emsp;&nbsp;<h:profile ID>  
&emsp;&emsp;&emsp;&nbsp;<d:number of input clusters> [<h:input cluster IDs> ...]  
&emsp;&emsp;&emsp;&nbsp;<d:number of output clusters> [<h:output cluster IDs> …] [timeout]*  
	
Note:  
Send Match Descriptor Request to the dst_addr node that is a query about the req_addr node of the prof_id profile ID, which must have at least one of n_input_clusters or n_output_clusters.    
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
Note:  
Create bound connection between a device identified by source eui64 and endpoint source ep, and a device identified by destination addr and endpoint destination ep. The connection is created for ZCL commands and attributes assigned to the ZCL cluster source cluster id on the request dst addr node.  
```bash
> zdo -b on f4ce36840d75b6dc 64 f4ce36b6ba35bed1 64 3 C698
Done
```

### bind_off
*zdo -b off <h:source eui64> <d:source ep> <h:destination eui64>  
&emsp;&emsp;&emsp;&emsp;&nbsp;<d:destination ep> <h:source cluster id> <h:request dst addr>*  
Remove a binding between two endpoints on two nodes.  

```bash
> zdo -b off f4ce36840d75b6dc 64 f4ce36b6ba35bed1 64 3 C698
Done
```

### mgmt_bind
Read the binding table from a node.  
*zdo -d <h:16-bit dst_addr> [d:start_index]*   

Note:  
Send a request to the remote device identified by dst_addr to read the binding table through zdo mgmt_bind_req, start_index is the index of the first entry in the binding table where the reading starts. It is zero by default.   

```bash
> zdo -d C698
[idx] src_address       src_endp cluster_id  dst_addr_mode  dst_addr          dst_endp
[  0] f4ce36840d75b6dc     64      0x003           3        f4ce36b6ba35bed1     64
Total entries for the binding table: 1
Done
```

### mgmt_lqi
Send a ZDO Mgmt_Lqi_Req command to a remote device and ask it to return its neighbor table.  
*zdo -l <h:short_addr> [d:start index]*  

```bash
> zdo -q 0xC698
I (28711) : [idx] ext_pan_id            ext_addr     short_addr flags permit_join depth     lqi
I (28711) : [   0] 74fa0801a003f784 74fa0801a003f784 0x0000      0x84     1       0         255
I (28711) : [   1] 74fa0801a003f784 f4ce36b6ba35bed1 0x4eaa      0x25     0       2         255
I (28731) : ZDO request 161480 complete
> Done
```

### nwk_addr
Resolve the EUI64 address by a short network address.  
*zdo -n <h:eui64>*  

```bash
> zdo -n f4ce36840d75b6dc 
I (122147) : nwk_addr:7655
Done
```

### ieee_addr
Resolve the EUI64 address by sending the IEEE address request.  
*zdo -i <h:short_addr>*  

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
Send a request to a remote device to leave the network through zdo mgmt_leave_req.  
*zdo -l <h:16-bit dst_addr> [h:device_address eui64] [children] [rejoin]*  

Note:  
Send mgmt_leave_req to a remote node specified by dst_addr.  
If device_address is omitted or it has value 0000000000000000, the remote device at address dst_addr will remove itself from the network;  
If device_address has other value, it must be a long address corresponding to dst_addr or a long address of child node of dst_addr;  
The request is sent with Remove Children and Rejoin flags set to 0 by default.  
Use options children or rejoin do change the respective flags to 1.  

Send mgmt_leave_req to the device with the short address 0x4eaa, and ask it to remove itself from the network.  
```bash
> zdo -l 0x4eaa
Done
```

Send mgmt_leave_req to the device with the short address 0x4eaa, and ask it to remove itself from the network and perform rejoin.  
```bash
> zdo -l 0x4eaa rejoin
Done
```

Send mgmt_leave_req to the device with the short address 0x4eaa, and ask it to remove device 74fa0801a003f784 from the network. If the target device with the short address 0x4eaa has also a long address 74fa0801a003f784, it will remove itself from the network, If the target device with the short address 0x4eaa has a child with long address 74fa0801a003f784, it will remove the child from the network.  
```bash
> zdo -l 0x4eaa 74fa0801a003f784
Done
```

Send mgmt_leave_req to the device with the short address 0x4eaa, and ask it to remove itself and all its children from the network.  
```bash
> zdo -l 0x4eaa children
Done
```

### zcl_command
Send a general command to the remote node.  
*zcl -c <h:dst_addr> <d:ep> <h:cluster>  
&emsp;&emsp;&ensp;<h:cmd_ID> [profile h:profile] [payload h:payload]  [default]*  

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
Retrieve the attribute value of the remote node.  
*zcl -a read <h:dst_addr> <d:ep> <h:cluster> <h:profile> <h:attr_id> [switch]*  

Note:  
read the value of the attribute attr_id in the cluster cluster. The cluster belongs to the profile profile, which resides on the endpoint ep of the remote node dst_addr. If the attribute is on the client role side of the cluster, use the "switch" change.  

```bash
> zcl -a read 6498 64 0x0000 0x0104 0 
I (688567) : ID: 0 Type: 0x20 Value: 2
I (688577) : Done 
```

### attr_write
Write the attribute value to the remote node.  
*zcl -a write <h:dst_addr> <d:ep> <h:cluster> <h:profile> <h:attr_id>   
&emsp;&emsp;&emsp;&emsp;&emsp;<h:attr_type> <h:attr_value> [switch]*  

```bash
> zcl -a write 6498 64 0x0003 0x0104 0 0x21 0
I (961517) : Done
```

### subscribe_on
Subscribe to the attribute changes on the remote node.   
*zcl -s on <h:addr> <d:ep> <h:cluster> <h:profile>  
&emsp;&emsp;&emsp;&emsp;<h:attr ID> <d:attr type>  
&emsp;&emsp;&emsp;&emsp;[<d:min interval (s)>] [<d:max interval (s)>]*  

Note:  
Enable reporting on the node identified by the address addr, with the endpoint ep that uses the profile profile of the attribute attr ID with the type attr type in the cluster.  
The reports must be generated in intervals not shorter than min interval (1 second by default) and not longer than max interval (60 seconds by default).  

```bash
> zcl -s on 6498 64 0x0006 0x0104 0 0x10
I (961517) : Done
```

### subscribe_off
Unsubscribe from the attribute reports.  
*zcl -s off <h:addr> <d:ep> <h:cluster> <h:profile> <h:attr ID> <d:attr type>*    

Note:  
Disable reporting on the node identified by the address addr, with the endpoint ep that uses the profile profile of the attribute attr ID with the type attr type in the cluster cluster.  

```bash
> zcl -s off 6498 64 0x0006 0x0104 0 0x10
I (961517) : Done
```
### ping
Issue a ping over ZCL.  
*zcl -p <h:dst_addr> <d:payload size>*

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
