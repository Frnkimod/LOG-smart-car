// dwt.c
// Author: Franki
// Date: 2025-01-11
#include "dwt.h"

uint8_t dwt_init(void) {
    /* 禁用 TRC */
    CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk; // ~0x01000000;
    /* 开启 TRC */
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // 0x01000000;

    /* 禁用时钟周期计数器 */
    DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001;
    /*启用时钟周期计数器 */
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; //0x00000001;

    /* 重置时钟周期计数器值 */
    DWT->CYCCNT = 0;

    __ASM volatile ("NOP");
    __ASM volatile ("NOP");
    __ASM volatile ("NOP");

    /* 检查时钟周期计数器是否已启动 */
    if (DWT->CYCCNT) {
        return 1; /*时钟周期计数器启动*/
    } else {
        return 0; /*时钟周期计数器未启动*/
    }
}

void dwt_delay_us(volatile uint16_t us) {
    uint32_t au32_initial_ticks = DWT->CYCCNT;
    uint32_t au32_ticks = (HAL_RCC_GetHCLKFreq() / 1000000);
    us *= au32_ticks;
    while ((DWT->CYCCNT - au32_initial_ticks) < (us - au32_ticks))
        ;
}

void dwt_delay_ms(volatile uint16_t ms) {
    uint32_t au32_initial_ticks = DWT->CYCCNT;
    uint32_t au32_ticks = (HAL_RCC_GetHCLKFreq() / 1000);
    uint32_t ms_new = ms * au32_ticks;
    while ((DWT->CYCCNT - au32_initial_ticks) < (ms_new - au32_ticks))
        ;
}

// Your C functions and implementation go here