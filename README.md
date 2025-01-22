# 项目介绍
- 工创赛智能物流小车程序文件
    - Actuator-dev:机构控制模块
    - Move-dev:移动控制模块
    - Scipt-py:自动化模块生成脚本
- Actuator-dev
    - Core\BSP


- Move-dev
    - Core\BSP
        - 42-dev:步进电机驱动
        - Control:移动控制算法
        - DWT:定时器驱动
        - `BSP_conf.h`GPIO与常量信息配置
    - Core\Src
        - `freertos.c`任务实现
        - `main.c`功能模块初始化程序入口
- Scipt-py
    - AutoFile:自动化C模块生成
    - Template:储存模板文件
----------------------
# 开发环境

- 译构建软件:__STM32CubuMX__,__Clion__
- 编译链工具:__CMake__,__gcc-arm-none-eabi__,__`Pyhon3.12`__
- 主控芯片:__STM32F103C8T6__,__`RK3866`__
- 框架:__HAL__,__RTOS__,__`Open-cv`__
----------------------
# 基本框架

### `控制逻辑`
```mermaid
classDiagram
 
 树莓派 <|--|>底层STM32:UART通讯
 树莓派 <|--|>上层STM32:UART通讯
 class 上层STM32{
  升降臂机构28步进电机*1
  伸缩机构42步进电机*1
  物料转盘舵机*1
  夹取舵机*2
  升降机构执行()
  伸缩机构执行()
  物料转盘执行()
  夹取执行()
 }
 class 树莓派{
  摄像头*2
  显示屏*1
  二维码任务识别并显示()
  路线识别并规划()
  物料颜色识别()
  物料放置中心点识别()
 }
 class 底层STM32{
  移动装置42步进电机*4
  上层转盘42步进电机*1
  运动执行()
  转盘转动执行()
 }
 
```
----------------------
### `底部STM32架构框架`
```mermaid
%%{
  init: {
    'theme': 'base',
    'themeVariables': {
      'fontSize':'16px',
      'primaryColor': 'rgb(174, 5, 246)',
      'primaryTextColor': 'rgb(255, 255, 255)',
      'secondaryColor': 'rgba(0, 219, 243,  0.80)',
      'tertiaryColor': 'rgba(251, 255, 3, 0.8)',
      'tertiaryBorderColor':'rgb(142, 40, 40)'
    }
  }
}%%
mindmap
  root((F103c8t6))
    (HAL抽象层)   
        TIM
        UART
        DWM
        GPIO
    (RTOS任务处理)
        数据处理任务
        UART数据通讯任务
        移动电机脉冲发送任务
        上层转盘电机脉冲发送任务  
     
```
----------------------

### `上层STM32架构框架` 
```mermaid
%%{
  init: {
    'theme': 'base',
    'themeVariables': {
      'fontSize':'16px',
      'primaryColor': 'rgb(251, 255, 3)',
      'primaryTextColor': 'rgb(255, 255, 255)',
      'secondaryColor': 'rgba(0, 219, 243,  0.80)',
      'tertiaryColor': 'rgba(162, 0, 243, 0.80)',
      'tertiaryBorderColor':'rgb(142, 40, 40)'
    }
  }
}%%
mindmap
  root((F103c8t6))
    (HAL抽象层)
        TIM
        PWM
        UART
        DWM
        GPIO
    (RTOS任务处理)
        数据处理和物料转盘舵机、夹取舵机控制任务
        UART数据通讯任务
        28电机升降臂脉冲发送任务
```
----------------------
