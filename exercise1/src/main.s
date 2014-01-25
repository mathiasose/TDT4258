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
    b init  // do nothing

/////////////////////////////////////////////////////////////////////////////
//
// GPIO handler
// The CPU will jump here when there is a GPIO interrupt
//
/////////////////////////////////////////////////////////////////////////////
.thumb_func
gpio_handler:
    b init  // do nothing

/////////////////////////////////////////////////////////////////////////////
//
// Some dummy handler
//
/////////////////////////////////////////////////////////////////////////////

.thumb_func
dummy_handler:
    b init // do nothing


// Init
.thumb_func
init:
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
    // Test LED
    LDR R5, =0x0
    STR R5, [R4, #GPIO_DOUT]

// Main loop
.thumb_func
main:
    B main
