#include <stdio.h>
#include "chip8.h"
#include "display.h"

int 
main(void)
{
    Chip8 chip8;
    chip8_init(&chip8);

    // Draw a square
    for(int y = 10; y < 15; y++) {
        for(int x = 10; x < 20; x++) {
            chip8.display[y * DISPLAY_WIDTH + x] = 1;
        }
    }

    render_display(chip8.display);

    return 0;
}