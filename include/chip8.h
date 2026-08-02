#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>

#define CHIP8_MEMORY_SIZE 4096   /* "The Chip-8 language is capable of accessing up to 4KB (4,096 bytes) of RAM" */
#define CHIP8_REGISTER_COUNT 16  /* "Chip-8 has 16 general purpose 8-bit registers" */
#define CHIP8_STACK_SIZE 16      /* "The stack is an array of 16 16-bit values" */

/**
 * @brief CHIP-8 virtual machine state.
 * 
 * Contains the memory, registers, program counter, stack, timers, keypad state, and display buffer.
 */
typedef struct {
    /** The memory of the CHIP-8 virtual machine. */
    uint8_t memory[CHIP8_MEMORY_SIZE];

    /** General-purpose registers. V0-VF */
    uint8_t V[CHIP8_REGISTER_COUNT];

    /** Index register. */
    uint16_t I;
    /** Program counter. */
    uint16_t pc;

    /** Current opcode. */
    uint16_t opcode;

    /** The stack of the CHIP-8 virtual machine. */
    uint16_t stack[CHIP8_STACK_SIZE];

    /** Stack pointer. */
    uint8_t sp;

    /** The delay timer. */
    uint8_t delay_timer;
    /** The sound timer. */
    uint8_t sound_timer;

    /** The keypad state. */
    uint8_t keypad[16];
    /** The display buffer. */
    uint8_t display[64*32];
    /** The draw flag. */
    uint8_t draw_flag;
} Chip8;

/**
 * @brief Initializes the CHIP-8 virtual machine state.
 * 
 * This function sets the program counter to 0x200, clears the memory, registers, stack, and timers.
 * 
 * @param chip8 Emulator instance.
 */
void chip8_init(Chip8* chip8);

/**
 * @brief Loads a CHIP-8 program from a file into the virtual machine's memory.
 * 
 * This function reads the contents of the specified file and loads it into memory starting at address 0x200.
 * 
 * @param chip8 Emulator instance.
 * @param filename The path to the CHIP-8 program file.
 */
void chip8_load_program(Chip8* chip8, const char* filename);

/**
 * @brief Executes a single cycle of the CHIP-8 virtual machine.
 * 
 * This function fetches the next opcode, decodes it, and executes the corresponding instruction.
 * 
 * @param chip8 Emulator instance.
 */
void chip8_cycle(Chip8* chip8);

/**
 * @brief Updates the CHIP-8 virtual machine's timers.
 * 
 * This function decrements the delay and sound timers if they are greater than zero.
 * 
 * @param chip8 Emulator instance.
 */
void chip8_update_timers(Chip8* chip8);

#endif