# SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0
import os

class EzDevCiCons:
    """Constants for ESP-Zigbee-Dev CI configuration"""

    IDF_DOCKER = {
        'v5.1.6': ['v5.1:1', 'v5.1:1'],
        'v5.2.6': ['v5.2:2', 'v5.2:2'],
        'v5.3.5': ['v5.3:1', 'v5.3:1'],
        'v5.4.3': ['v5.4:2', 'v5.4:2'],
        'v5.5.4': ['v5.5:3', 'v5.5:2'],
        'master': ['v6.0:2', 'v6.0:2'],
    }

    PATH_PROJECT = os.environ.get('CI_PROJECT_DIR', os.getcwd())

    PATH_TEMPLATE = '.gitlab/ci/templates.yml'

