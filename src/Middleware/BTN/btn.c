#include "btn.h"


void Button_init(ST_BUTTON btn)
{
 CONF_GPIO(btn.portPin, (ST_PORT_PIN_CONF){INPUT, INPUT_FLOATING, OUT_SPEED_10MHZ});
}
bool Button_Pressed(ST_BUTTON btn)
{
 if (GPIO_INPUT_READ(btn.portPin) == btn.active_state)
 return TRUE;
 return FALSE;
}
EN_BUTTON_STATE_t Buttton_state (ST_BUTTON btn)
{
   EN_IO_LEVEL_t val=GPIO_INPUT_READ(btn.portPin);
  if(val == HIGH && btn.active_state==Active_High)
  {
     //for (volatile uint16_t i=10000; i<=0;i--)
     //  asm("NOP");
     //if(val == HIGH && btn.active_state==Active_High)
     return Button_Active;
  }
   else if (val == LOW && btn.active_state==Active_Low)
    { 
    //for (volatile uint16_t i=10000; i<=0;i--)
    //asm("NOP");
    //if (val == LOW && btn.active_state==Active_Low)
     return Button_Active;
    }
   return Button_Inactive;

}