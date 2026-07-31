#ifndef SDL_DISPLAY_H
#define SDL_DISPLAY_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} SDLDisplay;

bool sdl_display_init(SDLDisplay* display);

void sdl_display_destroy(SDLDisplay* display);

#endif