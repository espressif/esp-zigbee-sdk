# SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0
import os

class ZbCiCons:

    IDF_DOCKER = {
        # IDF version: [build version, test version]
        'v5.1.6': ['v5.1:1', 'v5.1:1'],
        'v5.2.5': ['v5.2:2', 'v5.2:2'],
        'v5.3.4': ['v5.3:1', 'v5.3:1'],
        'v5.4.2': ['v5.4:2', 'v5.4:2'],
        'v5.5.1': ['v5.5:3', 'v5.5:2'],
        'master': ['v6.0:2', 'v6.0:2'],
    }

    PATH_PROJECT = os.environ.get('CI_PROJECT_DIR')
    if not PATH_PROJECT:
        raise Exception('PATH_PROJECT: CI_PROJECT_DIR is required')
    PATH_TEMPLATE = '.gitlab/ci/templates.yml'
    if not os.path.exists(PATH_TEMPLATE):
        raise Exception('FILE: .gitlab/ci/templates.yml is required')
