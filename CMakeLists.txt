cmake_minimum_required(VERSION 3.16)

project(chip8
    VERSION 1.0
    LANGUAGES C
)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(chip8
    src/main.c
    src/chip8.c
    src/instructions.c
    src/display.c
)

add_executable(tests
    tests/test_main.c
    tests/framework/test.c
    tests/test_cpu.c
    src/chip8.c
    src/instructions.c
)