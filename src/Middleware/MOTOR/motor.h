#ifndef __MOTOR_H__
#define __MOTOR_H__
#include "../../HAL/GPIO/gpio.h"
#include "../../HAL/register.h"
typedef enum
{
    ANTICLOCKWISE,
    CLOCKWISE
} EN_MOTOR_DIRECTION;

typedef enum
{
    RUNNING,
    STOPPED
} EN_MOTOR_STATUS;

typedef struct
{
    EN_MOTOR_DIRECTION DIRECTION;
    EN_MOTOR_STATUS STATUS;
} ST_MOTOR;

void SwitchDirection(void);
void MotorStart(void);
void MotorStop(void);
void MotorInit(void);

#endif