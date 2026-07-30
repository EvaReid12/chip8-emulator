#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "chip8.h"

typedef struct {
    uint16_t mask;
    uint16_t pattern;

    void (*function)(Chip8*);
} Instruction;

typedef struct {
    uint16_t pattern;

    void (*function)(Chip8*);
} Instruction8; 

void execute_opcode(Chip8* chip8);

void op_00E0(Chip8* chip8);
void op_00EE(Chip8* chip8);
void op_1nnn(Chip8* chip8);
void op_2nnn(Chip8* chip8);

void op_3xkk(Chip8* chip8);
void op_4xkk(Chip8* chip8);
void op_5xy0(Chip8* chip8);
void op_6xkk(Chip8* chip8);
void op_7xkk(Chip8* chip8);

void op_8(Chip8* chip8);
void op_8xy0(Chip8* chip8);
void op_8xy1(Chip8* chip8);
void op_8xy2(Chip8* chip8);
void op_8xy3(Chip8* chip8);
void op_8xy4(Chip8* chip8);
void op_8xy5(Chip8* chip8);
void op_8xy6(Chip8* chip8);
void op_8xy7(Chip8* chip8);
void op_8xye(Chip8* chip8);

#endif