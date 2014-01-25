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
    // aliases
    GPIO_O .req R4
    GPIO_I .req R5
    GPIO .req R6
    T1 .req R7
    T2 .req R8
    T3 .req R9
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
    LDR GPIO_O, =GPIO_PC_BASE
    STR T1, [GPIO_O, #GPIO_IFC]
    //Perform actual signal processing
    LDR GPIO_O, =GPIO_PA_BASE //output
    LDR GPIO_I, =GPIO_PC_BASE //input
    LDR GPIO_I, [GPIO_I, #GPIO_DIN]
    MOV T1, #8
    LSL GPIO_I, GPIO_I, T1 // shift the 8 lsb from input to use as 8 msb for output
    STR GPIO_I, [GPIO_O, #GPIO_DOUT]
    BX lr

 // Helper sleepfunction
.thumb_func
dowait:
    LDR T1, =0x50000
dowaitloop:
    SUBS T1, #1
    BNE dowaitloop
    BX lr

.thumb_func
led_test:
    PUSH {lr}
    // Test LEDs sequentially
    LDR T1, =0x7FFF
    STR T1, [GPIO_O, #GPIO_DOUT]
    BL dowait
    LDR T1, =0xBFFF
    STR T1, [GPIO_O, #GPIO_DOUT]
    BL dowait
    LDR T1, =0xDFFF
    STR T1, [GPIO_O, #GPIO_DOUT]
    BL dowait    
    LDR T1, =0xEFFF
    STR T1, [GPIO_O, #GPIO_DOUT]
    BL dowait
    LDR T1, =0xF7FF
    STR T1, [GPIO_O, #GPIO_DOUT]
    BL dowait
    LDR T1, =0xFBFF
    STR T1, [GPIO_O, #GPIO_DOUT]
    BL dowait
    LDR T1, =0xFDFF
    STR T1, [GPIO_O, #GPIO_DOUT]
    BL dowait
    LDR T1, =0xFEFF
    STR T1, [GPIO_O, #GPIO_DOUT]
    BL dowait
    // Blink all LEDs twice
    LDR T2, =0xFFFF
    LDR T1, =0x00FF
    STR T1, [GPIO_O, #GPIO_DOUT]
    BL dowait
    BL dowait
    STR T2, [GPIO_O, #GPIO_DOUT]
    BL dowait
    BL dowait
    STR T1, [GPIO_O, #GPIO_DOUT]
    BL dowait
    BL dowait
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
    b . // do nothing