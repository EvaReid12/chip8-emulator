#include "sdl_display.h"
#include <stdio.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 320

bool
sdl_display_init(SDLDisplay* display)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init error: %s\n", SDL_GetError());
        return false;
    }

    display -> window = SDL_CreateWindow(
        "CHIP-8 Emulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (display -> window == NULL) {
        printf("SDL_CreateWindow error: %s\n", SDL_GetError());
        return false;
    }

    display -> renderer = SDL_CreateRenderer(
        display -> window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (display -> renderer == NULL) {
        printf("SDL_CreateRenderer error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

void
sdl_display_destroy(SDLDisplay* display)
{
    SDL_DestroyRenderer(display -> renderer);
    SDL_DestroyWindow(display -> window);

    SDL_Quit();
}