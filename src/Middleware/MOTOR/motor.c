#include "motor.h"

ST_PORT_PIN B4= {EN_PORTB,4};
ST_PORT_PIN B5= {EN_PORTB,5};
ST_PORT_PIN B6= {EN_PORTB,6};
ST_PORT_PIN B7= {EN_PORTB,7};


void MotorInit(void) {
    CONF_GPIO(B4, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(B5, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(B6, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(B7, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
}

void MotorStart(void) {
    GPIO_OUTPUT_LEVEL(B4,HIGH);
    GPIO_OUTPUT_LEVEL(B5,HIGH);
    GPIO_OUTPUT_LEVEL(B6,LOW);
    GPIO_OUTPUT_LEVEL(B7,LOW);
}

void SwitchDirection(void) {
    GPIO_OUTPUT_TOGG(B4);
    GPIO_OUTPUT_TOGG(B5);
    GPIO_OUTPUT_TOGG(B6);
    GPIO_OUTPUT_TOGG(B7);
}

void MotorStop(void) {
    GPIO_OUTPUT_LEVEL(B4,LOW);
    GPIO_OUTPUT_LEVEL(B5,LOW);
    GPIO_OUTPUT_LEVEL(B6,LOW);
    GPIO_OUTPUT_LEVEL(B7,LOW);
}