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

    //Read info header     
    fread(&bih, sizeof(bitmap_infoheader), 1, f_ptr);

    printf("/*****************************************************/\n");
    printf("/ IMAGE DEBUG DATA\n");
    printf("/*****************************************************/\n");

    printf("Type: %d\n", bfh.bf_type);
    printf("File size: %d\n", bfh.bf_size);
    printf("Reserved: %d\n", bfh.bf_reserved);
    printf("Offset: %d\n", bfh.bf_off_bits);
    printf("Infoheader size: %d\n", bih.bi_size);
    printf("Width: %d, height: %d\n", bih.bi_width, bih.bi_height);
    printf("Planes: %d\n", bih.bi_planes);
    printf("BPP: %d\n", bih.bi_bit_count);
    printf("Compression: %d\n", bih.bi_compression);
    printf("BSI: %d\n", bih.bi_size_image);
    printf("Xres: %d\n", bih.bi_x_pels_per_meter);
    printf("Yres: %d\n", bih.bi_y_pels_per_meter);
    printf("Used colors: %d\n", bih.bi_clr_used);
    printf("Imp. colors: %d\n", bih.bi_clr_important);

    int row_size = ((int)floor((bih.bi_bit_count * bih.bi_width + 31)/32)) * 4;
    int image_data_size = row_size * abs(bih.bi_height);
    printf("Image data size: %d\n", image_data_size);

    image = (unsigned char*)malloc(image_data_size);

    if (image == NULL) {
        printf("Error: unable to allocate memory for image data\n");
        fclose(f_ptr);
        return EXIT_FAILURE;
    }

    // Move to beginning of image data
    fseek(f_ptr, bfh.bf_off_bits, SEEK_SET);

    // Read image data
    fread(image, sizeof(image), 1, f_ptr);
    if (image == NULL) {
        printf("Error: unable to read image data\n");
        fclose(f_ptr);
        return EXIT_FAILURE;
    }

    printf("Successfully loaded image into memory\n"); 

    for (int i = 0; i < (bih.bi_width * abs(bih.bi_height) * 4); i++) {
        if (image[i] != NULL)
            printf("%d ", image[i]);
    }
    printf("\n");
    fclose(f_ptr);
    return EXIT_SUCCESS;
}
