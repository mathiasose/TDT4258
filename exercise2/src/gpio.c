#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/* function to set up GPIO mode and interrupts*/
void setupGPIO() {
    *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO; /* enable GPIO clock*/
    *GPIO_PA_CTRL = 2;  /* set high drive strength */
    *GPIO_PA_MODEH = 0x55555555; /* set pins A8-15 as output */
    *GPIO_PC_MODEL = 0x33333333; /* Set pins C0-7 as input */
    *GPIO_PC_DOUT = 0xFF; /* Enable internal pull-up*/
    *GPIO_EXTIPSELL = 0x22222222;
    *GPIO_EXTIFALL = 0xFF; /* Interrupt on falling edge */
    //*GPIO_EXTIRISE = 0xFF; /* Interrupt on rising edge */
    *GPIO_IEN = 0x00FF;
    *GPIO_IFC = 0xFF;
    *GPIO_PA_DOUT = 0xFF00;
}

void GPIO_interrupt_clear() { 
    *GPIO_IFC = *GPIO_IF;
}

void GPIO_LED() {
    *GPIO_PA_DOUT = *GPIO_PC_DIN << 8;
}

/*
   Maps input to corresponding SWn button
   Will return 0 if no button is pressed, or multiple buttons are pressed
 */
int map_input() {
    int input = ~(*GPIO_PC_DIN);
    for ( int i = 0; i < 8; i++) {
	int match = input & (1 << i);
	if ( (1 << i) == match ) {
	    return (i+1);
	}
    }
    return 0;
}

