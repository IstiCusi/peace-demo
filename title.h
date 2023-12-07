#pragma once

#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "color.h"
#include "window.h"

typedef struct Title {
  SDL_Surface *surf;
  SDL_Texture *text;
  SDL_Rect rect;
} Title;


/**
 * @brief Initializes a Title structure based on the provided WindowInfo.
 *
 * @param winfo Pointer to a WindowInfo structure containing window and renderer information.
 * @return A Title structure on success. Exits the program with EXIT_FAILURE on failure.
 */
Title titleInit(WindowInfo *winfo);

/**
 * @brief Clears the bottom half of the screen.
 *
 * This function is designed to clear the bottom half of the screen by drawing a rectangle
 * with the background color over it. It calculates the rectangle's dimensions based on the
 * window's width and height.
 *
 * @param winfo A pointer to a WindowInfo structure containing information about the window,
 *              including its dimensions and the renderer.
 *
 * @note The function sets the drawing color to the background color and then fills the bottom
 *       half of the screen with this color.
 *
 * @warning Currently, this function is not being used in the application because clearing only 
 *          half of the screen has proven to be unreliable under certain environments, such as 
 *          running in a VMware virtual machine.
 */
void clearBottomScreen(WindowInfo* winfo);

/**
 * @brief Destroys the resources associated with a Title object.
 * 
 * This function releases the surface and texture resources of a 
 * Title object to prevent memory leaks.
 *
 * @param title The Title object whose resources are to be released.
 */
void destroyTitle(Title *title);

