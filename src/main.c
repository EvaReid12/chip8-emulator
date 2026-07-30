#include <stdio.h>
#include "chip8.h"

int main(void)
{
    Chip8 chip8;
    chip8_init(&chip8);

    printf("Chip_8 initialized.\n");
    printf("Program Counter (pc): 0x%X\n", chip8.pc);
    return 0;
}