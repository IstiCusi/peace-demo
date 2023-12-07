#include "color.h"

const SDL_Color WHITE         = { 255 , 255 , 255 , 255 };
const SDL_Color RED           = { 255 , 0   , 0   , 255 };
const SDL_Color BORDER        = { 130 , 166 , 250 , 255 };
const SDL_Color BACKGROUND    = {   7 , 112 , 232 , 255 };

int SetRenderDrawColor(SDL_Renderer* renderer, SDL_Color color) {

  int result = SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a); return result;

}

int SetTextureColorMod(SDL_Texture *texture, SDL_Color color) {
  int fail = 0;
  if (SDL_SetTextureColorMod(texture, color.r, color.g, color.b) < 0)  fail = -1;
  if (SDL_SetTextureAlphaMod(texture, color.a) < 0) fail = -1;
  return fail;
}

void cycleColor(SDL_Color  *color) {

  static int sign = -1; // Sign also needs to static !
  static int var = 255;

  color->r = var;
  color->g = var;
  color->b = var;
  color->a = 255;

  if (var == 255) sign = -1;
  if (var == 0)   sign =  1;

  var = var + sign;

}
