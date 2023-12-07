#include "music.h"

Mix_Music* playMusic() {
  if (Mix_Init(MIX_INIT_MOD) < 0) {
    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    exit( EXIT_FAILURE); 
  }
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    exit( EXIT_FAILURE);
  }
  Mix_Music *music = Mix_LoadMUS("./assets/drum-bass-ext.xm");
  if (!music) {
    printf("Failed to load music: SDL_mixer Error: %s\n", Mix_GetError());
    exit( EXIT_FAILURE);
  }
  Mix_PlayMusic(music, 20);
  return music;
}

void destroyMusic (Mix_Music* music) {
  Mix_FreeMusic(music);
  Mix_CloseAudio();
  Mix_Quit();
}

