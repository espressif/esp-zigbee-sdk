# Zigbee Manufacturing Partition Generator Utility  

This tool generates the Zigbee manufacturing binary, the device specific configuration includes:

* Install Code (encoding: string, 16/20/28/36 characters)  
* MAC Address  (encoding: string, 16 characters)  
* Channel Mask (encoding: uint32, 4 bytes)  
* Manufacturer Name (encoding: string, max length: 15 characters)  
* Manufacturer Code (encoding: uint16, 2 bytes)  

## Dependencies

* [Mass Manufacturing Utility](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/storage/mass_mfg.html#manufacturing-utility), mfg_gen.py to create factory NVS partition images.  
* [NVS Partition Generator Utility](https://github.com/espressif/esp-idf/tree/master/components/nvs_flash/nvs_partition_generator), nvs_partition_gen.py to creates a binary file based on key-value pairs provided in a CSV file.  
  
## Pre-requisites

* Install python dependencies  
```
cd path/tools/mfg_tool
python3 -m pip install -r requirements.txt
```

* Export IDF_PATH  
[IDF Get Started](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html)  

## Input/Output files and directory structure
```
in
├── multi_devices_config.csv

out
├── bin/CAFEBEEF50C0FFEC.bin
├── ...
```

`multi_devices_config.csv` : The file contains key-value of Zigbee product config parameters. The first line is the parameter key which do not need to be modified, and the next each line in `multi_devices_config.csv` corresponds to a device instance which User shall config.   
`bin/` : Zigbee product config binary file for each device.     

## Usage examples

`esp_zb_mfg_tool.py -h` lists the mandatory as well as optional arguments.  
### Generate a factory partition   
```
python esp_zb_mfg_tool.py -i 966b9f3ef98ae6059708 -m CAFEBEEF50C0FFED -c 0x8000 -mn Espressif -mc 0x131B 
```
### Generate factory partitions with extra key-values specified using csv file  

* Config parameters for each Zigbee device  
User shall config parameters by reference to `multi_devices_config.csv` formate. If key `installcode` and `mac_address` is none, please set `NULL`.  

* Generate factory partitions for each Zigbee device  
```
python esp_zb_mfg_tool.py --csv ./multi_devices_config.csv
```

## Flashing the manufacturing binary
Please note that `esp_zb_mfg_tool.py` only generates manufacturing binary images which need to be flashed onto device. Using `esptool.py` please refer [esptool usage](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html#flash-onto-the-device).  

`esptool.py` is present at path `$IDF_PATH/components/esptool_py/esptool/esptool.py`

* Flashing a binary image to the device
```
esptool.py -p <serial_port> write_flash <address> path/tool/mfg_tool/bin/xxx.bin
```
`<address>` : User can find section `zb_fct` in each project `partitions.csv`, which shows the address. For example [partition_table](../../examples/esp_zigbee_HA_sample/HA_color_dimmable_light/partitions.csv).
