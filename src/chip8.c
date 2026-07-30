#include "chip8.h"
#include <string.h>

void chip8_init(Chip8* chip8)
{
    memset(chip8, 0, sizeof(Chip8));

    chip8 -> pc = 0x200; /* The first 512 bytes (0x000 to 0x1FF) are reserved for the interpreter, program usually starts at 0x200 */
}