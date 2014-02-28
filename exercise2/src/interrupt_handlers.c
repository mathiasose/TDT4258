#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "notes.h"

static uint32_t i = 0;
static uint8_t SONG_LENGTH = 22;
static Note *c_maj[] = {
    &C, &D, &E, &F,
    &G, &G, &A, &A,
    &A, &A, &G, &F,
    &F, &F, &F, &E,
    &E, &D, &D, &D,
    &D, &C
};
static uint16_t hold[] = {
    0x7FFF, 0x7FFF, 0x7FFF, 0x7FFF,
    0xFFFF, 0xFFFF, 0x3FFF, 0x3FFF,
    0x3FFF, 0x3FFF, 0xFFFF, 0x3FFF,
    0x3FFF, 0x3FFF, 0x3FFF, 0x7FFF,
    0x7FFF, 0x3FFF, 0x3FFF, 0x3FFF,
    0x3FFF, 0xFFFF
};
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
    /* Do some magic yo */

    //note(&c_maj[(i/0xCFFF) % 8]);
    /*if (c == 0) {
      note_c = ( note_c + 1 ) % 8;
      hold_c = ( hold_c + 1 ) % 3;
      c = hold[hold_c];
      } else {
      c--;
      }*/

    if ( c == hold[note_c] ) {
	c = 0;
	note_c = (note_c + 1) % SONG_LENGTH;
    } else {
	c++;
    }

    note0(c_maj[note_c]);
    //note0(&(c_maj[note_c]));
    //*DAC0_CH0DATA = sin[(n*i) % E_note.num];
    i++;// = (i+1) % G->num;
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() {
    /* TODO handle button pressed event, remember to clear pending interrupt */
    *GPIO_IFC = *GPIO_IF;
    /* Do the magic */
    //*TIMER1_CMD = 1;
    //*GPIO_PA_DOUT = (!note_c) << 8; //*GPIO_PC_DIN << 8;
    //note_c = (note_c - 1) % 8;
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() {
    /* TODO handle button pressed event, remember to clear pending interrupt */
    *GPIO_IFC = *GPIO_IF;
    /* Magic repeated */
    //*TIMER1_CMD = 1;
    //*GPIO_PA_DOUT = (!note_c) << 8; //*GPIO_PC_DIN << 8;
    //note_c = (note_c + 1) % 8;
}
