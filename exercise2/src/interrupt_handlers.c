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

void playSong(Song* song, uint16_t note_length) {
    setSong(song, note_length);

    setupSleep(0b010);
    setupDAC();
    setupTimer();
    startTimer();
}

void GPIO_Handler() {
    timer_cleanup();
    GPIO_interrupt_clear();
    GPIO_LED();

    int SW = map_input();
    if (SW == 1) {
	playSong(&JUMP, 0x027F);
    } else if ( SW == 2) {
	playSong(&PEWPEW, 0x3FF);
    } else if ( SW == 3) {
	playSong(&ONEUP, 0x71f);
    } else if (SW == 4) {
	playSong(&THATSNOMOON, 0x3FFF);
    } else if (SW == 5) {
	playSong(&SCOM, 0x24FF);
    } else if (SW == 6) {
	playSong(&CANON, 0x17FF);
    } else if (SW == 7) {
	playSong(&CANON, 0x5FFF);
    } else if (SW == 8) {
	playSong(&CANON, 0xFFF);
    }
}

void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() { 
    GPIO_Handler();
}

void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() {
    GPIO_Handler();
}
