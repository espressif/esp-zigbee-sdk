# SPDX-FileCopyrightText: 2025 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0
"""This file is used for generating the child pipeline for build jobs."""
import argparse
import os
import sys

# 添加当前目录到路径
sys.path.insert(0, os.path.dirname(__file__))

from models import BuildJob
from utils import dump_jobs_to_yaml
from constants import EzDevCiCons


def generate(idf_and_docker, generate_yaml, build_templates, test_job_template, chips, manual_pytest):
    generate_jobs = []
    for idf_version, docker_version in idf_and_docker.items():
        for job_name_fmt, tmpl in build_templates:
            if not tmpl:
                continue
            generate_jobs.append(BuildJob(
                name=job_name_fmt.format(idf_version),
                extends=[f'.{tmpl}'],
                variables={
                    'DOCKER_ENV_VERSION': docker_version[0],
                    'IDF_VERSION': idf_version
                }
            ))
        if test_job_template:
            assert chips, "chips is required when --test_templates is set"
            for chip in chips:
                needs_target = (
                    f'build_pytest_examples_{idf_version}'
                    if chip != 'esp32s3'
                    else f'build_pytest_gateway_{idf_version}'
                )
                generate_jobs.append(BuildJob(
                    name=f'pytest_{chip}_{idf_version}',
                    extends=[f'.{test_job_template}'],
                    variables={
                        'DOCKER_ENV_VERSION': docker_version[1],
                        'CHIP': chip,
                        'IDF_VERSION': idf_version,
                    },
                    needs=[needs_target],
                    when='manual' if manual_pytest else 'always'
                ))
    dump_jobs_to_yaml(generate_jobs, generate_yaml, EzDevCiCons.PATH_TEMPLATE)


def match_idf_docker(idf_version):
    idf_and_docker = {}
    for version in idf_version:
        if version in EzDevCiCons.IDF_DOCKER:
            idf_and_docker[version] = EzDevCiCons.IDF_DOCKER[version]
        else:
            raise ValueError(f'Invalid IDF version: {version}')
    return idf_and_docker


def parse_build_templates(build_template_names):
    result = []
    for name in build_template_names:
        if "gateway" in name:
            result.append(('build_pytest_gateway_{}', name))
            continue
        if "non_pytest" in name:
            result.append(('build_non_pytest_{}', name))
            continue
        if "build_pytest" in name:
            result.append(('build_pytest_examples_{}', name))
            continue
        result.append((name + '_{}', name))
    return result


def main(arg):
    idf_and_docker = match_idf_docker(arg.idf_version)
    yaml_result_path = os.path.join(EzDevCiCons.PATH_PROJECT, arg.result)
    build_templates = parse_build_templates(arg.build_templates)
    test_template = arg.test_templates[0] if arg.test_templates else None
    if test_template and not arg.chips:
        raise ValueError('--chips is required when --test_templates is set')
    generate(
        idf_and_docker,
        yaml_result_path,
        build_templates,
        test_template,
        arg.chips,
        arg.manual_pytest,
    )


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Generate build child pipeline',
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument(
        '--idf_version',
        required=True,
        nargs='+',
        help='List of IDF versions (e.g. v5.5.1 v5.5.2)',
    )
    parser.add_argument(
        '--result',
        required=True,
        help='Output YAML name (e.g. child_pipeline_default.yml)',
    )
    parser.add_argument(
        '--chips',
        default=None,
        nargs='+',
        help='Chip names for pytest jobs (required if --test_templates is set)',
    )
    parser.add_argument(
        '--build_templates',
        required=True,
        nargs='+',
        metavar='TEMPLATE',
        help='One or more build hidden template names (e.g. build_non_pytest_example build_pytest_sdk_example)',
    )
    parser.add_argument(
        '--test_templates',
        default=None,
        nargs=1,
        metavar='TEMPLATE',
        help='Exactly one test (pytest) hidden template; omit if no pytest jobs in this pipeline',
    )
    parser.add_argument(
        '--manual_pytest',
        action='store_true',
        dest='manual_pytest',
        default=False,
        help='Set pytest jobs to manual',
    )

    args = parser.parse_args()
    main(args)

