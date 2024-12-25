#include <HAL/GPIO/gpio.h>
void delay_us(uint16_t t) { for(int i = 0; i < t; i++) { for(volatile uint16_t a = 0; a < 6; a++) {} } }
uint16_t LOOP_ADC(void) {
    ADC1->ADC_CR1 = (1<<5); 
    ADC1->ADC_SQR3 = 1; /* choose channel 1 as the input */ 
    ADC1->ADC_CR2 |= 1<<1; /* CONT = 1 (Convert continuously) */ 
    ADC1->ADC_CR2 |= 1<<0; /* ADCON = 1 (start conversion) */
    delay_us(5);

    while((ADC1->ADC_SR&(1<<1)) == 0); /* wait until the EOC flag is set */
}

uint16_t INIT_ADC_INTPUT(void)
{
    RCC->RCC_APB2ENR |= 0xFC|(1<<9)|(1<<14); /* enable clocks for GPIO, ADC1 and usart1 */ 
    PORTA->GPIO_CRL = 0x44444440; /* PA1(ADC_IN1) as analog input */ 
    ADC1->ADC_CR2 = 1; /* ADON = 1 (power-up) */ 
    ADC1->ADC_SMPR2 = 1<<3; /* SMP1 = 001 (set sample time for IN1 to 7.5 clock cycles) */
    delay_us(5);
}  