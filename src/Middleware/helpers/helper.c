#include "helper.h"

void PWM(int x)
{
    RCC->RCC_APB2ENR |= 0xFC;
    RCC->RCC_APB1ENR |= (1 << 1);

    PORTA->GPIO_CRL = 0x4B444444;
    TIM3->TIM_CCER = 0x1 << 0; /* CC1P = 0, CC1E = 1 */
    TIM3->TIM_CCMR1 = 0x0068;
    TIM3->TIM_CR1 = 0x80;
    TIM3->TIM_PSC = 200 - 1;
    TIM3->TIM_ARR = 1000 - 1; /* ARR = 999 */
    TIM3->TIM_CCR1 = x;       /* duty cycle = (300/1000) *100 */
    TIM3->TIM_EGR = 1;        /* UG = 1 (generate update) */
    TIM3->TIM_CR1 |= 0x01;    /* timer enable (CEN = 1) */
}

// Function to convert uint16_t to string
void uint16ToStr(uint16_t num, char *str)
{
    int i = 0;
    char temp;

    // Extract digits from the number
    do
    {
        str[i++] = (num % 10) + '0'; // Convert the last digit to char and store
        num /= 10;                   // Remove the last digit
    } while (num > 0);

    str[i] = '\0'; // Null-terminate the string

    // Reverse the string as digits are stored in reverse order
    for (int j = 0; j < i / 2; j++)
    {
        temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}

void floatToStr(float num, char *str, int precision)
{
    int intPart = (int)num;         // Get the integer part
    float fracPart = num - intPart; // Get the fractional part

    // Convert integer part to string
    uint16ToStr(intPart, str);

    // Move the pointer to the end of the integer part
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }

    // Add decimal point
    str[i++] = '.';

    // Convert fractional part to string
    for (int j = 0; j < precision; j++)
    {
        fracPart *= 10;
        int fracDigit = (int)fracPart;
        str[i++] = fracDigit + '0';
        fracPart -= fracDigit;
    }

    // Null-terminate the string
    str[i] = '\0';
}