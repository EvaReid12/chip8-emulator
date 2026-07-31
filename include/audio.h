#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
    SDL_AudioDeviceID device;
    bool playing;
    float phase;
} Audio;

bool audio_init(Audio* audio);

void audio_destroy(Audio* audio);

void audio_set_beep(Audio* audio, bool enabled);

#endif