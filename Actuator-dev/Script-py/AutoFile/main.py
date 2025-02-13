# main.py

from RTOS import TaskConfig

tasks = [
    TaskConfig(name="LED_Blink", func_name="led_blink_task", stack_size=128, priority=2, allocation='Dynamic', code_gen_option='default'),
    TaskConfig(name="UART_Send", func_name="uart_send_task", stack_size=256, priority=3, params="NULL", allocation='Dynamic', code_gen_option='external'),
    TaskConfig(name="Sensor_Read", func_name="sensor_read_task", stack_size=128, priority=1, allocation='Static', code_gen_option='weak')
]
# main.py

def generate_task_config_code(tasks):
    code = ""
    for task in tasks:
        code += task.generate_code() + "\n\n"
    return code

# 生成任务配置代码
task_config_code = generate_task_config_code(tasks)
print(task_config_code)
