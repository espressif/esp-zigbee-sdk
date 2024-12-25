# SPDX-FileCopyrightText: 2022 Espressif Systems (Shanghai) CO LTD

# SPDX-License-Identifier: CC0-1.0

# This file is used in CI generate binary files for different kinds of apps

import argparse
import sys
import os
from typing import List
from pathlib import Path
from idf_build_apps import App, build_apps, find_apps, setup_logging

# from idf_ci_utils import IDF_PATH, get_pytest_app_paths, get_pytest_cases, get_ttfw_app_paths
APPS_BUILD_PER_JOB = 30
PYTEST_APPS = [
    {"target": "esp32h2", "name": "esp_zigbee_all_device_types_app"},
    {"target": "esp32h2", "name": "HA_color_dimmable_light"},
    {"target": "esp32h2", "name": "customized_client"},
    {"target": "esp32h2", "name": "customized_server"},
    {"target": "esp32h2", "name": "ota_client"},
    {"target": "esp32h2", "name": "ota_server"},
    {"target": "esp32h2", "name": "light_sleep"},
    {"target": "esp32h2", "name": "deep_sleep"},
    {"target": "esp32h2", "name": "touchlink_switch"},
    {"target": "esp32h2", "name": "touchlink_light"},
    {"target": "esp32h2", "name": "HA_on_off_light"},
    {"target": "esp32c6", "name": "esp_zigbee_all_device_types_app"},
    {"target": "esp32c6", "name": "HA_color_dimmable_light"},
    {"target": "esp32c6", "name": "customized_client"},
    {"target": "esp32c6", "name": "customized_server"},
    {"target": "esp32c6", "name": "light_sleep"},
    {"target": "esp32c6", "name": "deep_sleep"},
    {"target": "esp32c6", "name": "touchlink_switch"},
    {"target": "esp32c6", "name": "touchlink_light"},
]

GATEWAY_APPS = [{"target": "esp32h2", "name": "esp_zigbee_all_device_types_app"}, ]

IGNORE_WARNINGS = [
    r"warning: 'init_spiffs' defined but not used",
    r"warning: 'esp_zb_gateway_board_try_update' defined but not used",
    r"DeprecationWarning: pkg_resources is deprecated as an API",
]

def _is_pytest_app(app: App, app_list) -> bool:
    for pytest_app in app_list:
        if app.name == pytest_app["name"] and app.target == pytest_app["target"]:
            return True
    return False


def get_cmake_apps(
        path: str,
        target: str,
        config_rules_str: List[str],
) -> List[App]:
    current_working_dir = Path.cwd()
    manifest_files = str(current_working_dir / path / '.build-test-rules.yml')
    print('manifest path:{}'.format(manifest_files))
    if not os.path.exists(manifest_files):
        raise FileNotFoundError(f"The file '{manifest_files}' does not exist.")
    apps = find_apps(
        path,
        recursive=True,
        target=target,
        build_dir='build_@t_@w',
        config_rules_str=config_rules_str,
        check_warnings=True,
        manifest_files=manifest_files,
    )
    return apps

def main(args: argparse.Namespace) -> None:
    apps = get_cmake_apps(args.path, args.target, args.config)
    # no_pytest and only_pytest can not be both True
    assert not (args.no_pytest and args.pytest)
    if args.no_pytest:
        apps_for_build = [app for app in apps if not (_is_pytest_app(app, PYTEST_APPS)
                                                      or _is_pytest_app(app, GATEWAY_APPS))]
    elif args.pytest:
        apps_for_build = [app for app in apps if _is_pytest_app(app, PYTEST_APPS)]
    elif args.rcp_gateway:
        apps_for_build = [app for app in apps if _is_pytest_app(app, GATEWAY_APPS)]
    else:
        apps_for_build = apps[:]
    assert apps_for_build, 'Found no apps for build'
    print('Found %d apps after filtering', len(apps_for_build))
    print('Suggest setting the parallel count to %d for this build job', len(apps_for_build) // APPS_BUILD_PER_JOB + 1)

    ignore_warnings = IGNORE_WARNINGS
    if args.ignore_warning:
        ignore_warnings = [r"warning: .*"]
    ret_code = build_apps(
        apps_for_build,
        parallel_count=args.parallel_count,
        parallel_index=args.parallel_index,
        dry_run=False,
        collect_size_info=args.collect_size_info,
        # build_verbose=0,
        keep_going=True,
        ignore_warning_strs=ignore_warnings,
        copy_sdkconfig=True,
    )

    # revert_sdkconfig_files()
    sys.exit(ret_code)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Build all the apps for different test types. Will auto remove those non-test apps binaries',
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument('path', help='Path to the file .build-test-rules.yml, it must be a relative path')
    parser.add_argument(
        '-t',
        '--target',
        default='all',
        help='Build apps for given target. could pass "all" to get apps for all targets',
    )
    parser.add_argument(
        '--config',
        default=['sdkconfig.ci=default', 'sdkconfig.ci.*=', '=default'],
        action='append',
        help='Adds configurations (sdkconfig file names) to build. This can either be '
             'FILENAME[=NAME] or FILEPATTERN. FILENAME is the name of the sdkconfig file, '
             'relative to the project directory, to be used. Optional NAME can be specified, '
             'which can be used as a name of this configuration. FILEPATTERN is the name of '
             'the sdkconfig file, relative to the project directory, with at most one wildcard. '
             'The part captured by the wildcard is used as the name of the configuration.',
    )
    parser.add_argument(
        '--parallel-count', default=1, type=int, help='Number of parallel build jobs.'
    )
    parser.add_argument(
        '--parallel-index',
        default=1,
        type=int,
        help='Index (1-based) of the job, out of the number specified by --parallel-count.',
    )
    parser.add_argument(
        '--no_pytest',
        action="store_true",
        help='Exclude pytest apps, defined in PYTEST_APPS',
    )
    parser.add_argument(
        '--pytest',
        action="store_true",
        help='Only build pytest apps, defined in PYTEST_APPS',
    )
    parser.add_argument(
        '--collect-size-info',
        type=argparse.FileType('w'),
        help='If specified, the test case name and size info json will be written to this file',
    )
    parser.add_argument(
        '--rcp_gateway',
        action="store_true",
        help='Only build rcp_gateway pytest apps, defined in GATEWAY_APPS',
    )
    parser.add_argument(
        '--ignore_warning',
        action="store_true",
        help='Ignore all warnings',
    )
    arguments = parser.parse_args()
    setup_logging(verbose=1)  # Info
    main(arguments)
