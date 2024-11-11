# SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0
import yaml


def dump_jobs_to_yaml(
    jobs, output_filepath, template_yaml
):
    yaml_dict = {}
    for job in jobs:
        yaml_dict.update(job.to_dict())
    # global stuffs
    yaml_dict.update(
        {
            'include':[{'local':template_yaml}],
        }
    )

    with open(output_filepath, 'w') as fw:
        yaml.dump(yaml_dict, fw, default_flow_style=False, indent=2)
