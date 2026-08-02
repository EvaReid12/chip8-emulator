#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SDL2/SDL.h>
#include <stdint.h>

/**
 * @brief Updates the state of the keypad based on SDL events.
 * 
 * @param event Pointer to the SDL_Event structure containing the event data.
 * @param keypad Array representing the state of the keypad (16 keys).
 *               Each index corresponds to a key, where 1 indicates pressed and 0 indicates released.
 */
void keyboard_update(SDL_Event* event, uint8_t keypad[16]);

#endif