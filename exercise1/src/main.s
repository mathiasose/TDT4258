.syntax unified
.include "lib/efm32gg.s"

/////////////////////////////////////////////////////////////////////////////
//
// Exception vector table
// This table contains addresses for all exception handlers
//
/////////////////////////////////////////////////////////////////////////////

.section .vectors

    .long   stack_top               /* Top of Stack                 */
    .long   _reset                  /* Reset Handler                */
    .long   dummy_handler           /* NMI Handler                  */
    .long   dummy_handler           /* Hard Fault Handler           */
    .long   dummy_handler           /* MPU Fault Handler            */
    .long   dummy_handler           /* Bus Fault Handler            */
    .long   dummy_handler           /* Usage Fault Handler          */
    .long   dummy_handler           /* Reserved                     */
    .long   dummy_handler           /* Reserved                     */
    .long   dummy_handler           /* Reserved                     */
    .long   dummy_handler           /* Reserved                     */
    .long   dummy_handler           /* SVCall Handler               */
    .long   dummy_handler           /* Debug Monitor Handler        */
    .long   dummy_handler           /* Reserved                     */
    .long   dummy_handler           /* PendSV Handler               */
    .long   dummy_handler           /* SysTick Handler              */

    /* External Interrupts */
    .long   dummy_handler
    .long   gpio_handler            /* GPIO even handler */
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   gpio_handler            /* GPIO odd handler */
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler


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
    // Enable clock for GPIO
    LDR R4, =CMU_BASE
    LDR R5, [R4, #CMU_HFPERCLKEN0]
    MOV R6, #1
    LSL R6, R6, #CMU_HFPERCLKEN0_GPIO
    ORR R5, R5, R6
    STR R5, [R4, #CMU_HFPERCLKEN0]
    // Set high drive strength
    LDR R4, =GPIO_PA_BASE
    MOV R7, #0x2
    STR R7, [R4, #GPIO_CTRL]
    // Set pins 8-15 of port A for output
    LDR R7, =0x55555555
    STR R7, [R4, #GPIO_MODEH]
    BL led_test
    // Set pins 0-7 of port C for input
    LDR R4, =GPIO_PC_BASE
    LDR R7, =0x33333333
    STR R7, [R4, #GPIO_MODEL]
    LDR R7, =0xFF
    STR R7, [R4, #GPIO_DOUT]

// Main loop
.thumb_func
main:
    LDR R4, =GPIO_PA_BASE //output
    LDR R5, =GPIO_PC_BASE //input
    LDR R4, [R5, #GPIO_DIN]
    MOV R7, #8
    LSL R4, R4, R7 // shift the 8 lsb from input to use as 8 msb for output
    LDR R6, =0xF0F0 // bit mask for inverting
    EOR R4, R4, R6
    STR R4, [R5, #GPIO_DOUT]
    B main


 // Helper sleepfunction
.thumb_func
dowait:
    LDR R2, =0x100000
dowaitloop:
    SUBS R2, #1
    BNE dowaitloop
    BX lr

.thumb_func
led_test:
    PUSH {lr}
    // Test LEDs sequentially
    LDR R5, =0x7FFF
    LDR R6, =0xBFFF
    LDR R7, =0xDFFF
    LDR R8, =0xEFFF
    LDR R9, =0xF7FF
    LDR R10, =0xFBFF
    LDR R11, =0xFDFF
    LDR R12, =0xFEFF
    STR R5, [R4, #GPIO_DOUT]
    BL dowait
    STR R6, [R4, #GPIO_DOUT]
    BL dowait
    STR R7, [R4, #GPIO_DOUT]
    BL dowait
    STR R8, [R4, #GPIO_DOUT]
    BL dowait
    STR R9, [R4, #GPIO_DOUT]
    BL dowait
    STR R10, [R4, #GPIO_DOUT]
    BL dowait
    STR R11, [R4, #GPIO_DOUT]
    BL dowait
    STR R12, [R4, #GPIO_DOUT]
    BL dowait
    // Blink all LEDs twice
    LDR R0, =0xFFFF
    LDR R1, =0x00FF
    STR R1, [R4, #GPIO_DOUT]
    BL dowait
    STR R0, [R4, #GPIO_DOUT]
    BL dowait
    STR R1, [R4, #GPIO_DOUT]
    BL dowait
    STR R0, [R4, #GPIO_DOUT]
    // Return function, LEDs are now off 
    POP {pc}
    
/////////////////////////////////////////////////////////////////////////////
//
// GPIO handler
// The CPU will jump here when there is a GPIO interrupt
//
/////////////////////////////////////////////////////////////////////////////
.thumb_func
gpio_handler:
    b .  // do nothing

/////////////////////////////////////////////////////////////////////////////
//
// Some dummy handler
//
/////////////////////////////////////////////////////////////////////////////

.thumb_func
dummy_handler:
    b . // do nothing