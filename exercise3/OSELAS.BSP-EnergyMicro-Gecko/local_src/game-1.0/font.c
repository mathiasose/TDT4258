#include "font.h"

font* main_font;

int init_fonts() 
{
    // Attempt to set main font
    if (path_to_font("/lib/game/res/font/font_small.bmp", main_font) == EXIT_FAILURE) {
        printf("Error: Unable to set font.\n" );
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/*
 * path_to_font - will build a font given a path to a compatible .bmp.
 */

int path_to_font(char* path, font* fontp) 
{
    FILE* f_ptr = fopen(path, "rb");
    if (f_ptr == NULL) {
        printf("Error: failed to open file.\n");
        return EXIT_FAILURE;
    } 
}
