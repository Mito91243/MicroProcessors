#include "SS.h"

ST_SS_MUX Mux;


void InitMux()
{
    ST_SS_letters SevenSeg = {{EN_PORTA, 15}, {EN_PORTA, 11}, {EN_PORTA, 8}, {EN_PORTB, 15}, {EN_PORTB, 14}, {EN_PORTB, 13}, {EN_PORTB, 12}, {EN_PORTA, 12}, {EN_PORTA, 15}, 0};
    ST_PORT_PIN Seg1 = {EN_PORTB, 8};
    ST_PORT_PIN Seg2 = {EN_PORTB, 9};
    ST_PORT_PIN Seg3 = {EN_PORTB, 3};
    ST_SS_letters x = InitSevenSegmment(SevenSeg, Seg1);
    ST_SS_letters y = InitSevenSegmment(SevenSeg, Seg2);
    ST_SS_letters z = InitSevenSegmment(SevenSeg, Seg3);
    ST_SS_MUX tempmux = {x, y, z, 0, 0, 0};
    Mux = tempmux;
}

ST_SS_letters InitSevenSegmment(ST_SS_letters seg, ST_PORT_PIN COM)
{
    seg.COM = COM;
    CONF_GPIO(seg.COM, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(seg.DOT, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(seg.A, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(seg.B, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(seg.C, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(seg.D, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(seg.E, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(seg.F, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    CONF_GPIO(seg.G, (ST_PORT_PIN_CONF){OUTPUT, GEN_OUT_PUSH, OUT_SPEED_10MHZ});
    return seg;
}

void Disp_Num(uint16_t number)
{
    Mux.totalvalue = number;
    while (1)
    {
        Data_Show(); // Call the timer ISR to update the display
        Delay_ms(5); // Add a delay to control the refresh rate
    }
}

void Data_Show()
{
    static uint8_t current_seg = 0;
    uint8_t not_hundredth = 0;
    uint16_t number = Mux.totalvalue;
    uint16_t digit1 = number / 100;       // Hundreds place
    uint16_t digit2 = (number / 10) % 10; // Tens place
    uint16_t digit3 = number % 10;        // Units place

    if (digit1 == 0)
    {
        not_hundredth = 1;
    }

    // Turn off all segments and DOTs
    GPIO_OUTPUT_LEVEL(Mux.Seg1.COM, LOW);
    GPIO_OUTPUT_LEVEL(Mux.Seg2.COM, LOW);
    GPIO_OUTPUT_LEVEL(Mux.Seg3.COM, LOW);
    GPIO_OUTPUT_LEVEL(Mux.Seg1.DOT, LOW);
    GPIO_OUTPUT_LEVEL(Mux.Seg2.DOT, LOW);
    GPIO_OUTPUT_LEVEL(Mux.Seg3.DOT, LOW);

    // Display the current digit
    switch (current_seg)
    {
    case 0:
        GPIO_OUTPUT_LEVEL(Mux.Seg1.COM, HIGH);
        if (not_hundredth == 1)
        {
            Disp_SS(Mux.Seg1, digit2);
            if (Mux.digitpos == 1)
                GPIO_OUTPUT_LEVEL(Mux.Seg1.DOT, HIGH);
            break;
        }
        Disp_SS(Mux.Seg1, digit1);
        if (Mux.digitpos == 1)
            GPIO_OUTPUT_LEVEL(Mux.Seg1.DOT, HIGH);
        break;

    case 1:
        GPIO_OUTPUT_LEVEL(Mux.Seg2.COM, HIGH);
        if (not_hundredth == 1)
        {
            Disp_SS(Mux.Seg2, digit3);
            if (Mux.digitpos == 2)
                GPIO_OUTPUT_LEVEL(Mux.Seg2.DOT, HIGH);
            break;
        }
        Disp_SS(Mux.Seg2, digit2);
        if (Mux.digitpos == 2)
            GPIO_OUTPUT_LEVEL(Mux.Seg2.DOT, HIGH);
        break;

    case 2:
        GPIO_OUTPUT_LEVEL(Mux.Seg3.COM, HIGH);
        if (not_hundredth == 1)
        {
            break;
        }
        Disp_SS(Mux.Seg3, digit3);
        if (Mux.digitpos == 3)
            GPIO_OUTPUT_LEVEL(Mux.Seg3.DOT, HIGH);
        break;
    }

    current_seg = (current_seg + 1) % 3;
}


void Disp_Float(float32_t number)
{
    GPIO_OUTPUT_LEVEL(Mux.Seg1.DOT, LOW);
    GPIO_OUTPUT_LEVEL(Mux.Seg2.DOT, LOW);
    GPIO_OUTPUT_LEVEL(Mux.Seg3.DOT, LOW);

    if (number < 10.0)
    {
        Mux.digitpos = 1; 
        uint16_t intvalue = (uint16_t)(number * 100);
        Disp_Num(intvalue);
    }
    else if (number >= 10.0 && number < 100.0)
    {
        Mux.digitpos = 2;
        uint16_t intvalue = (uint16_t)(number * 10);
        Disp_Num(intvalue);
    }
}

void Delay_ms(uint32_t ms)
{

    for (uint32_t i = 0; i < ms * 1000; i++)
    {
        __asm("nop");
    }
}


void Disp_SS(ST_SS_letters seg, uint16_t number)
{
    // Function to set the segments High or Low based on the input number
    // Assume HIGH and LOW are defined appropriately
    switch (number)
    {
    case 0:
        // Segments A, B, C, D, E, F are HIGH; G is LOW
        GPIO_OUTPUT_LEVEL(seg.A, HIGH);
        GPIO_OUTPUT_LEVEL(seg.B, HIGH);
        GPIO_OUTPUT_LEVEL(seg.C, HIGH);
        GPIO_OUTPUT_LEVEL(seg.D, HIGH);
        GPIO_OUTPUT_LEVEL(seg.E, HIGH);
        GPIO_OUTPUT_LEVEL(seg.F, HIGH);
        GPIO_OUTPUT_LEVEL(seg.G, LOW);
        break;
    case 1:
        // Segments B, C are HIGH; others are LOW
        GPIO_OUTPUT_LEVEL(seg.A, LOW);
        GPIO_OUTPUT_LEVEL(seg.B, HIGH);
        GPIO_OUTPUT_LEVEL(seg.C, HIGH);
        GPIO_OUTPUT_LEVEL(seg.D, LOW);
        GPIO_OUTPUT_LEVEL(seg.E, LOW);
        GPIO_OUTPUT_LEVEL(seg.F, LOW);
        GPIO_OUTPUT_LEVEL(seg.G, LOW);
        break;
    case 2:
        // Segments A, B, D, E, G are HIGH; C, F are LOW
        GPIO_OUTPUT_LEVEL(seg.A, HIGH);
        GPIO_OUTPUT_LEVEL(seg.B, HIGH);
        GPIO_OUTPUT_LEVEL(seg.C, LOW);
        GPIO_OUTPUT_LEVEL(seg.D, HIGH);
        GPIO_OUTPUT_LEVEL(seg.E, HIGH);
        GPIO_OUTPUT_LEVEL(seg.F, LOW);
        GPIO_OUTPUT_LEVEL(seg.G, HIGH);
        break;
    case 3:
        // Segments A, B, C, D, G are HIGH; E, F are LOW
        GPIO_OUTPUT_LEVEL(seg.A, HIGH);
        GPIO_OUTPUT_LEVEL(seg.B, HIGH);
        GPIO_OUTPUT_LEVEL(seg.C, HIGH);
        GPIO_OUTPUT_LEVEL(seg.D, HIGH);
        GPIO_OUTPUT_LEVEL(seg.E, LOW);
        GPIO_OUTPUT_LEVEL(seg.F, LOW);
        GPIO_OUTPUT_LEVEL(seg.G, HIGH);
        break;
    case 4:
        // Segments B, C, F, G are HIGH; A, D, E are LOW
        GPIO_OUTPUT_LEVEL(seg.A, LOW);
        GPIO_OUTPUT_LEVEL(seg.B, HIGH);
        GPIO_OUTPUT_LEVEL(seg.C, HIGH);
        GPIO_OUTPUT_LEVEL(seg.D, LOW);
        GPIO_OUTPUT_LEVEL(seg.E, LOW);
        GPIO_OUTPUT_LEVEL(seg.F, HIGH);
        GPIO_OUTPUT_LEVEL(seg.G, HIGH);
        break;
    case 5:
        // Segments A, C, D, F, G are HIGH; B, E are LOW
        GPIO_OUTPUT_LEVEL(seg.A, HIGH);
        GPIO_OUTPUT_LEVEL(seg.B, LOW);
        GPIO_OUTPUT_LEVEL(seg.C, HIGH);
        GPIO_OUTPUT_LEVEL(seg.D, HIGH);
        GPIO_OUTPUT_LEVEL(seg.E, LOW);
        GPIO_OUTPUT_LEVEL(seg.F, HIGH);
        GPIO_OUTPUT_LEVEL(seg.G, HIGH);
        break;
    case 6:
        // Segments A, C, D, E, F, G are HIGH; B is LOW
        GPIO_OUTPUT_LEVEL(seg.A, HIGH);
        GPIO_OUTPUT_LEVEL(seg.B, LOW);
        GPIO_OUTPUT_LEVEL(seg.C, HIGH);
        GPIO_OUTPUT_LEVEL(seg.D, HIGH);
        GPIO_OUTPUT_LEVEL(seg.E, HIGH);
        GPIO_OUTPUT_LEVEL(seg.F, HIGH);
        GPIO_OUTPUT_LEVEL(seg.G, HIGH);
        break;
    case 7:
        // Segments A, B, C are HIGH; D, E, F, G are LOW
        GPIO_OUTPUT_LEVEL(seg.A, HIGH);
        GPIO_OUTPUT_LEVEL(seg.B, HIGH);
        GPIO_OUTPUT_LEVEL(seg.C, HIGH);
        GPIO_OUTPUT_LEVEL(seg.D, LOW);
        GPIO_OUTPUT_LEVEL(seg.E, LOW);
        GPIO_OUTPUT_LEVEL(seg.F, LOW);
        GPIO_OUTPUT_LEVEL(seg.G, LOW);
        break;
    case 8:
        // All segments are HIGH
        GPIO_OUTPUT_LEVEL(seg.A, HIGH);
        GPIO_OUTPUT_LEVEL(seg.B, HIGH);
        GPIO_OUTPUT_LEVEL(seg.C, HIGH);
        GPIO_OUTPUT_LEVEL(seg.D, HIGH);
        GPIO_OUTPUT_LEVEL(seg.E, HIGH);
        GPIO_OUTPUT_LEVEL(seg.F, HIGH);
        GPIO_OUTPUT_LEVEL(seg.G, HIGH);
        break;
    case 9:
        // Segments A, B, C, D, F, G are HIGH; E is LOW
        GPIO_OUTPUT_LEVEL(seg.A, HIGH);
        GPIO_OUTPUT_LEVEL(seg.B, HIGH);
        GPIO_OUTPUT_LEVEL(seg.C, HIGH);
        GPIO_OUTPUT_LEVEL(seg.D, HIGH);
        GPIO_OUTPUT_LEVEL(seg.E, LOW);
        GPIO_OUTPUT_LEVEL(seg.F, HIGH);
        GPIO_OUTPUT_LEVEL(seg.G, HIGH);
        break;
    default:
        // Turn off all segments
        GPIO_OUTPUT_LEVEL(seg.A, LOW);
        GPIO_OUTPUT_LEVEL(seg.B, LOW);
        GPIO_OUTPUT_LEVEL(seg.C, LOW);
        GPIO_OUTPUT_LEVEL(seg.D, LOW);
        GPIO_OUTPUT_LEVEL(seg.E, LOW);
        GPIO_OUTPUT_LEVEL(seg.F, LOW);
        GPIO_OUTPUT_LEVEL(seg.G, LOW);
        break;
    }
    seg.value = number;
}