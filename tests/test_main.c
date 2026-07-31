#include "framework/test.h"
#include "test_cpu.h"

int
main(void)
{
    register_cpu_tests();

    tests_summary();

    return 0;
}