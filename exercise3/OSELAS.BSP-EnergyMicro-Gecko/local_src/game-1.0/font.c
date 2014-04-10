#include "font.h"
#define NUM_CHARS 91
char* characters = {'\0', '!', '"', '#', '$', '%', '&', '|', '(', ')', '*', '+', ',', '-', '.',
                    '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=',
                    '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[',
                    '\\', ']', '^', '_', '\'', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y',
                    'z'};

font* main_font;

int init_fonts() 
{
    // Attempt to set main font
    if (path_to_font("/lib/game/res/font/font_small.bmp", main_font) == EXIT_FAILURE) {
        printf("Error: Unable to load font.\n" );
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/*
 * path_to_font - will build a font given a path to a compatible .bmp.
 */

int path_to_font(char* path, font* fontp) 
{
    FILE* f_ptr;
    unsigned char* image;
    bitmap_fileheader bfh;
    bitmap_infoheader bih;
    // Open file
    if ((f_ptr = fopen(path, "rb")) == NULL) {
        printf("Error: failed to open file.\n");
        return EXIT_FAILURE;
    }

    // Read file header
    fread(&bfh, sizeof(bitmap_fileheader), 1, f_ptr);
    if (bfh.bf_type != 0x4D42) {
        printf("Error: not a .bmp file\n");
        fclose(f_ptr);
        return EXIT_FAILURE;
    }

    // Read info header
    fread(&bih, sizeof(bitmap_infoheader), 1, f_ptr);

    // Move to beginning of image data
    fseek(f_ptr, bfh.b_off_bits, SEEK_SET);
    
    /*
    // Allocate memory for image data
    image = (unsigned char*)malloc(10);
    if (image == NULL) {
        printf("Error: unable to allocate memory for image data.\n");
        free(image);
        fclose(f_ptr);
        return EXIT_FAILURE;
    }

    // Read image data
    fread(image, 10, 1,f_ptr);
    if (image == NULL) {
        printf("Error: unable to read image data\n");
        fclose(f_ptr);
        return EXIT_FAILURE;
    }

    // Populate fontp
    int char_idx;
    fontp->char_w = 20;
    fontp->char_h = 24;
    for (char_idx = 0; char_idx < NUM_CHARS; char_idx++) {
        fontp->characters[char_idx].letter = characters[char_idx];
    }
    */

    fclose(f_ptr);
    return EXIT_SUCCESS;
}
