#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "notes.h"

static uint32_t i = 0;
static Note* c_maj = { &C, &D, &E, &F, &G, &A, &B1, &C1 };

void note(Note* n) {
    int offset = (i  % n->num);
    *DAC0_CH0DATA = n->samples[offset];
}


/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() {  
    /* Clear interrupt flag */
    *TIMER1_IFC = 1;
    /* Do some magic yo */
    
    note(&c_maj[(i/0xFFF) % 8]);

    //*DAC0_CH0DATA = sin[(n*i) % E_note.num];
    i++;// = (i+1) % G->num;
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
