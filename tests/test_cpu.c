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

void
register_cpu_tests(void)
{
    RUN_TEST(test_ld_vx_byte);
}