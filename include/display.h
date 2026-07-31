#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32

void clear_display(uint8_t* display);
void render_display(uint8_t* display);

#endif