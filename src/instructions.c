#include "instructions.h"
#include <string.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "display.h"

static Instruction instructions[] = {
    {0xFFFF, 0x0000, op_00E0},  /* Clear the display */
    {0xFFFF, 0x00EE, op_00EE},  /* Return from subroutine */
    {0xF000, 0x1000, op_1nnn},  /* Jump to address NNN */
    {0xF000, 0x2000, op_2nnn},  /* Call subroutine at NNN */
    {0xF000, 0x3000, op_3xkk},  /* Skip next instruction if Vx == kk */
    {0xF000, 0x4000, op_4xkk},  /* Skip next instruction if Vx != kk */
    {0xF000, 0x5000, op_5xy0},  /* Skip next instruction if Vx == Vy */
    {0xF000, 0x6000, op_6xkk},  /* Set Vx = kk */
    {0xF000, 0x7000, op_7xkk},  /* Set Vx = Vx + kk */
    {0xF000, 0x8000, op_8},
    {0xF000, 0x9000, op_9xy0},  /* Skip next instruction if Vx != Vy */
    {0xF000, 0xA000, op_annn},  /* Set I = NNN */
    {0xF000, 0xB000, op_bnnn},  /* Jump to address NNN + V0 */
    {0xF000, 0xC000, op_cxkk},  /* Set Vx = random number AND kk */
    {0xF000, 0xD000, op_dxyn},  /* Display n-byte sprite at (Vx, Vy), set VF = collision */
    {0xF000, 0xE000, op_e},
    {0xF000, 0xF000, op_f},
};

static Instruction8 instructions8[] = {
    {0x0, op_8xy0},  /* Set Vx = Vy */
    {0x1, op_8xy1},  /* Set Vx = Vx OR Vy */
    {0x2, op_8xy2},  /* Set Vx = Vx AND Vy */
    {0x3, op_8xy3},  /* Set Vx = Vx XOR Vy */
    {0x4, op_8xy4},  /* Set Vx = Vx ADD Vy, set VF = carry */
    {0x5, op_8xy5},  /* Set Vx = Vx SUB Vy, set VF = NOT borrow */
    {0x6, op_8xy6},  /* Set Vx = Vx SHR 1*/
    {0x7, op_8xy7},  /* Set Vx = Vy - Vx, set VF = NOT borrow */
    {0xE, op_8xye},  /* Set Vx = Vx SHL 1 */
};

static InstructionE instructionsE[] = {
    {0x9E, op_ex9e},  /* Skip next instruction if key with the value of Vx is pressed */
    {0xA1, op_exa1},  /* Skip next instruction if key with the value of Vx is not pressed */
};

static InstructionF instructionsF[] = {
    {0x07, op_fx07},  /* Set Vx = delay timer */  
    {0x0A, op_fx0a},  /* Wait for a key press, store the value of the key in Vx */
    {0x15, op_fx15},  /* Set delay timer = Vx*/
    {0x18, op_fx18},  /* Set sound timer = Vx */
    {0x1E, op_fx1e},  /* Set I = I + Vx */
    {0x29, op_fx29},  /* Set I = location of sprite for digit Vx */
    {0x33, op_fx33},  /* Store BCD representation of Vx in memory locations I, I+1, and I+2 */
    {0x55, op_fx55},  /* Store registers V0 through Vx in memory starting at location I */
    {0x65, op_fx65},  /* Read registers V0 through Vx from memory starting at location I */
};

static uint16_t 
get_nnn(uint16_t opcode) 
{
    return opcode & 0x0FFF;
}

static uint8_t 
get_n(uint16_t opcode) 
{
    return opcode & 0x000F;
}

static uint8_t 
get_x(uint16_t opcode) 
{
    return (opcode & 0x0F00) >> 8;
}

static uint8_t 
get_y(uint16_t opcode) 
{
    return (opcode & 0x00F0) >> 4;
}

static uint8_t 
get_kk(uint16_t opcode) 
{
    return opcode & 0x00FF;
}


void 
op_00E0(Chip8* chip8) 
{
    clear_display(chip8 -> display);
    chip8 -> draw_flag = 1;
}

