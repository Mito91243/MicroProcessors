#include "app.h"
#include "../src/HAL/register_map.h"

ST_LCD lcd = {
    {EN_PORTB, 15},
    {EN_PORTB, 14},
    {EN_PORTB, 13},
    {EN_PORTB, 12},
    {EN_PORTA, 11},
    {EN_PORTA, 8}
};
ST_BUTTON onoffbtn = {{EN_PORTB, 11}, Active_Low};
ST_BUTTON toggbtn = {{EN_PORTB, 10}, Active_Low};

ST_LED GRN = {{EN_PORTC, 15}, LED_SWITCH_NORMAL};
ST_LED BLU = {{EN_PORTC, 14}, LED_SWITCH_NORMAL};
ST_LED YLW = {{EN_PORTC, 13}, LED_SWITCH_NORMAL};
ST_LED RED = {{EN_PORTA, 2}, LED_SWITCH_NORMAL};

//ST_MOTOR motor = {CLOCKWISE, STOPPED};

ST_STOPWATCH stopwatch = {
    STOPWATCH , STOPPED , 0 , 0
};

TimerConfig_t timerConfig = {
    .Timer = TIMER2,
    .Prescaler = 8000 - 1,
    .Period = 2000 - 1,
    .Mode = TIMER_MODE_UP};

uint32_t count =0;
char time_str[6]; // Buffer for MM:SS format
 uint8_t activate_stopwatch = 0;


void APP_Init(void)
{
    RCC->RCC_APB2ENR |= 0xFC | (1 << 14); // enable GPIO clocks
    Disable_JTAG_Enable_GPIO();

    LCD_init(lcd);
    LCD_Start(lcd);
    LCD_clear(lcd);

    INIT_ADC_INTPUT();
    TIMER_INIT(&timerConfig);
    TIMER_START(TIMER2);

    Button_init(toggbtn);
    Button_init(onoffbtn);
    MotorInit();

    LED_init(RED);

    usart1_init();
    Delay_ms(500);

}

void APP_Loop(void)
{
if (Buttton_state(onoffbtn) == Button_Active)
{
    if (stopwatch.STATUS == COUNTING) {
        LED_off(RED);
        stopwatch.STATUS = STOPPED;
    }
    else {
        LED_on(RED);
        stopwatch.STATUS = COUNTING;
    }
    
    // Initialize counter for detecting long press (3 seconds)
    uint8_t c = 0;
    
    // Loop while the button remains pressed
    while (Buttton_state(onoffbtn) == Button_Active)
    {
        Delay_ms(50); // Wait for 50ms
        c++;          // Increment counter
        
        // Check if button has been held for 3 seconds
        if (c >= 60) { // 60 * 50ms = 3000ms = 3 seconds
            // Reset the stopwatch
            stopwatch.CURRTIME = 0;
            stopwatch.STATUS = STOPPED;
            
            // Turn off the LED as the stopwatch is stopped
            LED_off(RED);
            
    // Format the time as "MM:SS"
    sprintf(time_str, "%02lu:%02lu", 0, 0);
            
            // Optional: Clear the LCD before writing (to prevent overlapping characters)
            LCD_clear(lcd);
                        
            // Write "00:00" to the LCD
            LCD_WriteStr(lcd, time_str);
            Delay_ms(100);
            // Optionally, break out of the loop after resetting
            break;
        }
    }
}

    if (stopwatch.STATUS == COUNTING) {
    Sec_timer(999);
    LCD_clear(lcd);
    Delay_ms(50);
    stopwatch.CURRTIME += 1;

    // Calculate minutes and seconds from total seconds
    uint32_t minutes = stopwatch.CURRTIME / 60;
    uint32_t seconds = stopwatch.CURRTIME % 60;

    // Format the time as "MM:SS"
    sprintf(time_str, "%02lu:%02lu", minutes, seconds);

    // Display the formatted time on the LCD
    LCD_WriteStr(lcd, time_str);

    // Wait for 1 second
    //Delay_ms(1000);
    }

    if (Buttton_state(toggbtn) == Button_Active)
    {
        LED_off(RED);
        stopwatch.STATUS = STOPPED;

        while (Buttton_state(toggbtn) == Button_Active)
        {
            Delay_ms(50);
        }
    }
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
/*

    uint8_t receivedByte = usart1_recByte();
        Delay_ms(500);

    usart1_sendByte((char)receivedByte);
    Delay_ms(500);


        char str[10]; // Buffer for the float as string
    // Convert the float voltage to string with 2 decimal precision
    floatToStr(receivedByte, str, 0);
    
*/