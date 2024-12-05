# SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0


class ZbCiCons:
    IDF_DOCKER_ENV = {
        'v5.1.4':'v5.1:1',
        'v5.2.3':'v5.2:2',
        'v5.3.2':'v5.3:1',
    }
    CHIPS = ['esp32c6', 'esp32h2', 'esp32s3']
    PIPELINE_YAML_DEFAULT = 'child_pipeline_default.yml'
    PIPELINE_YAML_FULL = 'child_pipeline_lts.yml'
