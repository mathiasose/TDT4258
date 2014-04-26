#include "graphics.h"

#define FB_DRAW 0x4680

#define MARGIN 2
#define TEXT_X_ANCHOR 245

int fbfd;
uint16_t* fbp;
int screensize_pixels;
int screensize_bytes;

struct fb_var_screeninfo vinfo;
struct fb_copyarea screen;

int init_framebuffer()
{
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

    screen.dx = 0;
    screen.dy = 0;
    screen.width = vinfo.xres;
    screen.height = vinfo.yres;

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
        fbp[i] = BACKGROUND_COLOR;
    }

    draw_string_at("CURRENT SCORE:", 14, font_small, TEXT_X_ANCHOR, 0);
    draw_string_at("HIGH SCORE:", 11, font_small, TEXT_X_ANCHOR, 30);

    draw_string_at("Press SW6 twice to", 18, font_small, TEXT_X_ANCHOR, 220);
    draw_string_at("start a new game.", 17, font_small, TEXT_X_ANCHOR, 230);

    return EXIT_SUCCESS;
}

void deinit_framebuffer()
{
    munmap(fbp, screensize_bytes);
    close(fbfd);
}

void refresh_fb()
{
    ioctl(fbfd, FB_DRAW, &screen);
}

bool* create_glyph(char* str, int len, font_t* font)
{
    bool* glyph = (bool*)malloc(len*(font->char_h)*(font->char_w)*sizeof(bool));
    for (int i = 0; i < len; i++) {
        bool* chardata = font->chars[str[i]-' '].data;
        for (int y = 0; y < (font->char_h); y++) {
            for (int x = 0; x < (font->char_w); x++) {
                glyph[(len * (font->char_w) * y) + i*(font->char_w) + x] = chardata[(font->char_w)*y + x];
            }
        }
    }

    return glyph;
}

void draw_tile(int pos, int val)
{
    int number = pow(2, val);

    int screen_offset_x = (60 * pos) % 240;
    int screen_offset_y = 60 * (pos / 4) - 1;

    int len = 0;
    if (val > 0 ) {
        int temp = number;
        while(temp) {
            temp = temp / 10;
            len++;
        }
    } else {
        len = 1;
    }

    font_t* font = font_large;
    if (len > 3) {
        font = font_medium;
    }

    char str[len];
    if (val == -1) {
        str[0] = gameover[pos];
    } else {
        sprintf(str, "%d", number);
    }

    int padding_y = (60 - (font->char_h)) / 2;
    int padding_x = (60 - len*(font->char_w)) / 2;

    bool* glyph = create_glyph(str, len, font);

    for (int y = MARGIN; y < 60 - MARGIN; y++) {
        for (int x = MARGIN; x < 60 - MARGIN; x++) {
            int r = MARGIN + 1;
            if ((x < r || x >= 60 - r) && (y < r || y >= 60 - r)) {
                continue;
            }

            int screen_index_x = x + screen_offset_x;
            int screen_index_y = y + screen_offset_y;

            int screen_index = vinfo.xres*screen_index_y + screen_index_x;

            bool g = glyph[(y-padding_y)*len*(font->char_w) + (x-padding_x)];
            bool b = padding_y < y && y < 60 - padding_y && padding_x < x && x < 60 - padding_x;
            if (val != 0 && g && b) {
                fbp[screen_index] = (val == -1) ? White : Black;
                continue;
            }

            fbp[screen_index] = (val == -1) ? Black : colors[val];
        }
    }
    free(glyph);
}

void draw_game_over()
{
    for (int i = 0; i < 16; i++) {
        draw_tile(i, -1);
    }
}

int int_len(int number) {
    int len = 0;
    if (number == 0) {
        len = 1;
    } else {
        int temp = number;
        while(temp) {
            temp = temp / 10;
            len++;
        }
    }
    return len;
}

void draw_high_score(int high_score)
{
    int len = int_len(high_score);

    char str[len];
    sprintf(str, "%d", high_score);

    font_t* font = font_medium;
    if (vinfo.xres - TEXT_X_ANCHOR - len*(font->char_w) < 0) {
        font = font_small;
    }

    draw_string_at(str, len, font, TEXT_X_ANCHOR, 40);
}

void draw_score(int score)
{
    int len = int_len(score); 
    char str[len];
    sprintf(str, "%d", score);

    font_t* font = font_medium;
    if (vinfo.xres - TEXT_X_ANCHOR - len*(font->char_w) < 0) {
        font = font_small;
    }

    draw_string_at(str, len, font, TEXT_X_ANCHOR, 10);
}

void clear_score()
{
    for (int y = 10; y < 10 + (font_medium->char_h); y++) {
        for (int x = TEXT_X_ANCHOR; x < vinfo.xres; x++) {
            fbp[y*(vinfo.xres) + x] = BACKGROUND_COLOR;
        }
    }
}

void draw_string_at(char* str, int len, font_t* font, int x_anchor, int y_anchor)
{
    char* glyph = create_glyph(str, len, font);
    int glyph_w = len*(font->char_w);

    for (int y = 0; y < font->char_h; y++) {
        for (int x = 0; x < len*(font->char_w); x++) {
            int glyph_index = y*glyph_w + x;
            int screen_index = (y_anchor + y)*vinfo.xres + (x_anchor + x);

            fbp[screen_index] = glyph[glyph_index] ? Black : BACKGROUND_COLOR;
        }
    }

    free(glyph);
}
