# SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0
"""This file is used for generating the child pipeline for build jobs."""
import argparse
import os
from models import BuildJob
from utils import dump_jobs_to_yaml
from constants import ZbCiCons

def generate(idf_and_docker, generate_yaml, template_yaml):
    generate_jobs = []
    for idf_version, docker_version in idf_and_docker.items():
        # generate build jobs
        build_non_pytest_examples_job = BuildJob(
            name='build_non_pytest_examples_{}'.format(idf_version),
            extends=['.build_non_pytest_example_template'],
            variables={'DOCKER_ENV_VERSION': docker_version,
                       'IDF_VERSION': idf_version},
        )
        build_pytest_examples_job = BuildJob(
            name='build_pytest_examples_{}'.format(idf_version),
            extends=['.build_pytest_example_template'],
            variables={'DOCKER_ENV_VERSION': docker_version,
                       'IDF_VERSION': idf_version},
        )
        build_pytest_gateway_job = BuildJob(
            name='build_pytest_gateway_{}'.format(idf_version),
            extends=['.build_pytest_gateway_template'],
            variables={'DOCKER_ENV_VERSION': docker_version,
                       'IDF_VERSION': idf_version},
        )
        # generate test jobs
        for chip in ZbCiCons.CHIPS:
            pytest_job = BuildJob(
                name='pytest_{}_{}'.format(chip, idf_version),
                extends=['.pytest_template'],
                variables={'DOCKER_ENV_VERSION': docker_version,
                           'CHIP': chip},
                needs=['build_pytest_examples_{}'.format(
                    idf_version) if chip != 'esp32s3' else 'build_pytest_gateway_{}'.format(idf_version)]
            )
            generate_jobs.append(pytest_job)

        generate_jobs.append(build_pytest_examples_job)
        generate_jobs.append(build_pytest_gateway_job)
        generate_jobs.append(build_non_pytest_examples_job)

        # generate docs jobs
    dump_jobs_to_yaml(generate_jobs, generate_yaml, template_yaml)

def main(arg):
    project_path = arg.project_path
    assert project_path
    template_yaml = arg.template_path
    if not os.path.exists(template_yaml):
        raise FileNotFoundError('The file {} does not exist.'.format(template_yaml))
    default_idf = arg.default_idf_version
    default_docker_version = arg.default_docker_version
    lts_idf_docker = ZbCiCons.LTS_IDF_DOCKER
    default_yaml_path = os.path.join(project_path, ZbCiCons.PIPELINE_YAML_DEFAULT)
    lts_yaml_path = os.path.join(project_path, ZbCiCons.PIPELINE_YAML_LTS)
    default_idf_docker = {default_idf: default_docker_version}
    generate(default_idf_docker, default_yaml_path, template_yaml)
    generate(lts_idf_docker, lts_yaml_path, template_yaml)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Generate build child pipeline',
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument(
        '-p',
        '--project_path',
        required=True,
        help='Paths to project',
    )
    parser.add_argument(
        '-t',
        '--template_path',
        required=True,
        help='Paths to template.yml',
    )
    parser.add_argument(
        '-i',
        '--default_idf_version',
        required=True,
        help='default_idf_version',
    )
    parser.add_argument(
        '-d',
        '--default_docker_version',
        required=True,
        help='default_docker_version',
    )
    args = parser.parse_args()
    main(args)
