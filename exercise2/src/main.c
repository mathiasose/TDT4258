#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "prototypes.h"

int main(void) {  
    setupGPIO();
    setupNVIC();
 
    setupSleep(0b110);
    wfi();
    return 0;
}

void setupNVIC() {
    *ISER0 = 0x1802;
}

void setupSleep(int arg) {
    *SCR = arg;
}
