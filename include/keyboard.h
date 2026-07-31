#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SDL2/SDL.h>
#include <stdint.h>

void keyboard_update(SDL_Event* event, uint8_t keypad[16]);

#endif