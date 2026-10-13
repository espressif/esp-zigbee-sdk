# SPDX-FileCopyrightText: 2026 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0
import os

class EzDevCiCons:
    """Constants for ESP-Zigbee-Dev CI configuration"""

    IDF_DOCKER = {
        'v5.2.6': ['v5.2:1', 'v5.2-target-test:1'],
        'v5.3.5': ['v5.3:1', 'v5.3-target-test:1'],
        'v5.4.3': ['v5.4:1', 'v5.4-target-test:1'],
        'v5.5.4': ['v5.5:1', 'v5.5-target-test:1'],
        'master': ['v6.2:2', 'v6.2-target-test:1'],
        'v6.0': ['v6.0:1', 'v6.0-target-test:1'],
        'v6.1': ['v6.1:1', 'v6.1-target-test:1'],

    }

    supported_since = {
        "esp32c5": "v5.5.2",
        # esp32p4 rev>3.0
        "esp32p4": "v5.5.4",
    }

    PATH_PROJECT = os.environ.get('CI_PROJECT_DIR', os.getcwd())

    PATH_TEMPLATE = '.gitlab/ci/templates.yml'

