# ESP Delta OTA

## Getting Started
Compressed Delta OTA Updates aims at enabling Over-the-Air firmware update with compressed delta binaries. 

### Compressed Delta Image for OTA
![Image Format](https://raw.githubusercontent.com/espressif/idf-extra-components/master/esp_delta_ota/image_format.png)

### Advantages of using this design for OTA update:
* Patch file have smaller size than the original firmware file. This reduces the time and network usage to download the file from server.
* No additional storage partition is required for the "patch".
* Only firmware level changes are required for integrating this component. No bootloader related changes required.
* This scheme can be implemented for the existing devices in the field.

## Workflow Block diagram
![ESP Delta OTA Block Diagram](https://raw.githubusercontent.com/espressif/idf-extra-components/master/esp_delta_ota/esp_delta_ota_block_diagram.png)

## Prerequisites

* **ESP-IDF v4.3 and above**

  You can visit the [ESP-IDF Programmming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html#installation-step-by-step) for the installation steps.

* **detools v0.49.0 and above**

  Binary delta encoding in Python 3.6+. You can install detools using the following command: 
  ```
  pip install -r examples/https_delta_ota/tools/requirements.txt
  ```
  More information about the package [here](https://pypi.org/project/detools/).

## Usage

Refer to the [https_delta_ota](https://github.com/espressif/idf-extra-components/blob/master/esp_delta_ota/examples/https_delta_ota/) example to see the use of `esp_delta_ota` component for OTA updates.

## API Reference
To learn more about how to use this component, please check API Documentation from header file [esp_delta_ota.h](https://github.com/espressif/idf-extra-components/blob/master/esp_delta_ota/include/esp_delta_ota.h)

## License

* Distributed under the Apache-2.0 License. Refer [esp_delta_ota LICENSE](https://github.com/espressif/idf-extra-components/blob/master/esp_delta_ota/LICENSE) for more information.
* `detools` : Distributed under the BSD 2-Clause License. Refer [detools LICENSE](https://github.com/eerimoq/detools/blob/master/LICENSE) for more information.
* `heatshrink` : Distributed under the ISC License. Refer [heatshrink LICENSE](https://github.com/eerimoq/detools/blob/master/c/heatshrink/README.rst) for more information.
