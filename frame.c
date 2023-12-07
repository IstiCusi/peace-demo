#include "frame.h"

void paintFrame (WindowInfo winfo) {

  SDL_Rect up, down, left, right;

  int bt = winfo.borderthickness;
  int ww = winfo.window_width;
  int wh = winfo.window_height;
  SDL_Renderer* ren = winfo.renderer;

  up.x = 0; up.y = 0; up.h = bt; up.w = ww;
  down.x = 0; down.y = wh - bt; down.h = bt; down.w = ww;
  left.x = 0; left.y = 0; left.h = wh; left.w = bt;
  right.x = ww - bt; right.y = 0; right.h = wh; right.w = bt;

  SetRenderDrawColor(ren, BORDER);
  SDL_RenderFillRect(ren, &up);
  SDL_RenderFillRect(ren, &down);
  SDL_RenderFillRect(ren, &left);
  SDL_RenderFillRect(ren, &right);
}

