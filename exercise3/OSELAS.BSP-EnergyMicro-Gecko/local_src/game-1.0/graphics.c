#include "graphics.h"

#define FB_DRAW 0x4680

int fbfd;
uint16_t* fbp;
int screensize;

int init_framebuffer()
{
    struct fb_var_screeninfo vinfo;
    struct fb_copyarea rect;
    system("echo 0 > /sys/class/graphics/fbcon/cursor_blink");
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
    // Screensize in bytes
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
    fbp = (uint16_t*)mmap(NULL, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if ((int)fbp == MAP_FAILED) {
        printf("Error: failed to memorymap framebuffer.\n");
        return EXIT_FAILURE;
    }

    // Fill screen with all black
    rect.dx = 0;
    rect.dy = 0;
    rect.width = vinfo.xres;
    rect.height = vinfo.yres;

    for (int i = 0; i < screensize/2; i++) {
        fbp[i] = 0x0000;
    }
    ioctl(fbfd, FB_DRAW, &rect);

    if (init_fonts() == EXIT_FAILURE) {
        printf("Error: failed to initialize fonts");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void deinit_framebuffer()
{
    munmap(fbp, screensize);
    close(fbfd);
}
