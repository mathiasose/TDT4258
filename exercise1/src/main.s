.syntax unified
.include "lib/efm32gg.s"
.include "lib/vector.s"

.section .text
/////////////////////////////////////////////////////////////////////////////
//
// Reset handler
// The CPU will start executing here after a reset
//
/////////////////////////////////////////////////////////////////////////////
.globl  _reset
.type   _reset, %function
.thumb_func
_reset:
    // aliases
    W .req R3
    GPIO_O .req R4
    GPIO_I .req R5
    GPIO .req R6
    T0 .req R7
    T1 .req R8
    T2 .req R9
    // do not change these registers
    LDR R4, =GPIO_PA_BASE
    LDR R5, =GPIO_PC_BASE
    LDR R6, =GPIO_BASE
    // Enable clock for GPIO
    LDR T2, =CMU_BASE
    LDR T0, [T2, #CMU_HFPERCLKEN0]
    MOV T1, #1
    LSL T1, T1, #CMU_HFPERCLKEN0_GPIO
    ORR T0, T0, T1
    STR T0, [T2, #CMU_HFPERCLKEN0]
    // Set high drive strength
    MOV T0, #0b10
    STR T0, [GPIO_O, #GPIO_CTRL]
    // Set pins 8-15 of port A for output
    LDR T0, =0x55555555
    // Do a fun little LED test then set all LEDs off
    STR T0, [GPIO_O, #GPIO_MODEH]
    BL led_test
    LDR T0, =0xFF00
    STR T0, [GPIO_O, #GPIO_DOUT]
    // Set pins 0-7 of port C for input
    LDR T0, =0x33333333
    STR T0, [GPIO_I, #GPIO_MODEL]
    LDR T0, =0xFF
    STR T0, [GPIO_I, #GPIO_DOUT]
    // EXTIP
    LDR T0, =0x22222222
    STR T0, [GPIO, #GPIO_EXTIPSELL]
    // Configure RISE/FALL
    LDR T0, =0xFF
    STR T0, [GPIO, #GPIO_EXTIRISE]
    STR T0, [GPIO, #GPIO_EXTIFALL]
    STR T0, [GPIO, #GPIO_IEN]
    LDR T0, [GPIO, #GPIO_IF]
    // Enable NVIC for GPIO
    LDR T0, =0x802
    LDR T1, =ISER0
    STR T0, [T1]
    B main
    

/////////////////////////////////////////////////////////////////////////////
//
// GPIO handler
// The CPU will jump here when there is a GPIO interrupt
//
/////////////////////////////////////////////////////////////////////////////
.thumb_func
gpio_handler:
    //Clear interrupt flag
    LDR T0, [GPIO, #GPIO_IF]
    STR T0, [GPIO, #GPIO_IFC]
    //Perform actual signal processing
    LDR T1, [GPIO_I, #GPIO_DIN]
    MOV T0, #8
    LSL T1, T1, T0 // shift the 8 lsb from input to use as 8 msb for output
    STR T1, [GPIO_O, #GPIO_DOUT]
    BX lr


// Main subroutine
.thumb_func
main:
    // Enable automatic deep sleep after return from interrupt handler
    MOV T0, #0b110
    LDR T1, =SCR
    STR T0, [T1]
    WFI


// Helper sleepfunction
.thumb_func
wait:
    LDR W, =0x30000
wait_loop:
    SUBS W, #1
    BNE wait_loop
    BX lr

// Test LEDS
.thumb_func
led_sequence:
    PUSH {LR}
    BL led_loop
led_loop:
    STR T0, [GPIO_O, #GPIO_DOUT]
    BL wait
    ROR T0, T1
    SUBS T2, #1
    BNE led_loop
    POP {PC}

led_blink:
    PUSH {LR}
    STR T0, [GPIO_O, #GPIO_DOUT]
    LDR W, =0xA0000
    BL wait_loop
    STR T1, [GPIO_O, #GPIO_DOUT]
    LDR W, =0xA0000
    BL wait_loop
    // Return function, LEDs are now off
    POP {PC}

.thumb_func
led_test:
    PUSH {LR}
    // Test LEDs sequentially
    LDR T0, =0x7F00 // bit pattern led will display
    MOV T1, #1      // number of bits to rotate right each loop
    MOV T2, #7      // times to loop
    BL led_sequence

    // Blink all LEDs twice
    LDR T0, =0x0000
    LDR T1, =0xFF00
    BL led_blink
    LDR T0, =0x5500
    LDR T1, =0xAA00
    BL led_blink
    POP {PC}


/////////////////////////////////////////////////////////////////////////////
//
// Some dummy handler
//
/////////////////////////////////////////////////////////////////////////////

.thumb_func
dummy_handler:
    BX lr
