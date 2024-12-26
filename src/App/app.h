#ifndef __APP_H__
#define __APP_H__
#include "../Middleware/LED/led.h"
#include "../Middleware/SS/SS.h"
#include "../Middleware/LCD/lcd.h"
#include "../Middleware/BTN/btn.h"
#include "../Middleware/MOTOR/motor.h"
#include "../Middleware/STOPWATCH/stopwatch.h"

#include "../HAL/Systick/systick.h"
#include "../HAL/TIMER/timer.h"
#include "../HAL/ADC/ADC.h"
#include "../HAL/GPIO/gpio.h"
#include "../HAL/USART/USART.h"

#include "../Middleware/helpers/helper.h"

void APP_Init(void);
void APP_Loop(void);
void APP_Start(void);

#endif