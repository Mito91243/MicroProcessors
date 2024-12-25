#ifndef __LIQUIDCRYSTAL_H__
#define __LIQUIDCRYSTAL_H__
#include"../../HAL/GPIO/gpio.h"

typedef struct
{
ST_PORT_PIN D7;
ST_PORT_PIN D6;
ST_PORT_PIN D5;
ST_PORT_PIN D4;   
ST_PORT_PIN Enable;
ST_PORT_PIN RS;

}SST_LCD;

void LCD_Init(SST_LCD lcd);
void LCD_Start(SST_LCD lcd);

void LCD_SetDataPins(SST_LCD lcd, uint8_t data);
void LCD_SendCMD(SST_LCD lcd, uint8_t cmd);

void LCD_ClearDisplay(SST_LCD lcd);
void LCD_SetCursor(SST_LCD lcd, uint8_t x, uint8_t y);

void LCD_PrintChar(SST_LCD lcd, uint16_t c);
void LCD_Printstring(SST_LCD lcd, char* s);

void LCD_PrintNum(SST_LCD lcd, uint16_t temp);










#endif