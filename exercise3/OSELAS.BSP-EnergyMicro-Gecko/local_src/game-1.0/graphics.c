#include "graphics.h"

#define FB_DRAW 0x4680

int fbfd;
uint16_t* fbp;
int screensize_pixels;
int screensize_bytes;

struct fb_var_screeninfo vinfo;
struct fb_copyarea grid;
/*
typedef union {
    uint16_t color;
    struct {
        int b : 5;
        int g : 6;
        int r : 5;
    };
} Color;
*/

void draw_tile(int pos, int value)
{
    int x_offset = (60 * pos) % 240;
    int y_offset = 60 * (pos / 4);

    int margin = 2;

    for (int y = margin; y < 60 - margin; y++) {
        for (int x = margin; x < 60 - margin; x++) {
            int r = margin + 1;
            if ((x < r || x >= 60 - r) && (y < r || y >= 60 - r)) {
                continue;
            }

            int x_coord = x + x_offset;
            int y_coord = y + y_offset;
            fbp[vinfo.xres*y_coord + x_coord] = colors[value];
        }
    }
}

int init_framebuffer()
{

    grid.dx = 0;
    grid.dy = 0;
    grid.width = 240;
    grid.height = 240;

    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        printf("Error: unable to open framebuffer device.\n");
        return EXIT_FAILURE;
    }

    // Get screen size info
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        printf("Error: unable to get screen info.\n");
        return EXIT_FAILURE;
    }
    printf("Screeninfo: %d x %d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    screensize_pixels = vinfo.xres * vinfo.yres;
    screensize_bytes = screensize_pixels * vinfo.bits_per_pixel / 8;

    fbp = (uint16_t*)mmap(NULL, screensize_bytes, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fbp == MAP_FAILED) {
        printf("Error: failed to memorymap framebuffer.\n");
        return EXIT_FAILURE;
    }

    if (init_fonts() == EXIT_FAILURE) {
        printf("Error: failed to initialize fonts.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < screensize_pixels; i++) {
        fbp[i] = DarkGrey;
    }

    return EXIT_SUCCESS;
}

void deinit_framebuffer()
{
    munmap(fbp, screensize_bytes);
    close(fbfd);
}

void redraw_grid()
{
    ioctl(fbfd, FB_DRAW, &grid);
}
