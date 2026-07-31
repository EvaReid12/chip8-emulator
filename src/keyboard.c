#include "keyboard.h"

void
keyboard_update(SDL_Event* event, uint8_t keypad[16])
{
    if (event -> type != SDL_KEYDOWN && event -> type != SDL_KEYUP) {
        return;
    }

    uint8_t pressed = (event -> type == SDL_KEYDOWN) ? 1 : 0;

    switch (event -> key.keysym.sym) {
        case SDLK_1:
            keypad[0x1] = pressed;
            break;
        case SDLK_2:
            keypad[0x2] = pressed;
            break;
        case SDLK_3:
            keypad[0x3] = pressed;
            break;
        case SDLK_4:
            keypad[0xC] = pressed;
            break;
        case SDLK_q:
            keypad[0x4] = pressed;
            break;
        case SDLK_w:
            keypad[0x5] = pressed;
            break;
        case SDLK_e:
            keypad[0x6] = pressed;
            break;
        case SDLK_r:
            keypad[0xD] = pressed;
            break;
        case SDLK_a:
            keypad[0x7] = pressed;
            break;
        case SDLK_s:
            keypad[0x8] = pressed;
            break;
        case SDLK_d:
            keypad[0x9] = pressed;
            break;
        case SDLK_f:
            keypad[0xE] = pressed;
            break;
        case SDLK_z:
            keypad[0xA] = pressed;
            break;
        case SDLK_x:
            keypad[0x0] = pressed;
            break;
        case SDLK_c:
            keypad[0xB] = pressed;
            break;
        case SDLK_v:
            keypad[0xF] = pressed;
    }
}