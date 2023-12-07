#define FPS 400
#define SCALE 80

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <time.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>

#include "color.h"
#include "music.h"
#include "title.h"
#include "event.h"
#include "window.h"
#include "scroller.h"
#include "charoffset.h"
#include "sdl_scroller.h"
#include "water.h"
#include "frame.h"

void exitit(void);


int main() {


  atexit(exitit);

  Mix_Music  *music = playMusic();

  float winscale = SCALE;
  WindowInfo winfo = createWindow(winscale);

  Title title = titleInit(&winfo);

  Scroller scroller = scrollerInit("./assets/scrolling.txt", winfo);
  Water water = waterInit(winfo);


  // ------------------------------------ -- ------------------------------------
  // ------------------------------ GAME LOOP START -----------------------------
  // ------------------------------------ -- ------------------------------------

  const int frameDelay = 1000 / FPS;
  Uint32 frameStart;
  int frameTime;

  while (!is_game_over()) {

    frameStart = SDL_GetTicks();

    SDL_GetWindowSize(winfo.window, &winfo.window_width, &winfo.window_height); 
    SetRenderDrawColor(winfo.renderer, BACKGROUND);
    SDL_RenderClear(winfo.renderer); 

    SDL_RenderCopy(winfo.renderer, title.text, NULL, &title.rect);
    paintWater(&winfo, &water);
    scroll(winfo, &scroller); // TODO: separate scroll from paint scroll, when possible
    paintFrame(winfo);
    
    SDL_RenderPresent(winfo.renderer);

    frameTime = SDL_GetTicks() - frameStart; 
    if (frameDelay > frameTime) {
      SDL_Delay(frameDelay - frameTime);
    }

    

  }

  // ------------------------------------ -- ------------------------------------
  // ----------------------------- END OF GAME LOOP -----------------------------
  // ------------------------------------ -- ------------------------------------

destroyMusic(music);
destroyTitle(&title);
destroyScroller(&scroller);
destroyWater(&water);
destroyWindow(&winfo);

SDL_Quit();

return EXIT_SUCCESS;
}

void exitit(void) {
  SC_free();
}

