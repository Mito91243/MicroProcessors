#ifndef __GPIO_H__
#define __GPIO_H__
#include "../register.h"

typedef enum
{
    EN_PORTA,
    EN_PORTB,
    EN_PORTC,
    EN_PORTD
} EN_PORTx;

typedef enum
{
    LOW,
    HIGH
} EN_IO_LEVEL_t;

typedef enum
{
    INPUT,
    OUTPUT
} EN_IO_DIR_t;

typedef enum
{
    OK,
    ERROR
} EN_IO_STAT_t;

typedef enum
{
    UNLOCKED,
    LOCKED
} EN_IO_LOK_STAT_t;

typedef enum
{
    INPUT_ANALOG,
    INPUT_FLOATING,
    INPUT_PULLDOWN,
    INPUT_PULLUP
} EN_IO_INPUT_t;

typedef enum
{
    GEN_OUT_PUSH,
    GEN_OUT_OPEN,
    ALT_FUNC_PUSH,
    ALT_FUNC_OPEN
} EN_IO_OUTPUT_t;

typedef enum
{
    OUT_SPEED_10MHZ = 1,
    OUT_SPEED_2MHZ,
    OUT_SPEED_50MHZ
} EN_IO_OUT_SPEED_t;

typedef struct
{
    EN_PORTx port;
    uint32_t pin;
} ST_PORT_PIN;

typedef struct
{
    EN_IO_DIR_t DIR;
    uint8_t TYPE;
    EN_IO_OUT_SPEED_t SPEED;
} ST_PORT_PIN_CONF;

GPIO_Typedef *GET_GPIO_PORT_REG(EN_PORTx PORT);
EN_IO_STAT_t SET_RCCGPIO(EN_PORTx PORT);
EN_IO_STAT_t CONF_GPIO(ST_PORT_PIN PortPin, ST_PORT_PIN_CONF CONF);
EN_IO_STAT_t SET_GPIO_DIR_MODE(GPIO_Typedef *PORT_X, uint8_t PIN, EN_IO_DIR_t DIR, uint8_t TYPE, EN_IO_OUT_SPEED_t SPEED);
EN_IO_STAT_t SET_GPIO_INPUT(GPIO_Typedef *PORT_X, uint8_t PIN, EN_IO_INPUT_t TYPE);
EN_IO_STAT_t SET_GPIO_OUTPUT(GPIO_Typedef *PORT_X, uint8_t PIN, EN_IO_OUTPUT_t TYPE, EN_IO_OUT_SPEED_t SPEED);
EN_IO_STAT_t SET_GPIO_OUT_LEVEL(GPIO_Typedef *PORT_X, uint8_t PIN, EN_IO_LEVEL_t LEVEL);
EN_IO_STAT_t TOG_GPIO_OUT_LEVEL(GPIO_Typedef *PORT_X, uint8_t PIN);
EN_IO_LEVEL_t READ_GPIO_IN_LEVEL(GPIO_Typedef *PORT_X, uint8_t PIN);
void Disable_JTAG_Enable_GPIO(void);

EN_IO_STAT_t GPIO_OUTPUT_LEVEL(ST_PORT_PIN PortPin, EN_IO_LEVEL_t LEVEL);
EN_IO_STAT_t GPIO_OUTPUT_TOGG(ST_PORT_PIN PortPin);
EN_IO_LEVEL_t GPIO_INPUT_READ(ST_PORT_PIN PortPin);
#endif