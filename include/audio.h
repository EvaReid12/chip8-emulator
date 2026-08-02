#ifndef AUDIO_H
#define AUDIO_H

#include <SDL2/SDL.h>
#include <stdbool.h>

/**
 * @brief Audio state for the CHIP-8 emulator.
 */
typedef struct {

    /** The SDL audio device ID. */
    SDL_AudioDeviceID device;
    /** Whether the audio is currently playing. */
    bool playing;
    /** The phase of the audio signal. */
    float phase;
} Audio;

/**
 * @brief Initializes the audio subsystem for the CHIP-8 emulator.
 * 
 * This function sets up the SDL audio device with the desired specifications and starts audio playback.
 * 
 * @param audio Pointer to the Audio structure to initialize.
 * @return true if the audio subsystem was successfully initialized, false otherwise.
 */
bool audio_init(Audio* audio);

/**
 * @brief Cleans up the audio subsystem for the CHIP-8 emulator.
 * 
 * This function closes the SDL audio device and releases any associated resources.
 * 
 * @param audio Pointer to the Audio structure to clean up.
 */
void audio_destroy(Audio* audio);

/** 
 * @brief Enables or disables the beep sound in the CHIP-8 emulator.
 *
 * This function locks the audio device, sets the playing state, and unlocks the device.
 * 
 * @param audio Pointer to the Audio structure.
 * @param enabled true to enable the beep sound, false to disable it.
 * @note This function is thread-safe and can be called from different threads
 */
void audio_set_beep(Audio* audio, bool enabled);

#endif