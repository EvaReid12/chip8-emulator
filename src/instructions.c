#include "instructions.h"instructions
#include <string.h>
#include <stdio.h>
#include <stddef.h>

static Instruction instructions[] = {
    {0xF000, 0x0000, op_00E0},  /* Clear the display */
    {0xF000, 0x00EE, op_00EE},  /* Return from subroutine */
    {0xF000, 0x1000, op_1nnn},  /* Jump to address NNN */
    {0xF000, 0x2000, op_2nnn},  /* Call subroutine at NNN */
    {0xF000, 0x3000, op_3xkk},  /* Skip next instruction if Vx == kk */
    {0xF000, 0x4000, op_4xkk},  /* Skip next instruction if Vx != kk */
    {0xF000, 0x5000, op_5xy0},  /* Skip next instruction if Vx == Vy */
    {0xF000, 0x6000, op_6xkk},  /* Set Vx = kk */
    {0xF000, 0x7000, op_7xkk},  /* Set Vx = Vx + kk */
    {0xF000, 0x8000, op_8}
};

static Instruction8 instructions8[] = {
    {0x0, op_8xy0},
    {0x1, op_8xy1},
    {0x2, op_8xy2},
    {0x3, op_8xy3},
    {0x4, op_8xy4},
    {0x5, op_8xy5},
    {0x6, op_8xy6},
    {0x7, op_8xy7},
    {0xE, op_8xye},
};

static uint8_t get_nnn(uint16_t opcode) 
{
    return opcode & 0x0FFF;
}

static uint8_t get_n(uint16_t opcode) 
{
    return opcode & 0x000F;
}

static uint8_t get_x(uint16_t opcode) 
{
    return (opcode & 0x0F00) >> 8;
}

static uint8_t get_y(uint16_t opcode) 
{
    return (opcode & 0x00F0) >> 4;
}

static uint8_t get_kk(uint16_t opcode) 
{
    return opcode & 0x00FF;
}


void op_00E0(Chip8* chip8) 
{
    memset(chip8 -> display, 0, sizeof(chip8 -> display));
    chip8 -> draw_flag = 1;
}

void op_00EE(Chip8* chip8) 
{
    chip8 -> sp--;
    chip8 -> pc = chip8 -> stack[chip8 -> sp];
}

void op_1nnn(Chip8* chip8) 
{
    uint16_t nnn = get_nnn(chip8 -> opcode);
    chip8 -> pc = nnn;
}

void op_2nnn(Chip8* chip8) 
{
    uint16_t nnn = get_nnn(chip8 -> opcode);
    chip8 -> stack[chip8 -> sp] = chip8 -> pc;
    chip8 -> sp++;
    chip8 -> pc = nnn;
}

void op_3xkk(Chip8* chip8) 
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t kk = get_kk(chip8 -> opcode);

    if (chip8 -> V[x] == kk) {
        chip8 -> pc += 2;  /* Skip the next instruction */
    }
}

void op_4xkk(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t kk = get_kk(chip8 -> opcode);

    if (chip8 -> V[x] != kk) {
        chip8 -> pc += 2;  /* Skip the next instruction */
    }
}

void op_5xy0(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t y = get_y(chip8 -> opcode);

    if (chip8 -> V[x] == chip8 -> V[y]) {
        chip8 -> pc += 2;  /* Skip the next instruction */
    }
}

void op_6xkk(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t kk = get_kk(chip8 -> opcode);

    chip8 -> V[x] = kk;
}

void op_7xkk(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t kk = get_kk(chip8 -> opcode);

    chip8 -> V[x] = chip8 -> V[x] + kk;
}

void op_8(Chip8* chip8)
{
    uint8_t id = get_n(chip8 -> opcode);

    for (size_t i = 0; i < sizeof(instructions8) / sizeof(Instruction8); i++) {
        Instruction8 instruction = instructions8[i];

        if (id == instruction.pattern) {
            instruction.function(chip8);
            return;
        }
    }
}


void execute_opcode(Chip8* chip8) 
{
    size_t instruction_count = sizeof(instructions) / sizeof(Instruction);

    for (size_t i = 0; i < instruction_count; i++) {
        Instruction instruction = instructions[i];

        if ((chip8 -> opcode & instruction.mask) == instruction.pattern) {
            instruction.function(chip8);
            return;
        }
    }

    fprintf(stderr, "Unknown opcode: 0x%X\n", chip8 -> opcode);
}