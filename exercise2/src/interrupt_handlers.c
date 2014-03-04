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
        current_song = &JUMP;
        current_note_length = 0x027F;
    } else if ( *GPIO_PC_DIN == 0xFB) {
        current_song = &PEWPEW;
        current_note_length = 0x3FF;
    } else {
        current_note_length = 0x3FFF;
        current_song = &THATSNOMOON;
    }
    GPIO_Handler();
}

void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() {
    timer_cleanup();
    current_note_length = 0x7FF;
    current_song = &ENIGMA;
    GPIO_Handler();
}
