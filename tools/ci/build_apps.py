# SPDX-FileCopyrightText: 2022-2026 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0.
# This file is used in CI generate binary files for different kinds of apps

import argparse
import sys
import os
from typing import List
from pathlib import Path
from idf_build_apps import App, build_apps, find_apps, setup_logging

APPS_BUILD_PER_JOB = 30
targets_for_gateway = ["esp32c6", "esp32c5"]
targets_for_generic_apps = ["esp32h2", "esp32c6", "esp32c5"]
targets_for_ota = ['esp32h2']
PYTEST_APPS = {
    "all_device_types_app": targets_for_generic_apps,
    "light_sleep_end_device": targets_for_generic_apps,
    "deep_sleep_end_device": targets_for_generic_apps,
    "touchlink_initiator": targets_for_generic_apps,
    "touchlink_target": targets_for_generic_apps,
    "zigbee_gateway": targets_for_gateway,
    "ota_client": targets_for_ota,
    "ota_server": targets_for_ota,
    "color_dimmable_light": targets_for_generic_apps,
    "color_dimmer_switch": targets_for_generic_apps,
    "on_off_light": targets_for_generic_apps,
    "on_off_switch": targets_for_generic_apps,
    "thermostat": targets_for_generic_apps,
    "temperature_sensor": targets_for_generic_apps,
    "data_consumer": targets_for_generic_apps,
    "data_producer": targets_for_generic_apps,
}

DEFAULT_IGNORE_WARNING_FILE = Path(__file__).resolve().parent / 'ignore_build_warnings.txt'

def _load_ignore_warnings_from_file(filepath: Path) -> List[str]:
    """Load ignore warning regex patterns from file (one per line, skip empty and # lines)."""
    if not filepath.exists():
        return []
    patterns = []
    with open(filepath, 'r', encoding='utf-8') as f:
        for line in f:
            line = line.strip()
            if line and not line.startswith('#'):
                patterns.append(line)
    return patterns

def _collect_unignored_log_lines(app: App) -> List[str]:
    """Lines that idf_build_apps treats as error/warning and not covered by ignore_warning_strs."""
    log_path = app.build_log_path
    if not os.path.isfile(log_path):
        return []
    collected: List[str] = []
    seen = set()
    with open(log_path, encoding='utf-8', errors='replace') as fr:
        for raw in fr:
            line = raw.rstrip()
            if not line:
                continue
            is_err_or_warn, ignored = app.is_error_or_warning(line)
            if is_err_or_warn and not ignored and line not in seen:
                seen.add(line)
                collected.append(line)
    return collected

def _print_failed_builds_summary(apps: List[App]) -> None:
    try:
        from idf_build_apps.constants import BuildStatus
    except ImportError:
        return
    failed = [a for a in apps if a.build_status == BuildStatus.FAILED]
    if not failed:
        return
    print('=== CI: failed build(s) summary (exit code will be non-zero) ===')
    for app in failed:
        print('---')
        print('app: {}  target: {}  config: {}'.format(app.name, app.target, app.config_name))
        print('build_path: {}'.format(app.build_path))
        print('build_comment: {}'.format(app.build_comment))
        lines = _collect_unignored_log_lines(app)
        if lines:
            print('unignored error/warning lines from log ({}):'.format(len(lines)))
            for ln in lines:
                print(ln)
        else:
            print('no unignored error/warning lines from log')
    print('=== end of failed build(s) summary ===')

def _is_pytest_app(app: App) -> bool:
    if app.name in PYTEST_APPS and app.target in PYTEST_APPS[app.name]:
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
        apps_for_build = [app for app in apps if not _is_pytest_app(app)]
    elif args.pytest:
        apps_for_build = [app for app in apps if _is_pytest_app(app)]
    elif args.example:
        apps_for_build = [app for app in apps if args.example == app.name]
    else:
        apps_for_build = apps[:]
    assert apps_for_build, 'Found no apps for build'
    print('Found {} apps after filtering'.format(len(apps_for_build)))
    for app in apps_for_build:
        print(app.name, app.target)
    print('Suggest setting the parallel count to {} for this build job'.format(len(apps_for_build) // APPS_BUILD_PER_JOB + 1))

    ignore_warnings = []
    if args.ignore_warning:
        ignore_warnings = _load_ignore_warnings_from_file(DEFAULT_IGNORE_WARNING_FILE)
    ret_code = build_apps(
        apps_for_build,
        parallel_count=args.parallel_count,
        parallel_index=args.parallel_index,
        dry_run=False,
        collect_size_info=args.collect_size_info,
        keep_going=True,
        ignore_warning_strs=ignore_warnings,
        copy_sdkconfig=True,
    )
    if ret_code != 0:
        _print_failed_builds_summary(apps_for_build)
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
        default=['sdkconfig.defaults=default', 'sdkconfig.ci.*=', '=default'],
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
        '--ignore_warning',
        action="store_true",
        help='Ignore all warnings',
    )
    parser.add_argument(
        '--example',
        help='Build specific example',
    )
    arguments = parser.parse_args()
    setup_logging(verbose=1)
    main(arguments)
