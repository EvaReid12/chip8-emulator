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

typedef struct {
    uint16_t pattern;
    void (*function)(Chip8*);
} InstructionE;

typedef struct {
    uint16_t pattern;
    void (*function)(Chip8*);
} InstructionF;

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

void op_9xy0(Chip8* chip8);
void op_a000(Chip8* chip8);
void op_bnnn(Chip8* chip8);
void op_cxkk(Chip8* chip8);
void op_dxyn(Chip8* chip8);

void op_e(Chip8* chip8);
void op_ex9e(Chip8* chip8);
void op_exa1(Chip8* chip8);

void op_f(Chip8* chip8);
void op_fx07(Chip8* chip8);
void op_fx0a(Chip8* chip8);
void op_fx15(Chip8* chip8);
void op_fx18(Chip8* chip8);
void op_fx1e(Chip8* chip8);
void op_fx29(Chip8* chip8);
void op_fx33(Chip8* chip8);
void op_fx55(Chip8* chip8);
void op_fx65(Chip8* chip8);

#endif