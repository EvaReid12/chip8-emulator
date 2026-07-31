#include <stdio.h>
#include "chip8.h"
#include "display.h"
#include <unistd.h>  /* For usleep() */

int 
main(void)
{
    Chip8 chip8;
    chip8_init(&chip8);

    /* Load a CHIP-8 program into memory */
    chip8_load_program(&chip8, "../roms/IBM_Logo.ch8");

    while(1)
    {
        chip8_cycle(&chip8);


        if(chip8.draw_flag)
        {
            printf("\033[H\033[2J"); // clear terminal

            render_display(chip8.display);

            chip8.draw_flag = 0;
        }


        usleep(1200);
    }

    return 0;
}