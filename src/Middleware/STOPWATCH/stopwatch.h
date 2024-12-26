#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_


#include "../../HAL/GPIO/gpio.h"
#include "../../HAL/register.h"

typedef enum
{
    STOPWATCH,
    TIMER
} EN_STOPWATCH_MODE;

typedef enum
{
    COUNTING,
    STOPPED
} EN_STOPWATCH_STATUS;

typedef struct
{
    EN_STOPWATCH_MODE MODE;
    EN_STOPWATCH_STATUS STATUS;
    uint32_t TIME;
    uint32_t CURRTIME;
    uint8_t HOLD;
} ST_STOPWATCH;


void Sec_timer(uint16_t x);

#endif