#include "graphics.h"

int fbfd;
char* fbp;

int init_framebuffer()
{
    struct fb_var_screeninfo vinfo;
    struct fb_copyarea rect;
    int screensize;
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

    rect.dx = 0;
    rect.dy = 0;
    rect.width = 320;
    rect.height = 240;

    for (int i = 0; i < screensize; i++) {
        fbp[i] = 0xFFFF;
    }
    ioctl(fbfd, 0x4680, &rect);
    return EXIT_SUCCESS;
}
