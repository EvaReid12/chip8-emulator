#include <stdio.h>
#include "chip8.h"
#include "display.h"
#include <unistd.h>  /* For usleep() */
#include <time.h>
#include "timer.h"

#define CPU_HZ 700
#define TIMER_HZ 60

int 
main(void)
{
    Chip8 chip8;
    chip8_init(&chip8);

    /* Load a CHIP-8 program into memory */
    chip8_load_program(&chip8, "../roms/Tetris.ch8");

    uint64_t last_timer_update = time_ms();

    while(1)
    {
        chip8_cycle(&chip8);

        if (chip8.draw_flag) {
            render_display(chip8.display);
            chip8.draw_flag = 0;
        }

        uint64_t now = time_ms();

        if (now - last_timer_update >= 1000 / TIMER_HZ) {
            chip8_update_timers(&chip8);
            last_timer_update = now;
        }
    }

    return 0;
}