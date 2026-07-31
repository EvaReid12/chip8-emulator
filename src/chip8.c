#include "chip8.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "instructions.h"

void chip8_init(Chip8* chip8)
{
    memset(chip8, 0, sizeof(Chip8));

    chip8 -> pc = 0x200; /* The first 512 bytes (0x000 to 0x1FF) are reserved for the interpreter, program usually starts at 0x200 */
}

void chip8_load_program(Chip8* chip8, const char* filename)
{
    FILE* file = fopen(filename, "rb");

    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    unsigned char buffer[CHIP8_MEMORY_SIZE - 0x200]; /* Load program into memory starting at 0x200 */

    size_t size = fread(buffer, sizeof(unsigned char), sizeof(buffer), file);

    fclose(file);

    if (size == 0) {
        fprintf(stderr, "Failed to read file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < size; i++) {
        chip8 -> memory[0x200 + i] = buffer[i];
    }

    printf("Loaded program '%s' into memory (size: %ld octets).\n", filename, size);
}

void chip8_cycle(Chip8* chip8)
{
    chip8 -> opcode = chip8 -> memory[chip8 -> pc] << 8 | chip8 -> memory[chip8 -> pc + 1];

    chip8 -> pc += 2; /* Increment the program counter to point to the next instruction */

    execute_opcode(chip8);
}