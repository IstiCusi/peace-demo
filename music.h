#pragma once

#include <SDL2/SDL_mixer.h>

/**
 * @brief Initializes the SDL mixer, loads and plays a music file.
 *
 * This function performs several steps to play music using SDL_mixer. It first initializes the SDL_mixer
 * library, then opens an audio device with specified settings. If any of these steps fail, the program 
 * prints an error message and exits. 
 *
 * @return A pointer to a Mix_Music object representing the loaded music. This pointer should be passed to
 *         destroyMusic() after use to free the memory and resources.
 * 
 * @note It's important to call destroyMusic() after you're done with the music to free the resources.
 * @warning If the SDL_mixer can't initialize or the music file can't be loaded, the program will exit.
 */
Mix_Music* playMusic();

/**
 * @brief Frees the music resource and shuts down the SDL mixer.
 *
 * This function releases the memory and resources associated with the provided Mix_Music object,
 * closes the audio device opened by SDL_mixer, and then shuts down the SDL_mixer system. It should
 * be called when the program no longer needs to play music or when it is shutting down.
 *
 * @param music A pointer to the Mix_Music object to be freed. This should be the same pointer returned
 *              by playMusic().
 */
void destroyMusic(Mix_Music* music);
