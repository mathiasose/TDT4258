#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

typedef struct  __attribute__((__packed__)) bitmap_fileheader {
    uint16_t bf_type;     // File type
    uint32_t bf_size;       // Byte size of the .bmp file
    uint32_t bf_reserved;   // Reserved, must be 0
    uint32_t bf_off_bits;    // Specifies offset in bytes from file header 
                                // to data section
} bitmap_fileheader;

typedef struct __attribute__((__packed__)) bitmap_infoheader {
    uint32_t bi_size; // Header size in bytes 
    uint32_t bi_width; // Image width in pixels
    uint32_t bi_height; // Image height in pixels
    uint16_t bi_planes; // Number of color panes
    uint16_t bi_bit_count; // Bits per pixel
    uint32_t bi_compression; // Compression type
    uint32_t bi_size_image; // Size of image in bytes
    int32_t bi_x_pels_per_meter; // Pixels/meter along x axis
    int32_t bi_y_pels_per_meter; // Pixels/meter along y axis
    uint32_t bi_clr_used; // Number of colors used by the bitmap
    uint32_t bi_clr_important; // Number of colors that are important
} bitmap_infoheader;

int init_fonts();
int path_to_font(char* path, font* fontp); 
