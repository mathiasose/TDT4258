#include "graphics.h"

#define FB_DRAW 0x4680

int fbfd;
uint16_t* fbp;
int screensize_pixels;
int screensize_bytes;

struct fb_var_screeninfo vinfo;
struct fb_copyarea grid;

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

void refresh_fb()
{
    ioctl(fbfd, FB_DRAW, &grid);
}

void draw_tile(int pos, int val)
{
    int screen_offset_x = (60 * pos) % 240;
    int screen_offset_y = 60 * (pos / 4) - 1;

    int margin = 2;

    bool* char_mask = (bool*)malloc(60*60*sizeof(bool));
    //memset(&char_mask, 0, 60*60*sizeof(bool));

    if (val > 0) {
        int padding_x = (60 - 20) / 2;
        int padding_y = (60 - 24) / 2;

        char str[1];
        sprintf(str, "%X", val);

        bool* glyph = main_font->chars[str[0]-' '].data;

        for (int y = 0; y < 24; y++) {
            for (int x = 0; x < 20; x++) {
                char_mask[(padding_y + y)*60 + padding_x + x] = glyph[y*20 + x];
            }
        }
    }

    for (int y = margin; y < 60 - margin; y++) {
        for (int x = margin; x < 60 - margin; x++) {
            int r = margin + 1;
            if ((x < r || x >= 60 - r) && (y < r || y >= 60 - r)) {
                continue;
            }

            int screen_coord_x = x + screen_offset_x;
            int screen_coord_y = y + screen_offset_y;

            int screen_index = vinfo.xres*screen_coord_y + screen_coord_x;

            if ( val > 0 && char_mask[60*y + x] == 1 ) {
                fbp[screen_index] = Black;
            } else {
                fbp[screen_index] = (val < 0) ? Black : colors[val];
            }
        }
    }
    free(char_mask);
}

void draw_game_over()
{
    for (int i = 0; i < 16; i++) {
        draw_tile(i, -1);
    }
}

void draw_scores(int curr_score, int high_score)
{
    char str[15];
    sprintf(str, "%d", high_score);
}
