#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "chip8.h"

/**
 * Instruction structure for opcode handling.
 * Each instruction consists of a mask, a pattern, and a function pointer.
 */
typedef struct {
    uint16_t mask;
    uint16_t pattern;

    void (*function)(Chip8*);
} Instruction;

/**
 * Instruction structure for opcode handling with a specific pattern.
 * Each instruction consists of a pattern and a function pointer.
 */
typedef struct {
    uint16_t pattern;

    void (*function)(Chip8*);
} Instruction0;

/**
 * Instruction structure for opcode handling with a specific pattern.
 * Each instruction consists of a pattern and a function pointer.
 */
typedef struct {
    uint16_t pattern;

    void (*function)(Chip8*);
} Instruction8; 

/**
 * Instruction structure for opcode handling with a specific pattern.
 * Each instruction consists of a pattern and a function pointer.
 */
typedef struct {
    uint16_t pattern;
    void (*function)(Chip8*);
} InstructionE;

/**
 * Instruction structure for opcode handling with a specific pattern.
 * Each instruction consists of a pattern and a function pointer.
 */
typedef struct {
    uint16_t pattern;
    void (*function)(Chip8*);
} InstructionF;

/**
 * Executes the opcode currently stored in the Chip8 structure.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void execute_opcode(Chip8* chip8);

/**
 * Handler for the opcode 0x0, which can represent multiple instructions.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_0(Chip8* chip8);

/**
 * Executes the opcode 0x0nnn, which is ignored in modern interpreters.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_0nnn(Chip8* chip8);

/**
 * Executes the opcode 0x00E0, which clears the display.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_00E0(Chip8* chip8);

/**
 * Executes the opcode 0x00EE, which returns from a subroutine.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_00EE(Chip8* chip8);

/**
 * Executes the opcode 0x1nnn, which jumps to address nnn.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_1nnn(Chip8* chip8);

/**
 * Executes the opcode 0x2nnn, which calls subroutine at nnn.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_2nnn(Chip8* chip8);

/**
 * Executes the opcode 0x3xkk, which skips the next instruction if Vx equals kk.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_3xkk(Chip8* chip8);

/**
 * Executes the opcode 0x4xkk, which skips the next instruction if Vx does not equal kk.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_4xkk(Chip8* chip8);

/**
 * Executes the opcode 0x5xy0, which skips the next instruction if Vx equals Vy.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_5xy0(Chip8* chip8);

/**
 * Executes the opcode 0x6xkk, which sets Vx to kk.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_6xkk(Chip8* chip8);

/**
 * Executes the opcode 0x7xkk, which adds kk to Vx.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_7xkk(Chip8* chip8);

/**
 * Executes the opcode 0x8, which can represent multiple instructions based on the last nibble.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_8(Chip8* chip8);

/**
 * Executes the opcode 0x8xy0, which sets Vx to the value of Vy.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_8xy0(Chip8* chip8);

/**
 * Executes the opcode 0x8xy1, which sets Vx to Vx OR Vy.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_8xy1(Chip8* chip8);

/**
 * Executes the opcode 0x8xy2, which sets Vx to Vx AND Vy.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_8xy2(Chip8* chip8);

/**
 * Executes the opcode 0x8xy3, which sets Vx to Vx XOR Vy.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_8xy3(Chip8* chip8);

/**
 * Executes the opcode 0x8xy4, which adds Vy to Vx and sets VF to 1 if there's a carry, 0 otherwise.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_8xy4(Chip8* chip8);

/**
 * Executes the opcode 0x8xy5, which subtracts Vy from Vx and sets VF to 1 if there's no borrow, 0 otherwise.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_8xy5(Chip8* chip8);

/**
 * Executes the opcode 0x8xy6, which shifts Vx right by 1 and stores the result in Vx.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_8xy6(Chip8* chip8);

/**
 * Executes the opcode 0x8xy7, which sets Vx to Vy minus Vx and sets VF to 1 if there's no borrow, 0 otherwise.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_8xy7(Chip8* chip8);

/**
 * Executes the opcode 0x8xyE, which shifts Vx left by 1 and stores the result in Vx.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_8xye(Chip8* chip8);

/**
 * Executes the opcode 0x9xy0, which skips the next instruction if Vx does not equal Vy.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_9xy0(Chip8* chip8);

/**
 * Executes the opcode 0xAnnn, which sets the index register I to nnn.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_annn(Chip8* chip8);

/**
 * Executes the opcode 0xBnnn, which jumps to the address nnn plus V0.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_bnnn(Chip8* chip8);

/**
 * Executes the opcode 0xCxkk, which sets Vx to a random number AND kk.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_cxkk(Chip8* chip8);

/**
 * Executes the opcode 0xDxyn, which draws a sprite at coordinate (Vx, Vy) with a width of 8 pixels and a height of n pixels.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_dxyn(Chip8* chip8);

/**
 * Executes the opcode 0xE, which can represent multiple instructions based on the last byte.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_e(Chip8* chip8);

/**
 * Executes the opcode 0xEx9E, which skips the next instruction if the key stored in Vx is pressed.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_ex9e(Chip8* chip8);

/**
 * Executes the opcode 0xExA1, which skips the next instruction if the key stored in Vx is not pressed.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_exa1(Chip8* chip8);

/**
 * Executes the opcode 0xF, which can represent multiple instructions based on the last byte.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_f(Chip8* chip8);

/**
 * Executes the opcode 0xFx07, which sets Vx to the value of the delay timer.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_fx07(Chip8* chip8);

/**
 * Executes the opcode 0xFx0A, which waits for a key press and stores the value of the key in Vx.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_fx0a(Chip8* chip8);

/**
 * Executes the opcode 0xFx15, which sets the delay timer to Vx.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_fx15(Chip8* chip8);

/**
 * Executes the opcode 0xFx18, which sets the sound timer to Vx.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_fx18(Chip8* chip8);

/**
 * Executes the opcode 0xFx1E, which adds Vx to I.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_fx1e(Chip8* chip8);

/**
 * Executes the opcode 0xFx29, which sets I to the location of the sprite for the character in Vx.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_fx29(Chip8* chip8);

/**
 * Executes the opcode 0xFx33, which stores the binary-coded decimal representation of Vx in memory locations I, I+1, and I+2.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_fx33(Chip8* chip8);

/**
 * Executes the opcode 0xFx55, which stores registers V0 through Vx in memory starting at address I.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_fx55(Chip8* chip8);

/**
 * Executes the opcode 0xFx65, which loads registers V0 through Vx from memory starting at address I.
 * 
 * @param chip8 Pointer to the Chip8 structure containing the current state of the virtual machine.
 */
void op_fx65(Chip8* chip8);

#endif