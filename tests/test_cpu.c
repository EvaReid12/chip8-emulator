#include "framework/test.h"
#include "chip8.h"
#include "instructions.h"

TEST(test_ld_vx_byte)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.opcode = 0x60AB;  /* LD V0, AB */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[0], 0xAB);

    PASS();
}

TEST(test_ld_vx_byte_with_different_register)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.opcode = 0x6FAB;  /* LD VF, AB */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[0xF], 0xAB);

    PASS();
}

TEST(test_ld_vx_byte_with_multiple_instructions)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.opcode = 0x60AB;  /* LD V0, AB */
    execute_opcode(&chip8);

    chip8.opcode = 0x6015;  /* LD V0, 15 */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[0], 0x15);

    PASS();
}

TEST(test_add_vx_byte)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[0] = 0x10;
    chip8.opcode = 0x7005;  /* ADD V0, 05 */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[0], 0x15);

    PASS();
}

TEST(test_add_vx_byte_with_overflow)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[0] = 0xFF;
    chip8.opcode = 0x7002;  /* ADD V0, 02 */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[0], 0x01);  /* Expect wrap-around due to overflow */

    PASS();
}

TEST(test_ld_vx_vy)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[1] = 0x42;  /* Set V1 to 0x42 */
    chip8.opcode = 0x8120;  /* LD V1, V2 (V1 = V2) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[1], 0x00);  /* Expect V1 to be set to the value of V2, which is 0 */

    PASS();
}

TEST(test_ld_vx_vy_with_two_filled_registers)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[1] = 0x42;  /* Set V1 to 0x42 */
    chip8.V[2] = 0x99;  /* Set V2 to 0x99 */
    chip8.opcode = 0x8120;  /* LD V1, V2 (V1 = V2) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[1], 0x99);  /* Expect V1 to be set to the value of V2, which is 0x99 */

    PASS();
}

TEST(test_ld_vx_vy_with_multiple_instructions)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[1] = 0x42;  /* Set V1 to 0x42 */
    chip8.V[2] = 0x99;  /* Set V2 to 0x99 */
    chip8.opcode = 0x8120;  /* LD V1, V2 (V1 = V2) */
    execute_opcode(&chip8);

    chip8.opcode = 0x8210;  /* LD V2, V1 (V2 = V1) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[1], 0x99);  /* Expect V1 to be set to the value of V2, which is 0x99 */
    ASSERT_EQ(chip8.V[2], 0x99);  /* Expect V2 to remain unchanged */

    PASS();
}

TEST(test_or_vx_vy)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[1] = 0x42;  /* Set V1 to 0x42 */
    chip8.V[2] = 0x99;  /* Set V2 to 0x99 */
    chip8.opcode = 0x8121;  /* OR V1, V2 (V1 = V1 | V2) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[1], (0x42 | 0x99));  /* Expect V1 to be set to the result of V1 | V2 */

    PASS();
}

TEST(test_and_vx_vy)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[1] = 0x42;  /* Set V1 to 0x42 */
    chip8.V[2] = 0x99;  /* Set V2 to 0x99 */
    chip8.opcode = 0x8122;  /* AND V1, V2 (V1 = V1 & V2) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[1], (0x42 & 0x99));  /* Expect V1 to be set to the result of V1 & V2 */

    PASS();
}

TEST(test_xor_vx_vy)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[1] = 0x42;  /* Set V1 to 0x42 */
    chip8.V[2] = 0x99;  /* Set V2 to 0x99 */
    chip8.opcode = 0x8123;  /* XOR V1, V2 (V1 = V1 ^ V2) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[1], (0x42 ^ 0x99));  /* Expect V1 to be set to the result of V1 ^ V2 */

    PASS();
}

TEST(test_add_vx_vy)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[1] = 0x10;  /* Set V1 to 0x10 */
    chip8.V[2] = 0x20;  /* Set V2 to 0x20 */
    chip8.opcode = 0x8124;  /* ADD V1, V2 (V1 = V1 + V2) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[1], (0x10 + 0x20));  /* Expect V1 to be set to the result of V1 + V2 */

    PASS();
}

