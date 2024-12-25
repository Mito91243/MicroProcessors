#include "USART.h"

void usart1_sendByte(unsigned char c)
{
    // Wait until TXE flag is set (bit 7)
    while (!(USART1->SR & (1 << 7)))
        ;
    // Send the byte
    USART1->DR = c;
}

uint8_t usart1_recByte(void)
{
    // Wait until RXNE flag is set (bit 5)
    while (!(USART1->SR & (1 << 5)))
        ;
    // Read and return the received data
    return (uint8_t)(USART1->DR);
}

void usart1_init(void)
{
    // Enable clock for GPIOA (IOPAEN, bit 2) and USART1 (USART1EN, bit 14)
    RCC->RCC_APB2ENR |= (1 << 2) | (1 << 14);

    // Configure PA9 (TX) as Alternate Function Push-Pull
    PORTA->GPIO_CRH &= ~(0xF << 4); // Clear bits for PA9
    PORTA->GPIO_CRH |= (0xB << 4);  // Set PA9 to AF Push-Pull

    // Configure PA10 (RX) as Input with Pull-Up
    PORTA->GPIO_CRH &= ~(0xF << 8); // Clear bits for PA10
    PORTA->GPIO_CRH |= (0x8 << 8);  // Set PA10 as Input with Pull-Up

    // Enable Pull-Up for PA10
    PORTA->GPIO_ODR |= (1 << 10);

    // Configure USART1 Control Register 1 (CR1)
    USART1->CR1 = 0x200C; // UE=1, TE=1, RE=1

    // Configure Baud Rate Register
    USART1->BRR = 7500; // 72MHz / 9600bps = 7500
}
