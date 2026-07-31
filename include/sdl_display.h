#ifndef SDL_DISPLAY_H
#define SDL_DISPLAY_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
} SDLDisplay;

void sdl_display_render(SDLDisplay* display, uint8_t framebuffer[64 * 32]);

bool sdl_display_init(SDLDisplay* display);

void sdl_display_destroy(SDLDisplay* display);

#endif