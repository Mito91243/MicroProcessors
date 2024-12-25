#ifndef __REGISTER_H__
#define __REGISTER_H__
#include "register_map.h"
#include "../Common/bitop.h"

typedef struct
{
    __IO uint32_t GPIO_CRL;
    __IO uint32_t GPIO_CRH;
    __IO uint32_t GPIO_IDR;
    __IO uint32_t GPIO_ODR;
    __IO uint32_t GPIO_BSRR;
    __IO uint32_t GPIO_BRR;
    __IO uint32_t GPIO_LCKR;
} GPIO_Typedef;

typedef struct
{
    __IO uint32_t RCC_CR;
    __IO uint32_t RCC_CFGR;
    __IO uint32_t RCC_CIR;
    __IO uint32_t RCC_APB2RSTR;
    __IO uint32_t RCC_APB1RSTR;
    __IO uint32_t RCC_AHBENR;
    __IO uint32_t RCC_APB2ENR;
    __IO uint32_t RCC_APB1ENR;
    __IO uint32_t RCC_BDCR;
    __IO uint32_t RCC_CSR;
    __IO uint32_t RCC_AHBSTR;
    __IO uint32_t RCC_CFGR2;
} RCC_Typedef;

typedef struct
{
    __IO uint32_t STK_CTRL;
    __IO uint32_t STK_LOAD;
    __IO uint32_t STK_VAL;
    __IO uint32_t STK_CALIB;
} Systick_Typedef;

typedef struct
{
    __IO uint32_t TIM_CR1;
    __IO uint32_t TIM_CR2;
    __IO uint32_t TIM_SMCR;
    __IO uint32_t TIM_DIER;
    __IO uint32_t TIM_SR;
    __IO uint32_t TIM_EGR;
    __IO uint32_t TIM_CCMR1;
    __IO uint32_t TIM_CCMR2;
    __IO uint32_t TIM_CCER;
    __IO uint32_t TIM_CNT;
    __IO uint32_t TIM_PSC;
    __IO uint32_t TIM_ARR;
    __IO uint32_t R1;
    __IO uint32_t TIM_CCR1;
    __IO uint32_t TIM_CCR2;
    __IO uint32_t TIM_CCR3;
    __IO uint32_t TIM_CCR4;
    __IO uint32_t R2;
    __IO uint32_t TIM_DCR;
    __IO uint32_t TIM_DMAR;
} TIM_Typedef;

typedef struct
{
    __IO uint32_t ADC_SR;
    __IO uint32_t ADC_CR1;
    __IO uint32_t ADC_CR2;
    __IO uint32_t ADC_SMPR1;
    __IO uint32_t ADC_SMPR2;
    __IO uint32_t ADC_JOFR1;
    __IO uint32_t ADC_JOFR2;
    __IO uint32_t ADC_JOFR3;
    __IO uint32_t ADC_JOFR4;
    __IO uint32_t ADC_HTR;
    __IO uint32_t ADC_LTR;
    __IO uint32_t ADC_SQR1;
    __IO uint32_t ADC_SQR2;
    __IO uint32_t ADC_SQR3;
    __IO uint32_t ADC_JSQR;
    __IO uint32_t ADC_JDR1;
    __IO uint32_t ADC_JDR2;
    __IO uint32_t ADC_JDR3;
    __IO uint32_t ADC_JDR4;
    __IO uint32_t ADC_DR;
} ADC_Typedef;

typedef struct
{
    __IO uint32_t SR;   // Status register
    __IO uint32_t DR;   // Data register
    __IO uint32_t BRR;  // Baud rate register
    __IO uint32_t CR1;  // Control register 1
    __IO uint32_t CR2;  // Control register 2
    __IO uint32_t CR3;  // Control register 3
    __IO uint32_t GTPR; // Guard time and prescaler
} USART_Typedef;

#define PORTA ((GPIO_Typedef *)GPIO_A_BASE)
#define PORTB ((GPIO_Typedef *)GPIO_B_BASE)
#define PORTC ((GPIO_Typedef *)GPIO_C_BASE)
#define PORTD ((GPIO_Typedef *)GPIO_D_BASE)

#define TIM2 ((TIM_Typedef *)TIM2_BASE)
#define TIM3 ((TIM_Typedef *)TIM3_BASE)
#define TIM4 ((TIM_Typedef *)TIM4_BASE)
#define TIM5 ((TIM_Typedef *)TIM5_BASE)

#define RCC ((RCC_Typedef *)RCC_BASE)
#define SYSTICK ((Systick_Typedef *)SYSTICK_BASE)
#define ADC1 ((ADC_Typedef *)ADC1_BASE)

#define USART1 ((USART_Typedef *)USART1_BASE)

#endif
