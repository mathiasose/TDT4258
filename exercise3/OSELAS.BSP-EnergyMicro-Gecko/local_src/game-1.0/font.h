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

#pragma pack(push, 1)
typedef struct bitmap_fileheader {
    unsigned short bf_type;     // File type
    unsigned int bf_size;       // Byte size of the .bmp file
    unsigned int bf_reserved;   // Reserved, must be 0
    unsigned int b_off_bits;    // Specifies offset in bytes from file header 
                                // to data section
} bitmap_fileheader;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct bitmap_infoheader {
    unsigned int bi_size; // Header size in bytes 
    int bi_width; // Image width in pixels
    unsigned int bi_height; // Image height in pixels
    unsigned short bi_planes; // Number of color panes
    unsigned short bi_bit_count; // Bits per pixel
    unsigned int bi_compression; // Compression type
    unsigned int bi_size_image; // Size of image in bytes
    int bi_x_pels_per_meter; // Pixels/meter along x axis
    int bi_y_pels_per_meter; // Pixels/meter along y axis
    unsigned int bi_clr_used; // Number of colors used by the bitmap
    unsigned int bi_clr_important; // Number of colors that are important
} bitmap_infoheader;
#pragma pack(pop)

int init_fonts();
int path_to_font(char* path, font* fontp); 
