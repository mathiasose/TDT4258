#include "font.h"
#define NUM_CHARS 91
char characters[NUM_CHARS] = {
    '\0', '!', '"', '#', '$', '%', '&', '|', '(', ')', '*', '+', ',', '-', '.',
    '/', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=',
    '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
    'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[',
    '\\', ']', '^', '_', '\'', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y',
    'z'
};

int init_fonts()
{
    // Allocate memory for font_large
    font_large = (font_t*)malloc(sizeof(font_t));
    if (font_large == NULL) {
        printf("Error: unable to allocate memory for font_large\n");
        return EXIT_FAILURE;
    }
    font_large->char_w = 20;
    font_large->char_h = 24;
    // Initialize font_large
    if (init_font(font_large, "font_large") == EXIT_FAILURE) {
        printf("Error: unable to init font: font_large\n");
        free(font_large);
        return EXIT_FAILURE;
    }
    // Allocate memory for font_medium
    font_medium = (font_t*)malloc(sizeof(font_t));
    if (font_medium == NULL) {
        printf("Error: unable to allocate memory for font_medium\n");
        free(font_large);
        return EXIT_FAILURE;
    }
    font_medium->char_w = 8;
    font_medium->char_h = 12;
    // Initialize font_medium
    if (init_font(font_medium, "font_medium") == EXIT_FAILURE) {
        printf("Error: unable to init font: font_medium\n");
        free(font_large);
        free(font_medium);
        return EXIT_FAILURE;
    }
    // Allocate memory for font_small
    font_small = (font_t*)malloc(sizeof(font_t));
    if (font_small == NULL) {
        printf("Error: unable to allocate memory for font_small\n");
        free(font_large);
        free(font_medium);
        return EXIT_FAILURE;
    }
    if (init_font(font_small, "font_small") == EXIT_FAILURE) {
        printf("Error: unable to init font: font_small\n");
        free(font_large);
        free(font_medium);
        free(font_small);
        return EXIT_FAILURE;
    }
}

int init_font(font_t* font, char* name) 
{
    // Allocate memory for pbm
    pbm_image_t* pbm = (pbm_image_t*)malloc(sizeof(pbm_image_t));
    if (pbm == NULL) {
        printf("Error: unable to allocate memory for pbm\n");
        return EXIT_FAILURE;
    }
    // Build path
    char* base = "/lib/game/res/font/";
    char* path = (char*)malloc(strlen(base) * sizeof(char) + strlen(name) * sizeof(char));
    strcpy(path, base);
    strcat(path, name);
    strcat(path, ".pbm");
    // Attempt to load main font image
    if (path_to_pbm(path, pbm) == EXIT_FAILURE) {
        printf("Error: Unable to load pbm: %s\n", name);
        free(pbm);
        return EXIT_FAILURE;
    }
    // Convert from pbm to font_t
    if (pbm_to_font(pbm, font) == EXIT_FAILURE) {
        printf("Error: unable to generate font from pbm\n");
        free(pbm);
        return EXIT_FAILURE;
    }
    // Not needed any more after this point
    free(pbm);
    return EXIT_SUCCESS;
}

/*
 * path_to_pbm - will build a font given a path to a compatible .pbm.
 */

int path_to_pbm(char* path, pbm_image_t* pbm) 
{
    char buff[16];
    FILE* f_ptr;
    // Open file
    if ((f_ptr = fopen(path, "rb")) == NULL) {
        printf("Error: failed to open file.\n");
        fclose(f_ptr);
        return EXIT_FAILURE;
    }

    // Read image format
    if (fgets(buff, sizeof(buff), f_ptr) == NULL) {
        printf("Error: unable to read image format\n");
        fclose(f_ptr);
        return EXIT_FAILURE;
    }

    // Check image format
    if (buff[0] != 'P' || buff[1] != '1') {
        printf("Error: invalid image format (must be 'P1')\n");
        fclose(f_ptr);
    }

    // Check for comments
    int c = getc(f_ptr);
    while (c == '#') {
        while (getc(f_ptr) != '\n');
        c = getc(f_ptr); 
    }
    ungetc(c, f_ptr);

    // Read image size
    if (fscanf(f_ptr, "%d %d", &(pbm->x), &(pbm->y)) != 2) {
        printf("Error: invalid image size\n");
        fclose(f_ptr);
        return EXIT_FAILURE;
    }

    // Move to image data
    while (getc(f_ptr) != '\n');
    // Allocate memory for data
    pbm->data = (bool*)malloc(pbm->x * pbm->y * sizeof(bool));
    if (pbm->data == NULL) {
        printf("Error: unable to allocate memory for image data\n");
        free(pbm->data);
        fclose(f_ptr);
        return EXIT_FAILURE;
    }
    int p_idx = 0;
    while ((c = getc(f_ptr)) != EOF) {
        if (c == '\n') {
            continue;
        }
        pbm->data[p_idx++] = c-'0';
    }
    fclose(f_ptr);
    return EXIT_SUCCESS;
}

/*
 * pbm_to_font - generates a font_t from a valid pbm
 */
int pbm_to_font(pbm_image_t* pbm, font_t* font)
{
    // Allocate memory for each character
    font->chars = (char_t*)malloc(NUM_CHARS * sizeof(char_t));
    if (font->chars == NULL) {
        printf("Error: unable to allocate memory for characters\n");
        return EXIT_FAILURE;
    }
    for (int ch_idx = 0; ch_idx < NUM_CHARS; ch_idx++) {
        font->chars[ch_idx].name = characters[ch_idx];
        font->chars[ch_idx].data = (bool*)malloc(font->char_w * font->char_h * sizeof(bool));
        int data_cnt = 0;
        int offset_x = (font->char_w * ch_idx) % pbm->x;
        int offset_y = font->char_h * (ch_idx / 15);

        for (int y = 0; y < font->char_h; y++) {
            for (int x = 0; x < font->char_w; x++) { 
                font->chars[ch_idx].data[data_cnt++] = pbm->data[(offset_y + y) * pbm->x + offset_x + x]; 
            }
        }
    }
    return EXIT_SUCCESS;
}
