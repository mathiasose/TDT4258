#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "prototypes.h"
#include "music.h"

static uint32_t i = 0;
static uint16_t note_c = 0;
static uint16_t c = 0;

void note0(Note* n) {
    int offset = (i  % n->num);
    *DAC0_CH0DATA = n->samples[offset];
}

void note1(Note* n) {
    int offset = (i  % n->num);
    *DAC0_CH1DATA = n->samples[offset];
}


/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() {  
    /* Clear interrupt flag */
    *TIMER1_IFC = 1;

    if ( c >= 0x1FFF ) {
	c = 0;
	note_c++;
    } else {
	c++;
    }
    if ( note_c >= SCOM_LEN ) {
	stopTimer();
	i = 0;
	c = 0;
	note_c = 0;

	disableDAC();
	disableTimer();
	setupSleep(0b110);
	return;
    }

    note0(SCOM[note_c]);
    note1(SCOM[note_c]);

    i++;
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() {
    *GPIO_IFC = *GPIO_IF;

    *GPIO_PA_DOUT = *GPIO_PC_DIN << 8;
    
    setupSleep(0b010);
    setupDAC();
    setupTimer();
    startTimer();
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() {
    *GPIO_IFC = *GPIO_IF;
    
    //*GPIO_PA_DOUT = *GPIO_PC_DIN << 8;
}
