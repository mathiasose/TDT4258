#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "prototypes.h"
#include "music.h"

void __attribute__ ((interrupt)) TIMER1_IRQHandler() {  
    /* Clear interrupt flag */
    *TIMER1_IFC = 1;

    if ( c >= 0x1FFF ) {
	c = 0;
	note_c++;
    } else {
	c++;
    }

    if ( note_c >= current_song->length ) {
	stopTimer();
	i = 0;
	c = 0;
	note_c = 0;

	disableDAC();
	disableTimer();
	setupSleep(0b110);
	return;
    }

    Note* n = &(current_song->notes[note_c]);
    int offset = (i % n->num);
    note(n, offset);

    i++;
}

void GPIO_Handler() {
    *GPIO_IFC = *GPIO_IF;

    *GPIO_PA_DOUT = *GPIO_PC_DIN << 8;
    
    setupSleep(0b010);
    setupDAC();
    setupTimer();
    startTimer();
}

void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() {
    GPIO_Handler();
}

void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() {
    GPIO_Handler();
}
