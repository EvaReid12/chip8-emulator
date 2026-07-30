#include <stdio.h>
#include "chip8.h"

int main(void)
{
    Chip8 chip8;
    chip8_init(&chip8);

    printf("Chip_8 initialized.\n");
    printf("Program Counter (pc): 0x%X\n", chip8.pc);

    chip8_load_program(&chip8, "../roms/IBM_Logo.ch8");

    printf("First octet of memory at 0x200: 0x%X\n", chip8.memory[0x200]);

    return 0;
}