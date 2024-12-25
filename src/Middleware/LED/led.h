#ifndef __LED_H__
#define __LED_H__
#include "../../HAL/GPIO/gpio.h"

typedef enum
{
    LED_SWITCH_INVERTED,
    LED_SWITCH_NORMAL
} EN_LED_SWITCH_INV;

typedef struct
{
    ST_PORT_PIN PortPin;
    EN_LED_SWITCH_INV Inv;
} ST_LED;

EN_IO_STAT_t LED_init(ST_LED led);
EN_IO_STAT_t LED_on(ST_LED led);
EN_IO_STAT_t LED_off(ST_LED led);
EN_IO_STAT_t LED_togg(ST_LED led);

#endif