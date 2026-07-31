#include <stdio.h>
#include "chip8.h"
#include <unistd.h>  /* For usleep() */
#include <time.h>
#include "timer.h"
#include "sdl_display.h"
#include <stdbool.h>
#include "keyboard.h"

#define CPU_HZ 700
#define TIMER_HZ 60

int 
main(void)
{
    SDLDisplay display;
    sdl_display_init(&display);

    bool running = true;

    uint64_t last_timer_update = time_ms();

    uint64_t last_cycle_time = time_ms();

    Chip8 chip8;
    chip8_init(&chip8);

    chip8_load_program(&chip8, "../roms/Tetris.ch8");

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            keyboard_update(&event, chip8.keypad);
        }

        uint64_t now = time_ms();

        if (now - last_cycle_time >= 1000 / CPU_HZ) {
            chip8_cycle(&chip8);
            last_cycle_time = now;
        }

        if (now - last_timer_update >= 1000 / TIMER_HZ) {
            chip8_update_timers(&chip8);
            last_timer_update = now;
        }

        if (chip8.draw_flag) {
            sdl_display_render(&display, chip8.display);
            chip8.draw_flag = 0;
        }

    }
}