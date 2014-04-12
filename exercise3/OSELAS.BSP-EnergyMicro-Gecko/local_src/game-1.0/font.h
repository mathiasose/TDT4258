#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

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
int path_to_pbm(char* path, pbm_image_t* pbm);
int pbm_to_font(pbm_image_t* pbm, font_t* font);

pbm_image_t* main_pbm;
pbm_image_t* small_pbm;
font_t* main_font;
font_t* small_font;
