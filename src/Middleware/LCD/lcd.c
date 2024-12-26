#include "lcd.h"
void LCD_init(ST_LCD lcd){
    CONF_GPIO(lcd.DB4, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(lcd.DB5, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(lcd.DB6, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(lcd.DB7, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(lcd.EN, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(lcd.RS, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ}); 
}

void LCD_Start(ST_LCD lcd){
    LCD_WriteCommand(lcd, 0x00);
    for(volatile int i = 1065244; i <= 0; i--){
        asm("NOP");
    }
    LCD_WriteCommand(lcd, 0x03);
    for(volatile int i = 5065244; i <= 0; i--){
        asm("NOP");
    }
    LCD_WriteCommand(lcd, 0x03);
    for(volatile int i = 10065244; i <= 0; i--){
        asm("NOP");
    }
    LCD_WriteCommand(lcd, 0x03);
    LCD_WriteCommand(lcd, 0x02);
    LCD_WriteCommand(lcd, 0x02);
    LCD_WriteCommand(lcd, 0x08);
    LCD_WriteCommand(lcd, 0x00);
    LCD_WriteCommand(lcd, 0x0C);
    LCD_WriteCommand(lcd, 0x00);
    LCD_WriteCommand(lcd, 0x00);
    
}

void LCD_WriteCommand(ST_LCD lcd, uint8_t data){
    GPIO_OUTPUT_LEVEL(lcd.RS, LOW);
    GPIO_OUTPUT_LEVEL(lcd.DB7, (data & 128) >> 7);
    GPIO_OUTPUT_LEVEL(lcd.DB6, (data & 64) >> 6);
    GPIO_OUTPUT_LEVEL(lcd.DB5, (data & 32) >> 5);
    GPIO_OUTPUT_LEVEL(lcd.DB4, (data & 16) >> 4);
    GPIO_OUTPUT_LEVEL(lcd.EN, HIGH);
    Delay_ms(10);
    GPIO_OUTPUT_LEVEL(lcd.EN, LOW);
    GPIO_OUTPUT_LEVEL(lcd.DB7, (data & 8) >> 3);
    GPIO_OUTPUT_LEVEL(lcd.DB6, (data & 4) >> 2);
    GPIO_OUTPUT_LEVEL(lcd.DB5, (data & 2) >> 1);
    GPIO_OUTPUT_LEVEL(lcd.DB4, data & 1);
    GPIO_OUTPUT_LEVEL(lcd.EN, HIGH);
    Delay_ms(10);
    GPIO_OUTPUT_LEVEL(lcd.EN, LOW);
    //delay 5u
    Delay_ms(10);
}

void LCD_WriteChar(ST_LCD lcd, uint16_t data){
    GPIO_OUTPUT_LEVEL(lcd.RS, HIGH);
    GPIO_OUTPUT_LEVEL(lcd.DB7, (data & 128) >> 7);
    GPIO_OUTPUT_LEVEL(lcd.DB6, (data & 64) >> 6);
    GPIO_OUTPUT_LEVEL(lcd.DB5, (data & 32) >> 5);
    GPIO_OUTPUT_LEVEL(lcd.DB4, (data & 16) >> 4);
    GPIO_OUTPUT_LEVEL(lcd.EN, HIGH);
    Delay_ms(10);
    GPIO_OUTPUT_LEVEL(lcd.EN, LOW);
    GPIO_OUTPUT_LEVEL(lcd.DB7, (data & 8) >> 3);
    GPIO_OUTPUT_LEVEL(lcd.DB6, (data & 4) >> 2);
    GPIO_OUTPUT_LEVEL(lcd.DB5, (data & 2) >> 1);
    GPIO_OUTPUT_LEVEL(lcd.DB4, data & 1);
    GPIO_OUTPUT_LEVEL(lcd.EN, HIGH);
    Delay_ms(10);
    GPIO_OUTPUT_LEVEL(lcd.EN, LOW);
    //delay 5u
    Delay_ms(10);
}

void LCD_WriteStr(ST_LCD lcd, char* p){
    uint8_t i = 0;
    while(p[i] != '\0'){
        LCD_WriteChar(lcd, p[i]);
        i++;
        Delay_ms(10);
    }
}

void LCD_SetCursor(ST_LCD lcd, uint8_t row, uint8_t col){
    uint8_t address;
    if (row == 0)
        address = 0x00 + col;
    else if (row == 1)
        address = 0x40 + col; 
    else
        return; 
    LCD_WriteCommand(lcd, 0x80 | address);
}

void LCD_clear(ST_LCD lcd){
    LCD_WriteCommand(lcd, 0x01);
}
void LCD_PrintNumber(ST_LCD lcd,uint32_t num) {
    if (num == 0) {
        LCD_WriteChar(lcd,'0'); // Handle the case when num is 0
        return;
    }

    uint32_t divisor = 1;
    // Find the largest power of 10 less than or equal to num
    while (num / divisor >= 10) {
        divisor *= 10;
    }

    // Extract and print each digit
    while (divisor > 0) {
        uint8_t digit = num / divisor; // Get the leading digit
        LCD_WriteChar(lcd,'0' + digit);   // Convert digit to character and print
        num %= divisor;               // Remove the leading digit
        divisor /= 10;                // Move to the next digit
    }
}