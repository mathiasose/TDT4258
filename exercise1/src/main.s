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
    GPIO_O .req R4
    GPIO_I .req R5
    GPIO .req R6
    T1 .req R7
    T2 .req R8
    T3 .req R9
    W .req R10
    // do not change these registers
    LDR R4, =GPIO_PA_BASE
    LDR R5, =GPIO_PC_BASE
    LDR R6, =GPIO_BASE
    // Enable clock for GPIO
    LDR T3, =CMU_BASE
    LDR T1, [T3, #CMU_HFPERCLKEN0]
    MOV T2, #1
    LSL T2, T2, #CMU_HFPERCLKEN0_GPIO
    ORR T1, T1, T2
    STR T1, [T3, #CMU_HFPERCLKEN0]
    // Set high drive strength
    MOV T1, #0x2
    STR T1, [GPIO_O, #GPIO_CTRL]
    // Set pins 8-15 of port A for output
    LDR T1, =0x55555555
    STR T1, [GPIO_O, #GPIO_MODEH]
    BL led_test
    // Set pins 0-7 of port C for input
    LDR T1, =0x33333333
    STR T1, [GPIO_I, #GPIO_MODEL]
    LDR T1, =0xFF
    STR T1, [GPIO_I, #GPIO_DOUT]
    // EXTIP
    LDR T1, =0x22222222
    STR T1, [GPIO, #GPIO_EXTIPSELL]
    // Configure RISE/FALL
    LDR T1, =0xFF
    STR T1, [GPIO, #GPIO_EXTIRISE]
    STR T1, [GPIO, #GPIO_EXTIFALL]
    STR T1, [GPIO, #GPIO_IEN]
    // Enable NVIC for GPIO
    LDR T1, =0x802
    LDR T2, =ISER0
    STR T1, [T2]
    // Enable automatic deep sleep after return from interrupt handler
    MOV T1, #6
    LDR T2, =SCR
    STR T1, [GPIO]
    WFI
    
/////////////////////////////////////////////////////////////////////////////
//
// GPIO handler
// The CPU will jump here when there is a GPIO interrupt
//
/////////////////////////////////////////////////////////////////////////////
.thumb_func
gpio_handler:
    //Clear interrupt flag
    LDR T1, =0xff
    STR T1, [GPIO_I, #GPIO_IFC]
    //Perform actual signal processing
    LDR T2, [GPIO_I, #GPIO_DIN]
    MOV T1, #8
    LSL T2, T2, T1 // shift the 8 lsb from input to use as 8 msb for output
    STR T2, [GPIO_O, #GPIO_DOUT]
    BX lr

 // Helper sleepfunction
.thumb_func
wait:
    LDR W, =0x30000
wait_loop:
    SUBS W, #1
    BNE wait_loop
    BX lr

.thumb_func
led_test:
    PUSH {lr}
    // Test LEDs sequentially
    LDR T1, =0x7FFF
    MOV T2, #1
    MOV T3, #7
    loop:
         STR T1, [GPIO_O, #GPIO_DOUT]
         BL wait
         ROR T1, T2
         SUBS T3, #1
         BNE loop
    // Blink all LEDs twice
    LDR T1, =0x00FF
    LDR T2, =0xFFFF
    STR T1, [GPIO_O, #GPIO_DOUT]
    LDR W, =0xA0000
    BL wait_loop
    STR T2, [GPIO_O, #GPIO_DOUT]
    LDR W, =0xA0000
    BL wait_loop
    STR T1, [GPIO_O, #GPIO_DOUT]
    LDR W, =0xA0000
    BL wait_loop
    STR T2, [GPIO_O, #GPIO_DOUT]
    // Return function, LEDs are now off 
    POP {pc}

/////////////////////////////////////////////////////////////////////////////
//
// Some dummy handler
//
/////////////////////////////////////////////////////////////////////////////

.thumb_func
dummy_handler:
    B _reset
