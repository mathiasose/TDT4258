#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "prototypes.h"
#include "music.h"

int main(void) {  
    setupSleep(0b110);
    setupGPIO();
    setupNVIC();

//    playSong(&SCOM, 0x24FF); 

//    wfi();
    return 0;
}

void setupNVIC() {
    *ISER0 = 0x1802;
}

void setupSleep(int arg) {
    *SCR = arg;
}
