#include <stdio.h>
#include "chip8.h"
#include <unistd.h>  /* For usleep() */
#include <time.h>
#include "timer.h"
#include "sdl_display.h"
#include <stdbool.h>

#define CPU_HZ 700
#define TIMER_HZ 60

int 
main(void)
{
    SDLDisplay display;
    sdl_display_init(&display);

    Chip8 chip8;
    chip8_init(&chip8);

    chip8_load_program(&chip8, "../roms/IBM_Logo.ch8");

    while (1) {
        chip8_cycle(&chip8);

        if (chip8.draw_flag) {
            sdl_display_render(&display, chip8.display);
            chip8.draw_flag = 0;
        }
    }
}