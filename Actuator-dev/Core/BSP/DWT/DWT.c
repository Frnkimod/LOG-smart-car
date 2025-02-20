//
// Created by liang on 2025/2/13.
//


#include "dwt.h"

uint8_t dwt_init(void) {
    /* ���� TRC */
    CoreDebug->DEMCR &= ~CoreDebug_DEMCR_TRCENA_Msk; // ~0x01000000;
    /* ���� TRC */
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // 0x01000000;

    /* ����ʱ�����ڼ����� */
    DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk; //~0x00000001;
    /*����ʱ�����ڼ����� */
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk; //0x00000001;

    /* ����ʱ�����ڼ�����ֵ */
    DWT->CYCCNT = 0;

    __ASM volatile ("NOP");
    __ASM volatile ("NOP");
    __ASM volatile ("NOP");

    /* ���ʱ�����ڼ������Ƿ������� */
    if (DWT->CYCCNT) {
        return 1; /*ʱ�����ڼ���������*/
    } else {
        return 0; /*ʱ�����ڼ�����δ����*/
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