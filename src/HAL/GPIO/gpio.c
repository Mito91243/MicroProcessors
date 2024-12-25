#include "gpio.h"

GPIO_Typedef *GET_GPIO_PORT_REG(EN_PORTx PORT)
{
    GPIO_Typedef *PORT_R = NULL;
    switch (PORT)
    {
    case EN_PORTA:
        PORT_R = PORTA;
        break;
    case EN_PORTB:
        PORT_R = PORTB;
        break;
    case EN_PORTC:
        PORT_R = PORTC;
        break;
    case EN_PORTD:
        PORT_R = PORTD;
        break;
    }
    return PORT_R;
}

EN_IO_STAT_t SET_RCCGPIO(EN_PORTx PORT)
{
    SET_BIT(RCC->RCC_APB2ENR, PORT + 2);
    if (READ_BIT(RCC->RCC_APB2ENR, PORT + 2))
        return OK;
    return ERROR;
}

EN_IO_STAT_t CONF_GPIO(ST_PORT_PIN PortPin, ST_PORT_PIN_CONF CONF) {
    
    GPIO_Typedef *PORT_R = GET_GPIO_PORT_REG(PortPin.port);
    SET_RCCGPIO(PortPin.port);
    SET_GPIO_DIR_MODE(PORT_R, PortPin.pin, CONF.DIR, CONF.TYPE, CONF.SPEED);
    return OK;
}

EN_IO_STAT_t SET_GPIO_DIR_MODE(GPIO_Typedef *PORT_X, uint8_t PIN, EN_IO_DIR_t DIR, uint8_t TYPE, EN_IO_OUT_SPEED_t SPEED)
{
    PORT_X->GPIO_CRH &= ~(0xF << ((15 - 8) * 4)); // Clear configuration bits for PA15
    PORT_X->GPIO_CRH |=  (0x3 << ((15 - 8) * 4)); // Set PA15 as output at 50 MHz push-pull

    if (DIR == INPUT)
    {
        SET_GPIO_INPUT(PORT_X, PIN, TYPE);
    }
    else
    {
        SET_GPIO_OUTPUT(PORT_X, PIN, TYPE, SPEED);
    }
    return OK;
}

EN_IO_STAT_t SET_GPIO_INPUT(GPIO_Typedef *PORT_X, uint8_t PIN, EN_IO_INPUT_t TYPE)
{
    uint8_t Type = TYPE < 2 ? TYPE : 3;
    uint8_t MODE_TYPE = Type << 2;
    if (PIN < 8)
    {
        SET_MBIT_SHF(PORT_X->GPIO_CRL, 7, MODE_TYPE, 4 * PIN);
    }
    else
    {
        SET_MBIT_SHF(PORT_X->GPIO_CRH, 7, MODE_TYPE, 4 * PIN);
    }

    if (TYPE > 1)
    {
        if (TYPE == INPUT_PULLDOWN)
        {
            CLR_BIT(PORT_X->GPIO_ODR, PIN);
        }
        else
        {
            SET_BIT(PORT_X->GPIO_ODR, PIN);
        }
    }
    return OK;
}

EN_IO_STAT_t SET_GPIO_OUTPUT(GPIO_Typedef *PORT_X, uint8_t PIN, EN_IO_OUTPUT_t TYPE, EN_IO_OUT_SPEED_t SPEED)
{

    uint8_t MODE_TYPE = TYPE << 2 | SPEED;
    if (PIN < 8)
    {
        SET_MBIT_SHF(PORT_X->GPIO_CRL, 7, MODE_TYPE, 4 * PIN);
    }
    else
    {
        SET_MBIT_SHF(PORT_X->GPIO_CRH, 7, MODE_TYPE, 4 * (PIN-8));
    }
    return OK;
}

EN_IO_STAT_t SET_GPIO_OUT_LEVEL(GPIO_Typedef *PORT_X, uint8_t PIN, EN_IO_LEVEL_t LEVEL)
{

    if (LEVEL == HIGH)
    {
        SET_BIT(PORT_X->GPIO_BSRR, PIN);
    }
    else
    {
        SET_BIT(PORT_X->GPIO_BSRR, PIN + 16);
    }
    return OK;
}

EN_IO_STAT_t TOG_GPIO_OUT_LEVEL(GPIO_Typedef *PORT_X, uint8_t PIN)
{
    TOG_BIT(PORT_X->GPIO_ODR, PIN);
    return OK;
}

EN_IO_LEVEL_t READ_GPIO_IN_LEVEL(GPIO_Typedef *PORT_X, uint8_t PIN) {
    return READ_BIT(PORT_X->GPIO_IDR, PIN);
}

EN_IO_STAT_t GPIO_OUTPUT_LEVEL(ST_PORT_PIN PortPin, EN_IO_LEVEL_t LEVEL) {
    return SET_GPIO_OUT_LEVEL(GET_GPIO_PORT_REG(PortPin.port), PortPin.pin, LEVEL);
}

EN_IO_STAT_t GPIO_OUTPUT_TOGG(ST_PORT_PIN PortPin) {
    return TOG_GPIO_OUT_LEVEL(GET_GPIO_PORT_REG(PortPin.port), PortPin.pin);
}

EN_IO_LEVEL_t GPIO_INPUT_READ(ST_PORT_PIN PortPin) {
    return READ_GPIO_IN_LEVEL(GET_GPIO_PORT_REG(PortPin.port), PortPin.pin);
}

// Function to disable JTAG and enable GPIO on JTAG pins
void Disable_JTAG_Enable_GPIO(void)
{
    volatile uint32_t *RCC_APB2ENR = (uint32_t *)0x40021018; // RCC APB2 peripheral clock enable register
    volatile uint32_t *AFIO_MAPR = (uint32_t *)0x40010004;   // AFIO remap and debug I/O configuration register

    *RCC_APB2ENR |= (1 << 0); // Set bit 0 (AFIOEN) to enable AFIO clock

    *AFIO_MAPR &= ~(0x7 << 24); // Clear bits 26:24
    *AFIO_MAPR |= (0x2 << 24);  // Set bits 26:24 to 0b010

    // Now, PA15 (JTDI), PB3 (JTDO), and PB4 (NJTRST) are free for GPIO use
}