#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "config.h"
#include "window.h"

typedef struct Water {
  SDL_Surface *surf;
  SDL_Texture *text;
  SDL_Rect     rect;
} Water;

Water waterInit(const WindowInfo winfo);
void paintWater(WindowInfo *winfo, Water *water);
void destroyWater(Water *water);

