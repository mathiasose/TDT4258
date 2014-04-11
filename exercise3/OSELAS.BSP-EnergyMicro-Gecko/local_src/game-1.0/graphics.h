#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 1
#define _GNU_SOURCE 1
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include "font.h"

#define Black           0x0000
#define White           0xFFFF
#define DarkGrey        0x7BEF
#define LightGrey       0xC618
#define Yellow          0xFFE0
#define Orange          0xFD20
#define Red             0xF800
#define Maroon          0x7800
#define Pink            0xF81F
#define GreenYellow     0xAFE5
#define Green           0x07E0
#define DarkGreen       0x03E0
#define DarkCyan        0x03EF
#define Cyan            0x07FF
#define Blue            0x001F
#define Navy            0x000F
#define Purple          0x780F
#define Olive           0x7BE0

static uint16_t colors[17] = {
    LightGrey,
    Yellow,   Orange,      Red,      Maroon,
    Pink,     GreenYellow, Green,    DarkGreen,
    DarkCyan, Cyan,        Blue,     Navy,
    Purple,   Olive,       DarkGrey, Black
};

/* Prototypes */
int init_framebuffer();
void deinit_framebuffer();
void refresh_fb();
void draw_tile(int pos, int val);
void draw_game_over();
void draw_scores(int curr_score, int high_score);