TEST(test_add_vx_vy_with_overflow)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[1] = 0xFF;  /* Set V1 to 0xFF */
    chip8.V[2] = 0x02;  /* Set V2 to 0x02 */
    chip8.opcode = 0x8124;  /* ADD V1, V2 (V1 = V1 + V2) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[1], (0xFF + 0x02) & 0xFF);  /* Expect V1 to wrap around due to overflow */
    ASSERT_EQ(chip8.V[0xF], 1);  /* Expect VF to be set to 1 due to carry */

    PASS();
}

TEST(test_sub_vx_vy_when_vx_greater_than_vy)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[1] = 0x20;  /* Set V1 to 0x20 */
    chip8.V[2] = 0x10;  /* Set V2 to 0x10 */
    chip8.opcode = 0x8125;  /* SUB V1, V2 (V1 = V1 - V2) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[1], (0x20 - 0x10));  /* Expect V1 to be set to the result of V1 - V2 */
    ASSERT_EQ(chip8.V[0xF], 1);  /* Expect VF to be set to 1 since V1 > V2 */

    PASS();
}

TEST(test_sub_vx_vy_when_vx_less_than_vy)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[1] = 0x10;  /* Set V1 to 0x10 */
    chip8.V[2] = 0x20;  /* Set V2 to 0x20 */
    chip8.opcode = 0x8125;  /* SUB V1, V2 (V1 = V1 - V2) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[1], (0x10 - 0x20) & 0xFF);  /* Expect V1 to wrap around due to underflow */
    ASSERT_EQ(chip8.V[0xF], 0);  /* Expect VF to be set to 0 since V1 < V2 */

    PASS();
}

TEST(test_shr_vx)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[1] = 0x04;  /* Set V1 to 0x04 (binary: 00000100) */
    chip8.opcode = 0x8106;  /* SHR V1 (V1 = V1 >> 1) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[1], 0x02);  /* Expect V1 to be set to the result of V1 >> 1 */
    ASSERT_EQ(chip8.V[0xF], 0);   /* Expect VF to be set to the least significant bit of original V1, which is 0 */

    PASS();
}

TEST(test_shr_vx_with_least_significant_bit_set)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[1] = 0x05;  /* Set V1 to 0x05 (binary: 00000101) */
    chip8.opcode = 0x8106;  /* SHR V1 (V1 = V1 >> 1) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[1], 0x02);  /* Expect V1 to be set to the result of V1 >> 1 */
    ASSERT_EQ(chip8.V[0xF], 1);   /* Expect VF to be set to the least significant bit of original V1, which is 1 */

    PASS();
}

TEST(test_subn_vx_vy_when_vx_less_than_vy)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[1] = 0x10;  /* Set V1 to 0x10 */
    chip8.V[2] = 0x20;  /* Set V2 to 0x20 */
    chip8.opcode = 0x8127;  /* SUBN V1, V2 (V1 = V2 - V1) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[1], (0x20 - 0x10));  /* Expect V1 to be set to the result of V2 - V1 */
    ASSERT_EQ(chip8.V[0xF], 1);  /* Expect VF to be set to 1 since V2 > V1 */

    PASS();
}

TEST(test_subn_vx_vy_when_vx_greater_than_vy)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[1] = 0x20;  /* Set V1 to 0x20 */
    chip8.V[2] = 0x10;  /* Set V2 to 0x10 */
    chip8.opcode = 0x8127;  /* SUBN V1, V2 (V1 = V2 - V1) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[1], (0x10 - 0x20) & 0xFF);  /* Expect V1 to wrap around due to underflow */
    ASSERT_EQ(chip8.V[0xF], 0);  /* Expect VF to be set to 0 since V2 < V1 */

    PASS();
}

TEST(test_ld_i_adrr)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.opcode = 0xA123;  /* LD I, 0x123 */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.I, 0x123);  /* Expect I to be set to 0x123 */

    PASS();
}

TEST(test_ld_vx_dt)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.delay_timer = 0x42;  /* Set delay timer to 0x42 */
    chip8.opcode = 0xF107;  /* LD V1, DT (V1 = delay timer) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[1], 0x42);  /* Expect V1 to be set to the value of the delay timer */

    PASS();
}