void 
op_00EE(Chip8* chip8) 
{
    chip8 -> sp--;
    chip8 -> pc = chip8 -> stack[chip8 -> sp];
}

void 
op_1nnn(Chip8* chip8) 
{
    uint16_t nnn = get_nnn(chip8 -> opcode);
    chip8 -> pc = nnn;
}

void 
op_2nnn(Chip8* chip8) 
{
    uint16_t nnn = get_nnn(chip8 -> opcode);
    chip8 -> stack[chip8 -> sp] = chip8 -> pc;
    chip8 -> sp++;
    chip8 -> pc = nnn;
}

void 
op_3xkk(Chip8* chip8) 
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t kk = get_kk(chip8 -> opcode);

    if (chip8 -> V[x] == kk) {
        chip8 -> pc += 2;  /* Skip the next instruction */
    }
}

void 
op_4xkk(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t kk = get_kk(chip8 -> opcode);

    if (chip8 -> V[x] != kk) {
        chip8 -> pc += 2;  /* Skip the next instruction */
    }
}

void 
op_5xy0(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t y = get_y(chip8 -> opcode);

    if (chip8 -> V[x] == chip8 -> V[y]) {
        chip8 -> pc += 2;  /* Skip the next instruction */
    }
}

void 
op_6xkk(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t kk = get_kk(chip8 -> opcode);

    chip8 -> V[x] = kk;
}

void 
op_7xkk(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t kk = get_kk(chip8 -> opcode);

    chip8 -> V[x] = chip8 -> V[x] + kk;
}

void 
op_8(Chip8* chip8)
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

void 
op_8xy0(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t y = get_y(chip8 -> opcode);

    chip8 -> V[x] = chip8 -> V[y];
}

void 
op_8xy1(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t y = get_y(chip8 -> opcode);

    chip8 -> V[x] = chip8 -> V[x] | chip8 -> V[y];
}

void 
op_8xy2(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t y = get_y(chip8 -> opcode);

    chip8 -> V[x] = chip8 -> V[x] & chip8 -> V[y];
}

void 
op_8xy3(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t y = get_y(chip8 -> opcode);

    chip8 -> V[x] = chip8 -> V[x] ^ chip8 -> V[y];
}

void 
op_8xy4(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t y = get_y(chip8 -> opcode);

    uint16_t sum = chip8 -> V[x] + chip8 -> V[y];
    chip8 -> V[0xF] = (sum > 0xFF) ? 1 : 0;  /* Set VF = carry */
    chip8 -> V[x] = sum & 0xFF;  /* Store the least significant byte in Vx */
}

void 
op_8xy5(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t y = get_y(chip8 -> opcode);

    chip8 -> V[0xF] = (chip8 -> V[x] > chip8 -> V[y]) ? 1 : 0;  /* Set VF = NOT borrow */
    chip8 -> V[x] = chip8 -> V[x] - chip8 -> V[y];
}

void 
op_8xy6(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);

    chip8 -> V[0xF] = chip8 -> V[x] & 0x1;  /* Set VF = least significant bit of Vx before the shift */
    chip8 -> V[x] >>= 1;  /* Shift Vx right by 1 */
}

void 
op_8xy7(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t y = get_y(chip8 -> opcode);

    chip8 -> V[0xF] = (chip8 -> V[y] > chip8 -> V[x]) ? 1 : 0;  /* Set VF = NOT borrow */
    chip8 -> V[x] = chip8 -> V[y] - chip8 -> V[x];
}

void 
op_8xye(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);

    chip8 -> V[0xF] = (chip8 -> V[x] & 0x80) >> 7;  /* Set VF = most significant bit of Vx before the shift */
    chip8 -> V[x] <<= 1;  /* Shift Vx left by 1 */
}

void 
op_9xy0(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t y = get_y(chip8 -> opcode);

    if (chip8 -> V[x] != chip8 -> V[y]) {
        chip8 -> pc += 2;  /* Skip the next instruction */
    }
}

void 
op_annn(Chip8* chip8)
{
    chip8 -> I = get_nnn(chip8 -> opcode);
}

void 
op_bnnn(Chip8* chip8)
{
    uint8_t nnn = get_nnn(chip8 -> opcode);

    chip8 -> pc = nnn + chip8 -> V[0];  /* Jump to address NNN + V0 */
}

