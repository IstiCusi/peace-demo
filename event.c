#include "event.h"


bool is_game_over(void) {

  SDL_Event event;
  bool over = false; 
  
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_QUIT:
        over = true;
        break;
      case SDL_MOUSEBUTTONUP:
        over = true;
        break;
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_j) { // back to neovim
          over = true;
        }
        break;

    }
  }
  return over;
}

