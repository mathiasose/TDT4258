#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef union {
    uint16_t color;
    struct {
        int b: 5;
        int g: 6;
        int r: 5;
    };
} pixel_t;

typedef struct {
    int x, y;
    bool* data;
} pbm_image_t;

typedef struct {
    char name;
    bool* data;
} char_t;

typedef struct {
    int char_w, char_h;
    char_t* chars;
} font_t;

int init_fonts();
int path_to_pbm(char* path, pbm_image_t* pbm);
int pbm_to_font(pbm_image_t* pbm, font_t* font);
