// RTOS_Template.h

#ifndef RTOS_TEMPLATE_H
#define RTOS_TEMPLATE_H

// 默认模板
#define DEFAULT_TEMPLATE \
    "void {func_name}(void *args) {{\\n" \
    "    // 任务实现代码\\n" \
    "}}\\n" \
    "\\n" \
    "#define {name_upper}_TASK_STACK_DEPTH {stack_size}\\n" \
    "#define {name_upper}_TASK_PRIORITY {priority}\\n" \
    "TaskHandle_t {name_lower}_task_handle;\\n" \
    "\\n" \
    "xTaskCreate(\\n" \
    "    {func_name},\\n" \
    "    \"{name}\",\\n" \
    "    {name_upper}_TASK_STACK_DEPTH,\\n" \
    "    {params},\\n" \
    "    {name_upper}_TASK_PRIORITY,\\n" \
    "    &{name_lower}_task_handle\\n" \
    ");\\n"

// 外部声明模板
#define EXTERNAL_TEMPLATE \
    "extern void {func_name}(void *args);\\n" \
    "\\n" \
    "#define {name_upper}_TASK_STACK_DEPTH {stack_size}\\n" \
    "#define {name_upper}_TASK_PRIORITY {priority}\\n" \
    "TaskHandle_t {name_lower}_task_handle;\\n" \
    "\\n" \
    "xTaskCreate(\\n" \
    "    {func_name},\\n" \
    "    \"{name}\",\\n" \
    "    {name_upper}_TASK_STACK_DEPTH,\\n" \
    "    {params},\\n" \
    "    {name_upper}_TASK_PRIORITY,\\n" \
    "    &{name_lower}_task_handle\\n" \
    ");\\n"

// 弱声明模板
#define WEAK_TEMPLATE \
    "void {func_name}(void *args) __attribute__((weak));\\n" \
    "\\n" \
    "#define {name_upper}_TASK_STACK_DEPTH {stack_size}\\n" \
    "#define {name_upper}_TASK_PRIORITY {priority}\\n" \
    "TaskHandle_t {name_lower}_task_handle;\\n" \
    "\\n" \
    "xTaskCreate(\\n" \
    "    {func_name},\\n" \
    "    \"{name}\",\\n" \
    "    {name_upper}_TASK_STACK_DEPTH,\\n" \
    "    {params},\\n" \
    "    {name_upper}_TASK_PRIORITY,\\n" \
    "    &{name_lower}_task_handle\\n" \
    ");\\n"

#endif // RTOS_TEMPLATE_H