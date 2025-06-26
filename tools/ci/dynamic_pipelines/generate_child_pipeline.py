# SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0
"""This file is used for generating the child pipeline for build jobs."""
import argparse
from models import BuildJob
from utils import dump_jobs_to_yaml
from constants import ZbCiCons
import os

def generate(idf_and_docker, generate_yaml, build_templates, pytest_job_template, chips):
    generate_jobs = []
    for idf_version, docker_version in idf_and_docker.items():
        for job_name_fmt, tmpl in build_templates:
            if not tmpl:
                continue
            generate_jobs.append(BuildJob(
                name=job_name_fmt.format(idf_version),
                extends=[f'.{tmpl}'],
                variables={
                    'DOCKER_ENV_VERSION': docker_version,
                    'IDF_VERSION': idf_version
                }
            ))
        if pytest_job_template:
            for chip in chips:
                needs_target = (
                    f'build_pytest_examples_{idf_version}'
                    if chip != 'esp32s3'
                    else f'build_pytest_gateway_{idf_version}'
                )
                generate_jobs.append(BuildJob(
                    name=f'pytest_{chip}_{idf_version}',
                    extends=[f'.{pytest_job_template}'],
                    variables={
                        'DOCKER_ENV_VERSION': docker_version,
                        'CHIP': chip,
                        'IDF_VERSION': idf_version,
                    },
                    needs=[needs_target]
                ))
    dump_jobs_to_yaml(generate_jobs, generate_yaml, ZbCiCons.PATH_TEMPLATE)

def match_idf_docker(idf_version):
    idf_and_docker = {}
    for idf_version in idf_version:
        if idf_version in ZbCiCons.IDF_DOCKER:
            idf_and_docker[idf_version] = ZbCiCons.IDF_DOCKER[idf_version]
        else:
            raise ValueError(f'Invalid IDF version: {idf_version}')
    return idf_and_docker

def parse_job_templates(job_templates):
    build_templates = []
    pytest_template = None
    for job in job_templates:
        if "build_pytest_template" in job:
            build_templates.append(('build_pytest_examples_{}', job))
        elif "build_non_pytest_template" in job:
            build_templates.append(('build_non_pytest_examples_{}', job))
        elif "build_pytest_gateway_template" in job:
            build_templates.append(('build_pytest_gateway_{}', job))
        else:
            pytest_template = job
    return build_templates, pytest_template

def main(arg):
    idf_and_docker = match_idf_docker(arg.idf_version)
    yaml_result_path = os.path.join(ZbCiCons.PATH_PROJECT, arg.result)
    build_templates, pytest_template = parse_job_templates(arg.job_templates)
    generate(idf_and_docker, yaml_result_path, build_templates, pytest_template, arg.chips)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Generate build child pipeline',
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument(
        '--idf_version',
        required=True,
        nargs='+',
        help='List of IDF versions (e.g. v5.2.3 v5.1.4)',
    )
    parser.add_argument(
        '--result',
        required=True,
        help='Output YAML name (e.g. idf.yml)',
    )
    parser.add_argument(
        '--chips',
        default=None,
        nargs='+',
        help='List of chip names (e.g. esp32c6 esp32h2 esp32s3)'
    )
    parser.add_argument(
        '--job_templates',
        required=True,
        help='job template names (e.g. build_pytest_template build_non_pytest_template build_pytest_gateway_template)',
        nargs='+',
    )
    args = parser.parse_args()
    main(args)
