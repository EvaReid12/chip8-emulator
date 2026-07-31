#include <stdio.h>
#include "chip8.h"
#include "display.h"
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

    if (!sdl_display_init(&display)) {
        return 1;
    }

    bool running = true;

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    sdl_display_destroy(&display);

    return 0;
}