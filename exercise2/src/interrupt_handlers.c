#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() {  
    /* Clear interrupt flag */
    *TIMER1_IFC = 1;
    /* Do some magic yo */
    *GPIO_PA_DOUT = 0xAAAA;
    *GPIO_PA_DOUT = 0xAAAA;
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() {
    /* TODO handle button pressed event, remember to clear pending interrupt */
    *GPIO_IFC = *GPIO_IF;
    /* Do the magic */
    //*TIMER1_CMD = 1;
    //*GPIO_PA_DOUT = *GPIO_PC_DIN << 8;
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() {
    /* TODO handle button pressed event, remember to clear pending interrupt */
    *GPIO_IFC = *GPIO_IF;
    /* Magic repeated */
    //*TIMER1_CMD = 1;
    //*GPIO_PA_DOUT = *GPIO_PC_DIN << 8;
}
