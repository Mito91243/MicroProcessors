#include "stopwatch.h"

void Sec_timer(uint16_t x) {
    // 1. Enable TIM2 clock (Assuming TIM2 is on APB1)
    RCC->RCC_APB1ENR |= (1 << 0); 
    /* 
        RCC_APB1ENR TIM2EN bit is typically bit 0.
        This enables the clock for TIM2.
    */

    // 2. Reset the status register to clear any pending flags
    TIM2->TIM_SR &= ~(1 << 0); 
    /* 
        Clear UIF (Update Interrupt Flag) by writing 0 to bit 0.
    */

    // 3. Configure the prescaler
    TIM2->TIM_PSC = 7199; 
    /* 
        Prescaler = 7199
        Timer Clock = 72 MHz / (Prescaler + 1) = 72 MHz / 7200 = 10 kHz
    */

    // 4. Set the auto-reload value
    TIM2->TIM_ARR = x; 
    /* 
        Auto-Reload Register (ARR) = x
        Timer period = ARR / Timer Clock = x / 10,000
        For a 1-second delay, set x = 10,000
    */

    // 5. Configure TIM_CR1 register
    TIM2->TIM_CR1 |= (1 << 7) | (1 << 0); 
    /* 
        Set ARPE (Auto-Reload Preload Enable) by setting bit 7.
        Set CEN (Counter Enable) by setting bit 0 to start the timer.
    */

    // 6. Wait until the update event flag (UIF) is set
    while ((TIM2->TIM_SR & (1 << 0)) == 0) {
        // Optionally, implement a timeout mechanism here to prevent an infinite loop
    }
    /* 
        The while loop blocks execution until UIF (bit 0) is set, indicating that the timer has reached the ARR value.
    */

    // 7. Clear the UIF flag to acknowledge the update event
    TIM2->TIM_SR &= ~(1 << 0); 
    /* 
        Clear UIF by writing 0 to bit 0 to prepare for the next timer operation.
    */

    // 8. Disable the timer to stop counting
    TIM2->TIM_CR1 &= ~(1 << 0); 
    /* 
        Clear CEN (bit 0) to disable the timer.
    */
}