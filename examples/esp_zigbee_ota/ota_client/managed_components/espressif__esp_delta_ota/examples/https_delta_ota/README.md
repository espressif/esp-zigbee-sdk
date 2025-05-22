# HTTPS Delta OTA

Compressed Delta OTA Updates aims at enabling Over-the-Air firmware update with compressed delta binaries. Instead of the original binary to be hosted on the OTA update server, a patch file is hosted which is the difference between the base firmware and the new firmware in compressed form. This reduces the size of the file to be downloaded when performing OTA updates thus reducing the network usage. This also reduces the time taken to complete the OTA process.

This example demonstrates OTA updates with compressed patch binary using `esp_delta_ota` component's APIs and tool.

Compressed patch generated for the new firmware must be hosted on OTA update server. See [How to generate the patch](#creating-patch).

This patch will be downloaded and then applied on the current running firmware on device. The new firmware after applying the patch will be written in a new partition.

## ESP Delta OTA Abstraction Layer

This example uses `esp_delta_ota` component hosted at [idf-extra-components/esp_delta_ota](https://github.com/espressif/idf-extra-components/blob/master/esp_delta_ota) and available though the [IDF component manager](https://components.espressif.com/component/espressif/esp_delta_ota).

Please refer to its documentation [here](https://github.com/espressif/idf-extra-components/blob/master/esp_delta_ota/README.md) for more details.


## How to use the example

### Configure the project
Open the project configuration menu(`idf.py menuconfig`)

In the `Example Connection Configuration` menu:
* Choose the network interface in the `Connect using` option based on your board. Currently both Wi-Fi and Ethernet are supported
* If the Wi-Fi interface is used, provide the Wi-Fi SSID and password of the AP you wish to connect to
* If using the Ethernet interface, set the PHY model under `Ethernet PHY Device` option, e.g. `IP101`

In the `Example Configuration` menu:
* Set the URL of the firmware to download in the `Firmware Upgrade URL` option. The format should be `https://<host-ip-address>:<host-port>/<firmware-image-filename>`, e.g. `https://192.168.2.106:8070/hello_world.bin`

### Build and Flash example

```
idf.py build flash
```

### Creating Patch

Now we will consider this firmware as the base firmware which we will flash into the device. We need a new firmware to which we want to upgrade to. You can try building the `hello_world` example present in ESP-IDF.
We need to create a patch file for this new firmware.

Install required packages:
```
pip install -r tools/requirements.txt
```

To create a patch file, use the [python tool](./tools/esp_delta_ota_patch_gen.py)
```
python esp_delta_ota_patch_gen.py --chip <target> --base_binary <base_binary> --new_binary <new_binary> --patch_file_name <patch_file_name>
```

This will generate the patch file for the new binary which needs to be hosted on the OTA update server.

> **_NOTE:_** Make sure that the firmware present in the device is used as `base_binary` while creating the patch file. For this purpose, user should keep backup of the firmware running in the device as it is required for creating the patch file.