TEST(test_ld_dt_vx)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[1] = 0x42;  /* Set V1 to 0x42 */
    chip8.opcode = 0xF115;  /* LD DT, V1 (delay timer = V1) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.delay_timer, 0x42);  /* Expect delay timer to be set to the value of V1 */

    PASS();
}

TEST(test_ld_st_vx)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[1] = 0x42;  /* Set V1 to 0x42 */
    chip8.opcode = 0xF118;  /* LD ST, V1 (sound timer = V1) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.sound_timer, 0x42);  /* Expect sound timer to be set to the value of V1 */

    PASS();
}

TEST(test_add_i_vx)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.I = 0x100;  /* Set I to 0x100 */
    chip8.V[1] = 0x20;  /* Set V1 to 0x20 */
    chip8.opcode = 0xF11E;  /* ADD I, V1 (I = I + V1) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.I, 0x120);  /* Expect I to be set to the result of I + V1 */

    PASS();
}

TEST(test_ld_f_vx)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[1] = 0x05;  /* Set V1 to 0x05 */
    chip8.opcode = 0xF129;  /* LD F, V1 (I = location of sprite for digit V1) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.I, 0x05 * 5);  /* Expect I to be set to the location of the sprite for digit 5 */

    PASS();
}

TEST(test_ld_b_vx)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[1] = 0xAB;  /* Set V1 to 0xAB */
    chip8.I = 0x300;    /* Set I to 0x300 */
    chip8.opcode = 0xF133;  /* LD B, V1 (Store BCD representation of V1 in memory locations I, I+1, and I+2) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.memory[0x300], 1);
    ASSERT_EQ(chip8.memory[0x301], 7);
    ASSERT_EQ(chip8.memory[0x302], 1);

    PASS();
}

TEST(test_ld_i_vx)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.V[1] = 0x42;  /* Set V1 to 0x42 */
    chip8.opcode = 0xF155;  /* LD I, V1 (I = V1) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.I, 0x42);  /* Expect I to be set to the value of V1 */

    PASS();
}

TEST(test_ld_vx_i)
{
    Chip8 chip8;
    chip8_init(&chip8);

    chip8.I = 0x300;  /* Set I to 0x300 */
    chip8.memory[0x300] = 0x42;  /* Set memory at I to 0x42 */
    chip8.opcode = 0xF165;  /* LD V1, I (V1 = memory[I]) */
    execute_opcode(&chip8);

    ASSERT_EQ(chip8.V[1], 0x42);  /* Expect V1 to be set to the value at memory location I */

    PASS();
}

void
register_cpu_tests(void)
{
    RUN_TEST(test_ld_vx_byte);
    RUN_TEST(test_ld_vx_byte_with_different_register);
    RUN_TEST(test_ld_vx_byte_with_multiple_instructions);

    RUN_TEST(test_add_vx_byte);
    RUN_TEST(test_add_vx_byte_with_overflow);

    RUN_TEST(test_ld_vx_vy);
    RUN_TEST(test_ld_vx_vy_with_two_filled_registers);
    RUN_TEST(test_ld_vx_vy_with_multiple_instructions);

    RUN_TEST(test_or_vx_vy);

    RUN_TEST(test_and_vx_vy);

    RUN_TEST(test_xor_vx_vy);

    RUN_TEST(test_add_vx_vy);
    RUN_TEST(test_add_vx_vy_with_overflow);

    RUN_TEST(test_sub_vx_vy_when_vx_greater_than_vy);
    RUN_TEST(test_sub_vx_vy_when_vx_less_than_vy);

    RUN_TEST(test_shr_vx);
    RUN_TEST(test_shr_vx_with_least_significant_bit_set);

    RUN_TEST(test_subn_vx_vy_when_vx_less_than_vy);
    RUN_TEST(test_subn_vx_vy_when_vx_greater_than_vy);

    RUN_TEST(test_ld_i_adrr);

    RUN_TEST(test_ld_vx_dt);

    RUN_TEST(test_ld_dt_vx);

    RUN_TEST(test_ld_st_vx);

    RUN_TEST(test_add_i_vx);

    RUN_TEST(test_ld_f_vx);

    RUN_TEST(test_ld_b_vx);

    RUN_TEST(test_ld_i_vx);

    RUN_TEST(test_ld_vx_i);
}