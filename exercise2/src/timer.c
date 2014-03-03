#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/* The period between sound samples, in clock cycles */
#define   SAMPLE_PERIOD 317

/* function to setup the timer */
void setupTimer() {
    *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_TIMER1;
    *TIMER1_TOP = SAMPLE_PERIOD;
    *TIMER1_IEN = 1;
}

void disableTimer() {
    *CMU_HFPERCLKEN0 &= ~CMU2_HFPERCLKEN0_TIMER1;
    *TIMER1_IEN = 0;
}

void startTimer() {
    *TIMER1_CMD = 1;
}

void stopTimer() {
    *TIMER1_CMD = 0;
}
