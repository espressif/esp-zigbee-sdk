# SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0
import os

class ZbCiCons:

    IDF_DOCKER = {
        'v5.1.4': 'v5.1:1',
        'v5.2.3': 'v5.2:2',
        'v5.3.2': 'v5.3:1',
        'master': 'v6.0:2',
    }

    PATH_PROJECT = os.environ.get('CI_PROJECT_DIR')
    if not PATH_PROJECT:
        raise Exception('PATH_PROJECT: CI_PROJECT_DIR is required')
    PATH_TEMPLATE = '.gitlab/ci/templates.yml'
    if not os.path.exists(PATH_TEMPLATE):
        raise Exception('FILE: .gitlab/ci/templates.yml is required')
