#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <errno.h>

typedef struct {
    unsigned int x;
    unsigned int y;
    bool* data;
} pbm_image_t;

typedef struct {
    char name;
    bool* data;
} char_t;

typedef struct {
    unsigned int char_w;
    unsigned int char_h;
    char_t* chars;
} font_t;

int init_fonts();
int init_font(font_t* font, char* name);
int path_to_pbm(char* path, pbm_image_t* pbm);
int pbm_to_font(pbm_image_t* pbm, font_t* font);

font_t* font_large;
font_t* font_medium;
font_t* font_small;
