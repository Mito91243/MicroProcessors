#ifndef _BUTTON_H_
#define _BUTTON_H_
#include "../../HAL/GPIO/gpio.h"
#include <stdbool.h>
typedef enum
 { 
    Active_Low,
    Active_High
}EN_BUTTON_Active_STATE_t;
typedef struct 
{
    ST_PORT_PIN portPin;
    EN_BUTTON_Active_STATE_t active_state;
    
}ST_BUTTON;
typedef enum 
{
    Button_Active,Button_Inactive
}EN_BUTTON_STATE_t;

void Button_init(ST_BUTTON btn);
bool Button_Pressed(ST_BUTTON btn);
EN_BUTTON_STATE_t Buttton_state (ST_BUTTON btn );

#endif