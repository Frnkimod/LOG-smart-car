// RTOS_Template.c

#include "RTOS_Template.h"

// 任务配置结构体
typedef struct {
    const char *name;
    const char *func_name;
    int stack_size;
    int priority;
    const char *params;
    const char *template;
} TaskConfig_t;

// 任务配置数组
TaskConfig_t task_configs[] = {
        {
                .name = "LED_Blink",
                .func_name = "led_blink_task",
                .stack_size = 128,
                .priority = 2,
                .params = "NULL",
                .template = DEFAULT_TEMPLATE
        },
        {
                .name = "UART_Send",
                .func_name = "uart_send_task",
                .stack_size = 256,
                .priority = 3,
                .params = "NULL",
                .template = EXTERNAL_TEMPLATE
        },
        {
                .name = "Sensor_Read",
                .func_name = "sensor_read_task",
                .stack_size = 128,
                .priority = 1,
                .params = "NULL",
                .template = WEAK_TEMPLATE
        }
};

// 生成任务配置代码
void generate_task_config_code() {
    for (int i = 0; i < sizeof(task_configs) / sizeof(task_configs[0]); i++) {
        const TaskConfig_t *config = &task_configs[i];
        printf(config->template,
                .name = config->name,
        .func_name = config->func_name,
        .name_upper = config->name,
        .stack_size = config->stack_size,
        .priority = config->priority,
        .params = config->params,
        .name_lower = config->name
        );
    }
}