#include "display.h"
#include <stdio.h>
#include <string.h>

void
clear_display(uint8_t* display)
{
    memset(display, 0, DISPLAY_WIDTH * DISPLAY_HEIGHT);
}

void
render_display(uint8_t* display)
{
    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (int x = 0; x < DISPLAY_WIDTH; x++) {
            uint8_t pixel = display[y * DISPLAY_WIDTH + x];
            printf("%c", pixel ? '#' : ' ');
        }
        printf("\n");
    }
}