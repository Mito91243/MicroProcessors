#include "app.h"
#include "../src/HAL/register_map.h"
SST_LCD lcd = {{EN_PORTB, 12}, {EN_PORTB, 13}, {EN_PORTB, 14}, {EN_PORTB, 15}, {EN_PORTA, 8}, {EN_PORTA, 11}};

ST_BUTTON onoffbtn = {{EN_PORTB, 11}, Active_Low};
ST_BUTTON toggbtn = {{EN_PORTB, 10}, Active_Low};

ST_LED GRN = {{EN_PORTC, 15}, LED_SWITCH_NORMAL};
ST_LED BLU = {{EN_PORTC, 14}, LED_SWITCH_NORMAL};
ST_LED YLW = {{EN_PORTC, 13}, LED_SWITCH_NORMAL};
ST_LED RED = {{EN_PORTA, 2}, LED_SWITCH_NORMAL};

ST_MOTOR motor = {CLOCKWISE, STOPPED};

TimerConfig_t timerConfig = {
    .Timer = TIMER2,
    .Prescaler = 8000 - 1,
    .Period = 2000 - 1,
    .Mode = TIMER_MODE_UP};

void APP_Init(void)
{
    RCC->RCC_APB2ENR |= 0xFC | (1 << 14); // enable GPIO clocks
    Disable_JTAG_Enable_GPIO();

    LCD_Init(lcd);
    LCD_Start(lcd);
    // LCD_ClearDisplay(lcd);

    INIT_ADC_INTPUT();
    TIMER_INIT(&timerConfig);
    TIMER_START(TIMER2);

    Button_init(toggbtn);
    Button_init(onoffbtn);
    MotorInit();

    LED_init(RED);

    usart1_init();
}

void APP_Loop(void)
{
    uint8_t receivedByte = usart1_recByte();
    usart1_sendByte('s');
    //LED_togg(RED);
    if (receivedByte == 1) {
        LED_on(RED);
    } else {
        LED_off(RED);
    }
    LCD_PrintChar(lcd,(char)receivedByte);
}

void APP_Start(void)
{
    APP_Init();
    while (1)
    {
        APP_Loop();
    }
}

/*
    LOOP_ADC();

    uint16_t number = ADC1->ADC_DR;
    float voltage = number * (3.3 / 4095);
    PWM(voltage * (1000 / 3.3));

    //! On-OFF Control
    if (Buttton_state(onoffbtn) == Button_Active)
    {

        if (motor.STATUS == STOPPED)
        {
            MotorStart();
            motor.STATUS = RUNNING;
        }
        else
        {
            MotorStop();
            motor.STATUS = STOPPED;
            LED_off(YLW);
        }

        LED_togg(GRN);

        while (Buttton_state(onoffbtn) == Button_Active)
        {
            Delay_ms(50);
        }
    }

    //! Toggle Direction Control
    if (Buttton_state(toggbtn) == Button_Active)
    {

        if (motor.DIRECTION == ANTICLOCKWISE)
        {
            SwitchDirection();
            motor.DIRECTION = CLOCKWISE;
            LED_off(YLW);
        }
        else
        {
            SwitchDirection();
            motor.DIRECTION = ANTICLOCKWISE;
            LED_on(YLW);
        }

        while (Buttton_state(toggbtn) == Button_Active)
        {
            Delay_ms(50);
        }
    }

    char str[10]; // Buffer for the float as string

    // Convert the float voltage to string with 2 decimal precision
    floatToStr(voltage, str, 2);

    // Display the string on the LCD
    Delay_ms(500);
    LCD_Printstring(lcd, str);
    Delay_ms(500);
    LCD_ClearDisplay(lcd);

*/