#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>

#define CHIP8_MEMORY_SIZE 4096   /* "The Chip-8 language is capable of accessing up to 4KB (4,096 bytes) of RAM" */
#define CHIP8_REGISTER_COUNT 16  /* "Chip-8 has 16 general purpose 8-bit registers" */
#define CHIP8_STACK_SIZE 16      /* "The stack is an array of 16 16-bit values" */

typedef struct {
    uint8_t memory[CHIP8_MEMORY_SIZE];
    uint8_t V[CHIP8_REGISTER_COUNT];

    uint16_t I;
    uint16_t pc;

    uint16_t stack[CHIP8_STACK_SIZE];
    uint8_t sp;

    uint8_t delay_timer;
    uint8_t sound_timer;

    uint8_t keypad[16];
    uint8_t display[64*32];
} Chip8;

void chip8_init(Chip8* chip8);

#endif