#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "prototypes.h"
#include "music.h"

void timer_cleanup() {
    stopTimer();
    i = 0;
    c = 0;
    note_c = 0;
}

void __attribute__ ((interrupt)) TIMER1_IRQHandler() {  
    /* Clear interrupt flag */
    *TIMER1_IFC = 1;

    if ( c >= current_note_length ) {
	c = 0;
	note_c++;
    } else {
	c++;
    }

    if ( note_c >= current_song->length ) {
	timer_cleanup();
	*GPIO_PA_DOUT = 0xFFFF;
	disableDAC();
	disableTimer();
	setupSleep(0b110);
	return;
    }

    Note* n = current_song->notes[note_c];
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
    timer_cleanup();
    if (*GPIO_PC_DIN == 0xFE) {
	setSong(&JUMP, 0x027F);
    } else if ( *GPIO_PC_DIN == 0xFB) {
	setSong(&PEWPEW, 0x3FF);
    } else if ( *GPIO_PC_DIN == 0xEF) {
	setSong(&CANON, 0x1FFF);
    } else {
	setSong(&THATSNOMOON, 0x3FFF);
    }
    GPIO_Handler();
}

void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() {
    timer_cleanup();
    if (*GPIO_PC_DIN == 0xFD) {
	setSong(&ONEUP, 0x71f);
    } else {
	setSong(&SCOM, 0x24FF);
    }
    GPIO_Handler();
}
