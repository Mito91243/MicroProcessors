#ifndef _SYSTICK_H_
#define _SYSTICK_H_
#include "../../Common/bitop.h"
#include "../register.h"
#pragma GCC optimize "O0" 

#define SYS_CLK 4000000
#define SYSTICK_1MS_LOAD ((SYS_CLK / 1000) - 1)
#define SYSTICK_1S_LOAD (SYS_CLK - 1)

typedef struct
{
    uint32_t ENABLE : 1;
    uint32_t INTEN : 1;
    uint32_t CLKSRC : 1;
    uint32_t : 13;
    uint32_t COUNT : 1;
    uint32_t : 15;
} SYSTICK_TYPEDEF_CTL;

typedef struct
{
    __IO SYSTICK_TYPEDEF_CTL CTL;
    __IO uint32_t LOAD;
    __IO uint32_t VAL;
} SYSTICK_TYPEDEF;

#define SYSTICK ((SYSTICK_TYPEDEF *)SYSTICK_BASE)

void SysTick_Delay_1MS(volatile uint32_t c);
//void SysTick_Delay_1S(volatile uint32_t c);

#endif