#ifndef _LIQUIDCRYSTAL_H_
#define _LIQUIDCRYSTAL_H_
#include"../../HAL/GPIO/gpio.h"
typedef struct{
    ST_PORT_PIN DB4;
    ST_PORT_PIN DB5;
    ST_PORT_PIN DB6;
    ST_PORT_PIN DB7;
    ST_PORT_PIN RS;
    ST_PORT_PIN EN;
}ST_LCD;

void LCD_init(ST_LCD lcd);

void LCD_Start(ST_LCD lcd);

void LCD_WriteCommand(ST_LCD lcd, uint8_t data);

void LCD_WriteChar(ST_LCD lcd, uint16_t data);

void LCD_WriteStr(ST_LCD lcd, char* p);

void LCD_SetCursor(ST_LCD lcd, uint8_t row, uint8_t col);

void LCD_clear(ST_LCD lcd);

void LCD_PrintNumber(ST_LCD lcd,uint32_t num);
#endif