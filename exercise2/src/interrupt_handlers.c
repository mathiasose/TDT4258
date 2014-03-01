#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "music.h"

static uint32_t i = 0;
static uint16_t note_c = 0;
static uint16_t c = 0;

void note0(Note* n) {
    int offset = (i  % n->num);
    *DAC0_CH0DATA = n->samples[offset];
}


/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() {  
    /* Clear interrupt flag */
    *TIMER1_IFC = 1;

    if ( c >= 0x3FFF ) {
	c = 0;
	note_c = (note_c + 1) % SCOM_LEN;
    } else {
	c++;
    }
    note0(SCOM[note_c]);

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
