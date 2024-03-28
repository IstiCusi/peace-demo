#include "window.h"

/**
 * @brief Creates a window with specified scale.
 *
 * This function initializes SDL, creates a window with dimensions scaled according to 
 * the specified scale factor relative to screen size, and sets up the rendering environment. It also sets up 
 * various attributes of a WindowInfo structure which is returned. In case of any 
 * error during these operations, an error message is logged to stderr and the program 
 * exits with EXIT_FAILURE.
 *
 * @param winscale The scaling factor for the window dimensions as a percentage. 
 *                 For example, a value of 100 will create a window with dimensions 
 *                 equal to the display dimensions.
 * @return A WindowInfo structure containing the created window and renderer, 
 *         along with other related attributes.
 */
WindowInfo createWindow(float winscale) {

  SDL_version version = { 0 };
  SDL_DisplayMode mode;

  #ifdef DEBUG
    SDL_GetVersion (&version);
    printf("%d-%d-%d\n", version.major, version.minor, version.patch);
  #endif

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "SDL not initialized: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  if (SDL_GetCurrentDisplayMode(0, &mode) < 0) {
    fprintf(stderr, "SDL: Cannot check Display properties: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  const float scale_factor = winscale / 100.0;
  const int scaled_w = scale_factor * mode.w;
  const int scaled_h = scale_factor * mode.h;

  WindowInfo winfo = {
    .winscale = winscale,
    .rpos_scroller = 0.67,  // originally 0.55
    .rpos_mirror   = 0.79,  // originally 0.73
    .rpos_water    = 0.75,
    .rpos_title = 0.20,
    .window_width = scaled_w,
    .window_height = scaled_h,
    .borderthickness = 200 * scaled_h / 1280,
    .fontsize = 300 * scaled_h / 1280,
    .window = SDL_CreateWindow("Demo",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               scaled_w,
                               scaled_h,
                               SDL_WINDOW_INPUT_FOCUS),
  };
  if (winfo.window == NULL) {
    fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  winfo.renderer = SDL_CreateRenderer(winfo.window, USE_BEST_DRIVER, SDL_RENDERER_ACCELERATED);

  if (winfo.renderer == NULL) {
    fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  SDL_SetWindowOpacity(winfo.window, 1.0f);
  SDL_SetRenderDrawBlendMode(winfo.renderer, SDL_BLENDMODE_BLEND);

  #ifdef DEBUG
    printf("Monitor %d - %d\n", mode.w, mode.h);
    printf("Window  %d - %d\n", scaled_w, scaled_h);
  #endif

  return winfo;
}

/**
 * @brief Destroys the window and associated resources created by createWindow.
 *
 * This function releases the resources associated with the window and renderer
 * contained in the provided WindowInfo structure. 
 *
 * @param info The WindowInfo structure obtained from createWindow.
 */
void destroyWindow(WindowInfo* winfo) {
    if (winfo->renderer) {
        SDL_DestroyRenderer(winfo->renderer);
        winfo->renderer = NULL;  // Set to NULL to prevent potential use-after-free bugs
    }
    if (winfo->window) {
        SDL_DestroyWindow(winfo->window);
        winfo->window = NULL;  // Set to NULL to prevent potential use-after-free bugs
    }
}



