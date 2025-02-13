# task_config.py

import re

class TaskConfig:
    def __init__(self, name, func_name, stack_size, priority, params=None, allocation='Dynamic', code_gen_option='default'):
        self.name = name
        self.func_name = func_name
        self.stack_size = stack_size
        self.priority = priority
        self.params = params if params else 'NULL'
        self.allocation = allocation
        self.code_gen_option = code_gen_option

    def generate_code(self):
        with open('../Template/RTOS_Template.h', 'r') as header_file:
            header_content = header_file.read()

        template_name = f"{self.code_gen_option.upper()}_TEMPLATE"
        template = re.search(f"\\n#define {template_name} (.*)", header_content).group(1)

        return template.format(
            name=self.name,
            name_upper=self.name.upper(),
            name_lower=self.name.lower(),
            func_name=self.func_name,
            stack_size=self.stack_size,
            priority=self.priority,
            params=self.params
        )