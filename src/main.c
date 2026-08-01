#include <stdio.h>
#include "chip8.h"
#include <unistd.h>  /* For usleep() */
#include <time.h>
#include "timer.h"
#include "sdl_display.h"
#include <stdbool.h>
#include "keyboard.h"
#include "audio.h"

#define CPU_HZ 700
#define TIMER_HZ 60

int 
main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <rom.ch8>\n", argv[0]);
        return 1;
    }

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    SDLDisplay display;
    sdl_display_init(&display);

    bool running = true;

    uint64_t last_timer_update = time_ms();

    uint64_t last_cycle_time = time_ms();

    Chip8 chip8;
    chip8_init(&chip8);

    Audio audio;

    if (!audio_init(&audio)){
        printf("Audio init failed\n");
        return 1;
    }

    printf("Audio OK\n");

    chip8_load_program(&chip8, argv[1]);
    

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
                audio_destroy(&audio);
            }

            keyboard_update(&event, chip8.keypad);
        }

        uint64_t now = time_ms();
        
        while (now - last_cycle_time >= 1000 / CPU_HZ) {
            chip8_cycle(&chip8);
            last_cycle_time += 1000 / CPU_HZ; 
        }

        if (now - last_timer_update >= 1000 / TIMER_HZ) {
            chip8_update_timers(&chip8);
            last_timer_update += 1000 / TIMER_HZ; 
        }

        if (chip8.draw_flag) {
            sdl_display_render(&display, chip8.display);
            chip8.draw_flag = 0;
        }

        bool should_beep = chip8.sound_timer > 0;
        if (should_beep != audio.playing) {
            audio_set_beep(&audio, should_beep);
        }

        if (chip8.draw_flag) {
            sdl_display_render(&display, chip8.display);
            chip8.draw_flag = 0;
        }
        
        SDL_Delay(1);
    }
}