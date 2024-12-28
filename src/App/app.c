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
ST_BUTTON incbtn = {{EN_PORTB, 1}, Active_Low};
ST_BUTTON decbtn = {{EN_PORTB, 0}, Active_Low};


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

// Helper function to update the LCD
void Update_LCD(void)
{
    uint32_t minutes = stopwatch.CURRTIME / 60;
    uint32_t seconds = stopwatch.CURRTIME % 60;
    char time_str[6];
    sprintf(time_str, "%02lu:%02lu", minutes, seconds);
    LCD_clear(lcd);
    LCD_WriteStr(lcd, time_str);
}

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
    Button_init(incbtn);
    Button_init(decbtn);

    LED_init(RED);
    LED_init(BLU);

    usart1_init();
    Delay_ms(500);

    LCD_WriteStr(lcd, "00:00");
    LED_on(RED);  // Indicate stopped state with the red LED

}

void APP_Loop(void)
{
    // Toggle between modes (Stopwatch <-> Timer)
    if (Buttton_state(toggbtn) == Button_Active) {
        stopwatch.MODE = (stopwatch.MODE == STOPWATCH) ? TIMER : STOPWATCH;
        stopwatch.STATUS = STOPPED;
        stopwatch.CURRTIME = 0;
        stopwatch.TIME = 0;
        LCD_clear(lcd);
        Update_LCD();
        LED_on(RED);
        LED_off(BLU);
        while (Buttton_state(toggbtn) == Button_Active) Delay_ms(50);  // Debounce
    }

    // Adjust preset time in Stopwatch mode
    if (stopwatch.MODE == STOPWATCH && stopwatch.STATUS == STOPPED) {
        if (Buttton_state(incbtn) == Button_Active) {
            stopwatch.TIME+=60;
            stopwatch.CURRTIME = stopwatch.TIME;
            Update_LCD();
            while (Buttton_state(incbtn) == Button_Active) Delay_ms(50);  // Debounce
        }
        if (Buttton_state(decbtn) == Button_Active && stopwatch.TIME > 0) {
            stopwatch.TIME-=60;
            stopwatch.CURRTIME = stopwatch.TIME;
            Update_LCD();
            while (Buttton_state(decbtn) == Button_Active) Delay_ms(50);  // Debounce
        }
    }

    // Start/Stop functionality with On/Off button
    if (Buttton_state(onoffbtn) == Button_Active) {
        if (stopwatch.STATUS == COUNTING) {
            stopwatch.STATUS = STOPPED;
            LED_on(RED);
            LED_off(BLU);
        } else {
            stopwatch.STATUS = COUNTING;
            LED_off(RED);
            LED_on(BLU);
        }

        // Long press to reset and stop
        uint8_t counter = 0;
        while (Buttton_state(onoffbtn) == Button_Active) {
            Delay_ms(50);
            counter++;
            if (counter >= 60) {  // 3 seconds
                stopwatch.STATUS = STOPPED;
                stopwatch.CURRTIME = (stopwatch.MODE == STOPWATCH) ? stopwatch.TIME : 0;
                stopwatch.TIME = 0;
                LED_on(RED);
                LED_off(BLU);
                Update_LCD();
                Delay_ms(500);
                break;
            }
        }
    }

    // Timer/Stopwatch operation
    if (stopwatch.STATUS == COUNTING) {
        Delay_ms(1000);  // Wait for 1 second
        if (stopwatch.MODE == STOPWATCH) {
            if (stopwatch.CURRTIME > 0) stopwatch.CURRTIME--;
            if (stopwatch.CURRTIME == 0) {
                stopwatch.STATUS = STOPPED;
                stopwatch.TIME = 0;
                LED_on(RED);
                LED_off(BLU);
            }
        } else {  // TIMER mode
            stopwatch.CURRTIME++;
        }
        Update_LCD();
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
