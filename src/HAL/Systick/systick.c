#include "systick.h"

void SysTick_Delay_1MS(__IO uint32_t c)
{
    SYSTICK->LOAD = SYSTICK_1MS_LOAD;
    SYSTICK->VAL = 0;
    SET(SYSTICK->CTL.CLKSRC);
    SET(SYSTICK->CTL.ENABLE);
    for (volatile uint32_t i=0; i < c; i++)
    {
        SYSTICK->VAL = 0;
        while (NCHK(SYSTICK->CTL.COUNT));
    }
    CLR(SYSTICK->CTL.ENABLE);
}