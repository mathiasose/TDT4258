#include "game.h"

void draw()
{
    FILE* f = fopen("/dev/fb0", "w");
    fprintf(f, "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ");
    fclose(f);
}
