#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "prototypes.h"

int main(void) {  
    setupSleep(0b110);
    setupGPIO();
    setupNVIC();

    wfi();
    return 0;
}

void setupNVIC() {
    *ISER0 = 0x1802;
}

void setupSleep(int arg) {
    *SCR = arg;
}
