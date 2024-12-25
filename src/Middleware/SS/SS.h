#ifndef _SS_H_
#define _SS_H_
#include "../../HAL/GPIO/gpio.h"

typedef struct 
{
    ST_PORT_PIN DOT;
    ST_PORT_PIN A;
    ST_PORT_PIN B; 
    ST_PORT_PIN C;
    ST_PORT_PIN D;
    ST_PORT_PIN E;
    ST_PORT_PIN F;
    ST_PORT_PIN G;
    ST_PORT_PIN COM;
    uint8_t value;
} ST_SS_letters;

typedef struct 
{
    ST_SS_letters Seg1;
    ST_SS_letters Seg2;
    ST_SS_letters Seg3;
    uint16_t totalvalue;
    uint8_t not_hundredth;
    uint8_t digitpos;
} ST_SS_MUX;

ST_SS_letters InitSevenSegmment(ST_SS_letters seg, ST_PORT_PIN x);
void Disp_Num(uint16_t number);
void Disp_Float(float32_t number);
void Disp_SS(ST_SS_letters seg, uint16_t number);
void InitMux(void);
void Data_Show(void); 
void Delay_ms(uint32_t ms); 

#endif