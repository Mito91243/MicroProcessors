#include "timer.h"

EN_IO_STAT_t SET_RCCTIM(EN_TIMERx TIMER)
{
    SET_BIT(RCC->RCC_APB1ENR,TIMER);
    if (READ_BIT(RCC->RCC_APB1ENR,TIMER)) {
       return OK;
    }
    return ERROR;
}

TIM_Typedef *GET_TIMER_REG(EN_TIMERx TIMER)
{
    TIM_Typedef * Timer_R = NULL;
    switch (TIMER)
    {
    case TIMER2:
        Timer_R = TIM2;
         break;
    case TIMER3:
        Timer_R = TIM3;
         break;
    case TIMER4:
        Timer_R = TIM4;
         break;
    case TIMER5:
        Timer_R = TIM5;
        break;
    }
    return Timer_R;
}

EN_IO_STAT_t TIMER_INIT(TimerConfig_t *config)
{
    if(!config) return ERROR;
    if(SET_RCCTIM(config->Timer) == ERROR) return ERROR;
    TIM_Typedef *Timer_R= GET_TIMER_REG(config->Timer);
    Timer_R->TIM_PSC = config->Prescaler;
        Timer_R->TIM_ARR = config->Period;
    if(config->Mode == TIMER_MODE_UP) {
        SET_BIT(Timer_R->TIM_CR1,4);
    } else {
        CLR_BIT(Timer_R->TIM_CR1,4);
    }
    SET_BIT(Timer_R->TIM_CR1,7);
    return OK;
}

void TIMER_START(EN_TIMERx TIMER)
{
    TIM_Typedef *Timer_R= GET_TIMER_REG(TIMER);
    SET_BIT(Timer_R->TIM_CR1,0);
}

void TIMER_STOP(EN_TIMERx TIMER)
{
    TIM_Typedef *Timer_R= GET_TIMER_REG(TIMER);
    CLR_BIT(Timer_R->TIM_CR1,0);
}

void TIMER_SET_PERIOD(EN_TIMERx TIMER, uint32_t period)
{
        TIM_Typedef *Timer_R= GET_TIMER_REG(TIMER);
        Timer_R->TIM_ARR = period;
}

void TIMER_WAIT_UNTIL_FINISHED(EN_TIMERx TIMER)
{
    TIM_Typedef *Timer_R= GET_TIMER_REG(TIMER);
    while(!CHK_BIT(Timer_R->TIM_SR,0));
    CLR_BIT(Timer_R->TIM_SR,0);
}
