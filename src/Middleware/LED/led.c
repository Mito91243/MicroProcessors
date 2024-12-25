#include "led.h"

EN_IO_STAT_t LED_init(ST_LED led) {
    return CONF_GPIO(led.PortPin, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
}

EN_IO_STAT_t LED_on(ST_LED led) {
    if (led.Inv == LED_SWITCH_NORMAL) {
        return GPIO_OUTPUT_LEVEL(led.PortPin, HIGH);
    }
    return GPIO_OUTPUT_LEVEL(led.PortPin, LOW);
}

EN_IO_STAT_t LED_off(ST_LED led) {
       if (led.Inv == LED_SWITCH_NORMAL) {
        return GPIO_OUTPUT_LEVEL(led.PortPin, LOW);
    }
    return GPIO_OUTPUT_LEVEL(led.PortPin, HIGH); 
}

EN_IO_STAT_t LED_togg(ST_LED led) {
    GPIO_OUTPUT_TOGG(led.PortPin);
}