#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
static uint16_t i = 0;

void tone(int n) {
    int x = 1;
    int i = 0;
    while(i++ < 6000){
        if (x*2 >= 0xFFF) {
            x = 1;
        } else {
            x *= 2;
        }
        *DAC0_CH0DATA = x;
    }
}

/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() {  
    /* Clear interrupt flag */
    *TIMER1_IFC = 1;
    *GPIO_PA_DOUT = 0xFF00;
    /* Do some magic yo */
    *DAC0_CH0DATA = i & 0xFFF;
    i++;
    
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() {
    /* TODO handle button pressed event, remember to clear pending interrupt */
    *GPIO_IFC = *GPIO_IF;
    /* Do the magic */
    //*TIMER1_CMD = 1;
    *GPIO_PA_DOUT = *GPIO_PC_DIN << 8;
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() {
    /* TODO handle button pressed event, remember to clear pending interrupt */
    *GPIO_IFC = *GPIO_IF;
    /* Magic repeated */
    //*TIMER1_CMD = 1;
    *GPIO_PA_DOUT = *GPIO_PC_DIN << 8;
}
