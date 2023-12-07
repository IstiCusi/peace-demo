#pragma once

#include "config.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>

#define USE_BEST_DRIVER -1

typedef struct WindowInfo {

  SDL_Window* window;
  SDL_Renderer* renderer;
  float winscale;
  float rpos_title;
  float rpos_scroller;
  float rpos_mirror;
  float rpos_water;
  int window_width;
  int window_height;
  unsigned int fontsize;
  unsigned int borderthickness;

} WindowInfo;



/**
 * @brief Creates a window of shape similar of the monitor but shrinked by scale factor.
 *
 * This function initializes SDL, creates a window with dimensions scaled according to 
 * the specified scale factor relative to screen size, and sets up the rendering
 * environment. It also sets up  various attributes of a WindowInfo structure which is 
 * returned. In case of any error during these operations, an error message is logged 
 * to stderr and the program exits with EXIT_FAILURE.
 *
 * @param winscale The scaling factor for the window dimensions as a percentage. 
 *                 For example, a value of 100 will create a window with dimensions 
 *                 equal to the display dimensions.
 *
 * @return A WindowInfo structure containing the created window and renderer, 
 *         along with other related attributes.
 */
WindowInfo createWindow(float winscale);


/**
 * @brief Destroys the window and associated resources created by createWindow.
 *
 * This function releases the resources associated with the window and renderer
 * contained in the provided WindowInfo structure. 
 *
 * @param info The WindowInfo structure obtained from createWindow.
 */
void destroyWindow(WindowInfo* winfo);


