#ifndef SDL_DISPLAY_H
#define SDL_DISPLAY_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Structure representing the SDL display, containing the window and renderer.
 */
typedef struct {
    /** Pointer to the SDL window */
    SDL_Window* window;
    /** Pointer to the SDL renderer */
    SDL_Renderer* renderer;
} SDLDisplay;

/**
 * @brief Renders the framebuffer to the SDL display.
 * 
 * @param display Pointer to the SDLDisplay structure containing the window and renderer.
 * @param framebuffer Array representing the state of the display (64x32 pixels).
 */
void sdl_display_render(SDLDisplay* display, uint8_t framebuffer[64 * 32]);

/**
 * @brief Initializes the SDL display, creating the window and renderer.
 * 
 * @param display Pointer to the SDLDisplay structure to be initialized.
 * @return true if initialization is successful, false otherwise.
 */
bool sdl_display_init(SDLDisplay* display);

/**
 * @brief Destroys the SDL display, cleaning up resources.
 * 
 * @param display Pointer to the SDLDisplay structure to be destroyed.
 */
void sdl_display_destroy(SDLDisplay* display);

#endif