#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct pixel_t {
    uint16_t colors;
} pixel_t;

typedef struct char_t {
    pixel_t** pixels;
    char letter;
} char_t;

typedef struct font {
    char_t* characters;
    int char_w;
    int char_h;
} font;

int init_fonts();
int path_to_font(char* path, font* fontp); 
