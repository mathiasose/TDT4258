#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
static uint16_t i = 0;
static uint16_t sin[] = {
    1024, 1088, 1152, 1216, 1279, 1340, 1401, 1460, 1517, 1573, 1626, 1677,
    1725, 1770, 1813, 1852, 1889, 1921, 1951, 1976, 1998, 2016, 2030, 2040,
    2046, 2048, 2046, 2040, 2030, 2016, 1998, 1976, 1951, 1921, 1889, 1852,
    1813, 1770, 1725, 1677, 1626, 1573, 1517, 1460, 1401, 1340, 1279, 1216,
    1152, 1088, 1024, 960, 896, 832, 769, 708, 647, 588, 531, 475, 422, 371,
    323, 278, 235, 196, 159, 127, 97, 72, 50, 32, 18, 8, 2, 0, 2, 8, 18, 32,
    50, 72, 97, 127, 159, 196, 235, 278, 323, 371, 422, 475, 531, 588, 647,
    708, 769, 832, 896, 960 
};
/*static uint16_t sin[] = {
  0x7ff, 0x86a, 0x8d5, 0x93f, 0x9a9, 0xa11, 0xa78, 0xadd, 0xb40, 0xba1,
  0xbff, 0xc5a, 0xcb2, 0xd08, 0xd59, 0xda7, 0xdf1, 0xe36, 0xe77, 0xeb4,
  0xeec, 0xf1f, 0xf4d, 0xf77, 0xf9a, 0xfb9, 0xfd2, 0xfe5, 0xff3, 0xffc,
  0xfff, 0xffc, 0xff3, 0xfe5, 0xfd2, 0xfb9, 0xf9a, 0xf77, 0xf4d, 0xf1f,
  0xeec, 0xeb4, 0xe77, 0xe36, 0xdf1, 0xda7, 0xd59, 0xd08, 0xcb2, 0xc5a,
  0xbff, 0xba1, 0xb40, 0xadd, 0xa78, 0xa11, 0x9a9, 0x93f, 0x8d5, 0x86a,
  0x7ff, 0x794, 0x729, 0x6bf, 0x655, 0x5ed, 0x586, 0x521, 0x4be, 0x45d,
  0x3ff, 0x3a4, 0x34c, 0x2f6, 0x2a5, 0x257, 0x20d, 0x1c8, 0x187, 0x14a,
  0x112, 0x0df, 0x0b1, 0x087, 0x064, 0x045, 0x02c, 0x019, 0x00b, 0x002,
  0x000, 0x002, 0x00b, 0x019, 0x02c, 0x045, 0x064, 0x087, 0x0b1, 0x0df,
  0x112, 0x14a, 0x187, 0x1c8, 0x20d, 0x257, 0x2a5, 0x2f6, 0x34c, 0x3a4,
  0x3ff, 0x45d, 0x4be, 0x521, 0x586, 0x5ed, 0x655, 0x6bf, 0x729, 0x794
  };*/
static int SIN_NUM_SAMPLES = 100;

void note(int n) {
    int offset = (i  % SIN_NUM_SAMPLES);
    *DAC0_CH0DATA = sin[offset];
}


/* TIMER1 interrupt handler */
void __attribute__ ((interrupt)) TIMER1_IRQHandler() {  
    /* Clear interrupt flag */
    *TIMER1_IFC = 1;
    /* Do some magic yo */
    note(1);
    //*DAC0_CH0DATA = sin[(n*i) % SIN_NUM_SAMPLES];
    i = (i+1) % SIN_NUM_SAMPLES;
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() {
    /* TODO handle button pressed event, remember to clear pending interrupt */
    *GPIO_IFC = *GPIO_IF;
    /* Do the magic */
    //*TIMER1_CMD = 1;
    *GPIO_PA_DOUT = *GPIO_PC_DIN << 8;
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() {
    /* TODO handle button pressed event, remember to clear pending interrupt */
    *GPIO_IFC = *GPIO_IF;
    /* Magic repeated */
    //*TIMER1_CMD = 1;
    *GPIO_PA_DOUT = *GPIO_PC_DIN << 8;
}
