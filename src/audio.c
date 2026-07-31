#include "audio.h"

#define SAMPLE_RATE 44100
#define FREQ 440.0f
#define AMPLITUDE 10000

static void
audio_callback(void* userdata, Uint8* stream, int len)
{
    Audio* audio = userdata;

    Sint16* buffer = (Sint16*) stream;

    int samples = len / sizeof(Sint16);

    for (int i = 0; i < samples; i++) {
        if (!audio -> playing) {
            buffer[i] = 0;
            continue;
        }

        buffer[i] = (audio -> phase < 0.5f) ? AMPLITUDE : -AMPLITUDE;

        audio -> phase += FREQ / SAMPLE_RATE;

        if (audio -> phase >= 1.0f) {
            audio -> phase -= 1.0f;
        }
    }
}

bool
audio_init(Audio* audio)
{
    SDL_AudioSpec desired = {0};

    desired.freq = SAMPLE_RATE;
    desired.format = AUDIO_S16SYS;
    desired.channels = 1;
    desired.samples = 1024;
    desired.callback = audio_callback;
    desired.userdata = audio;

    audio -> device = SDL_OpenAudioDevice(NULL, 0, &desired, NULL, 0);

    if (audio -> device == 0) {
        SDL_Log("Audio: %s", SDL_GetError());
        return false;
    }

    audio -> playing = false;
    audio -> phase = 0.0f;

    SDL_PauseAudioDevice(audio -> device, 0);

    return true;
}

void
audio_destroy(Audio* audio)
{
    SDL_CloseAudioDevice(audio -> device);
}

void 
audio_set_beep(Audio* audio, bool enabled)
{
    SDL_LockAudioDevice(audio->device);

    audio->playing = enabled;

    SDL_UnlockAudioDevice(audio->device);
}