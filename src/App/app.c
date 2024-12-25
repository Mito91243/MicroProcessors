#include "app.h"
#include "../src/HAL/register_map.h"
SST_LCD lcd = {{EN_PORTB,12},{EN_PORTB,13},{EN_PORTB,14},{EN_PORTB,15},{EN_PORTA,8},{EN_PORTA,11}};

ST_BUTTON onoffbtn={{EN_PORTB,11},Active_Low};
ST_BUTTON toggbtn={{EN_PORTB,10},Active_Low};

ST_LED GRN = {{EN_PORTC,15},LED_SWITCH_NORMAL};
ST_LED BLU = {{EN_PORTC,14},LED_SWITCH_NORMAL};
ST_LED YLW = {{EN_PORTC,14},LED_SWITCH_NORMAL};

ST_MOTOR motor = {CLOCKWISE,STOPPED};

TimerConfig_t timerConfig = {
    .Timer = TIMER3,
    .Prescaler = 8000-1,
    .Period = 2000-1,
    .Mode = TIMER_MODE_UP
};

void PWM (int x)
{
    RCC-> RCC_APB2ENR |= 0xFC;
    RCC->RCC_APB1ENR |= (1<<1) ;

    PORTA->GPIO_CRL = 0x4B444444;
    TIM3->TIM_CCER = 0x1 << 0; /* CC1P = 0, CC1E = 1 */
    TIM3->TIM_CCMR1 = 0x0068;
    TIM3->TIM_CR1 = 0x80;
    TIM3->TIM_PSC = 200-1; 
    TIM3->TIM_ARR = 1000-1; /* ARR = 999 */
    TIM3->TIM_CCR1= x; /* duty cycle = (300/1000) *100 */
    TIM3->TIM_EGR = 1; /* UG = 1 (generate update) */
    TIM3->TIM_CR1 |= 0x01; /* timer enable (CEN = 1) */
}

void APP_Init(void) {
    Disable_JTAG_Enable_GPIO();
    
    LCD_Init(lcd);
    LCD_Start(lcd);
    LCD_ClearDisplay(lcd);

    INIT_ADC_INTPUT();
    TIMER_INIT(&timerConfig);
    TIMER_START(TIMER3);

    Button_init(toggbtn);
    Button_init(onoffbtn);
    MotorInit();


    LED_init(GRN);
    LED_init(BLU);
    LED_init(YLW);

}
// Function to convert uint16_t to string
void uint16ToStr(uint16_t num, char* str) {
    int i = 0;
    char temp;

    // Extract digits from the number
    do {
        str[i++] = (num % 10) + '0'; // Convert the last digit to char and store
        num /= 10;                  // Remove the last digit
    } while (num > 0);

    str[i] = '\0'; // Null-terminate the string

    // Reverse the string as digits are stored in reverse order
    for (int j = 0; j < i / 2; j++) {
        temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}

void floatToStr(float num, char* str, int precision) {
    int intPart = (int)num; // Get the integer part
    float fracPart = num - intPart; // Get the fractional part

    // Convert integer part to string
    uint16ToStr(intPart, str);

    // Move the pointer to the end of the integer part
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }

    // Add decimal point
    str[i++] = '.';

    // Convert fractional part to string
    for (int j = 0; j < precision; j++) {
        fracPart *= 10;
        int fracDigit = (int)fracPart;
        str[i++] = fracDigit + '0';
        fracPart -= fracDigit;
    }

    // Null-terminate the string
    str[i] = '\0';
}


void APP_Loop(void) {
    LOOP_ADC();

    uint16_t number = ADC1->ADC_DR;
    float voltage = number * (3.3 / 4095);
    PWM(voltage * (1000/3.3));
    
   
    //! On-OFF Control
    if(Buttton_state(onoffbtn) == Button_Active) {
        
        if(motor.STATUS == STOPPED) {
            MotorStart();
            motor.STATUS = RUNNING;
        } else {
            MotorStop();
            motor.STATUS = STOPPED;
            LED_off(YLW);
        }
        
        LED_togg(GRN);
        
        while(Buttton_state(onoffbtn) == Button_Active) {
            Delay_ms(50);
        }
    }
   
    //! Toggle Direction Control
    if(Buttton_state(toggbtn) == Button_Active) {

        if(motor.DIRECTION == ANTICLOCKWISE) {
            SwitchDirection();
            motor.DIRECTION = CLOCKWISE;
            LED_off(YLW);

        } else {
            SwitchDirection();
            motor.DIRECTION = ANTICLOCKWISE;
            LED_on(YLW);
        }

        while(Buttton_state(toggbtn) == Button_Active) {
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
}


void APP_Start(void) {
    APP_Init();
    while (1) {
        APP_Loop();
    }
}

