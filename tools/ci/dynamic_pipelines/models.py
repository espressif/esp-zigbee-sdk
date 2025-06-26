# SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
# SPDX-License-Identifier: Apache-2.0
import inspect
import yaml

class Job:
    def __init__(
            self,
            name,
            extends=None,
            tags=None,
            stage=None,
            parallel=1,
            variables=None,
            script=None,
            before_script=None,
            after_script=None,
            needs=None,
            artifacts=None,
            **kwargs
    ):
        self.name = name
        self.extends = extends
        self.tags = tags
        self.stage = stage
        self.parallel = parallel
        self.variables = variables or None
        self.script = script
        self.before_script = before_script
        self.after_script = after_script
        self.needs = needs
        self.artifacts = artifacts

        for k, v in kwargs.items():
            setattr(self, k, v)

    def __str__(self):
        return yaml.dump(self.to_dict())  # type: ignore

    def set_variable(self, key, value):
        self.variables[key] = value

    def to_dict(self):
        res = {}
        for k, v in inspect.getmembers(self):
            if k.startswith('_'):
                continue

            # name is the dict key
            if k == 'name':
                continue

            # parallel 1 is not allowed
            if k == 'parallel' and v == 1:
                continue

            if v is None:
                continue

            if inspect.ismethod(v) or inspect.isfunction(v):
                continue

            res[k] = v

        if self.artifacts is not None:
            res['artifacts'] = self.artifacts

        return {self.name: res}


class BuildJob(Job):
    def __init__(
            self,
            name,
            extends= None,
            tags=None,
            stage= None,
            **kwargs
    ):
        super().__init__(
            name=name,
            extends=extends,
            tags=tags,
            stage=stage,
            **kwargs
        )
