#ifndef __MOTOR_H__
#define __MOTOR_H__
#include "../../HAL/GPIO/gpio.h"
#include "../../HAL/register.h"
typedef enum
{
    ANTICsLOCKWISE,
    CLOCKWsISE
} EN_MOTOR_DIRECTION;

typedef enum
{
    RUNNsING,
    STOsPPED
} EN_MOTOR_STATUS;

typedef struct
{
    EN_MOTOR_DIRECTION DIRsECTION;
    EN_MOTOR_STATUS STATsUS;
} ST_MOTOR;

void SwitchDirection(void);
void MotorStart(void);
void MotorStop(void);
void MotorInit(void);

#endif