void 
op_cxkk(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t kk = get_kk(chip8 -> opcode);

    uint8_t random_value = rand() % 256;  /* Generate a random number between 0 and 255 */
    chip8 -> V[x] = random_value & kk;  /* Set Vx = random number AND kk */
}

void 
op_dxyn(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t y = get_y(chip8 -> opcode);
    uint8_t n = get_n(chip8 -> opcode);

    uint8_t Vx = chip8 -> V[x];
    uint8_t Vy = chip8 -> V[y];

    chip8 -> V[0xF] = 0;  /* Reset the carry flag */

    for (uint8_t row = 0; row < n; row++) {
        uint8_t sprite_byte = chip8 -> memory[chip8 -> I + row];

        for (uint8_t col = 0; col < 8; col++) {
            if ((sprite_byte & (0x80 >> col)) != 0) {  /* Check if the pixel is set */
                uint16_t display_index = ((Vy + row) % 32) * 64 + ((Vx + col) % 64);

                if (chip8 -> display[display_index] == 1) {
                    chip8 -> V[0xF] = 1;  /* Set the carry flag if a pixel is turned off */
                }

                chip8 -> display[display_index] ^= 1;  /* XOR the pixel value */
            }
        }
    }
}

void 
op_e(Chip8* chip8)
{
    uint8_t id = get_kk(chip8 -> opcode);

    for (size_t i = 0; i < sizeof(instructionsE) / sizeof(InstructionE); i++) {
        InstructionE instruction = instructionsE[i];

        if (id == instruction.pattern) {
            instruction.function(chip8);
            return;
        }
    }
}

void 
op_ex9e(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t key = chip8 -> V[x];

    if (chip8 -> keypad[key] != 0) {
        chip8 -> pc += 2;  /* Skip the next instruction */
    }
}

void 
op_exa1(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t key = chip8 -> V[x];

    if (chip8 -> keypad[key] == 0) {
        chip8 -> pc += 2;  /* Skip the next instruction */
    }
}

void 
op_f(Chip8* chip8)
{
    uint8_t id = get_kk(chip8 -> opcode);

    for (size_t i = 0; i < sizeof(instructionsF) / sizeof(InstructionF); i++) {
        InstructionF instruction = instructionsF[i];

        if (id == instruction.pattern) {
            instruction.function(chip8);
            return;
        }
    }
}

void 
op_fx07(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);

    chip8 -> V[x] = chip8 -> delay_timer;
}

void 
op_fx0a(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);

    for (uint8_t key = 0; key < 16; key++) {
        if (chip8 -> keypad[key] != 0) {
            chip8 -> V[x] = key;  /* Store the value of the key in Vx */
            return;
        }
    }
}

void 
op_fx15(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);

    chip8 -> delay_timer = chip8 -> V[x];
}

void 
op_fx18(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);

    chip8 -> sound_timer = chip8 -> V[x];
}

void 
op_fx1e(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);

    chip8 -> I = chip8 -> I + chip8 -> V[x];
}

void 
op_fx29(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t digit = chip8 -> V[x];

    /* Each digit's sprite is 5 bytes long, starting at memory location 0x000 */
    chip8 -> I = digit * 5;
}

void 
op_fx33(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);
    uint8_t value = chip8 -> V[x];

    /* Store the hundreds, tens, and units digits of Vx in memory locations I, I+1, and I+2 */
    chip8 -> memory[chip8 -> I] = value / 100;          /* Hundreds digit */
    chip8 -> memory[chip8 -> I + 1] = (value / 10) % 10;   /* Tens digit */
    chip8 -> memory[chip8 -> I + 2] = value % 10;          /* Units digit */
}

void 
op_fx55(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);

    for (uint8_t i = 0; i <= x; i++) {
        chip8 -> memory[chip8 -> I + i] = chip8 -> V[i];
    }
}

void 
op_fx65(Chip8* chip8)
{
    uint8_t x = get_x(chip8 -> opcode);

    for (uint8_t i = 0; i <= x; i++) {
        chip8 -> V[i] = chip8 -> memory[chip8 -> I + i];
    }
}

void 
execute_opcode(Chip8* chip8) 
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