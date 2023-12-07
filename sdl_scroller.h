#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "window.h"
#include "scroller.h"
#include "charoffset.h"
#include "color.h"


typedef struct Scroller {
  char* txt;
  char* buffer;
  TTF_Font* font;
  SDL_Color varyingColor;
  SDL_Surface *surf;
  SDL_Texture *text;
  char left_character;
  int delta_x;
  int char_width;

} Scroller;

/**
 * @brief Initializes a Scroller structure with the given filename and window information.
 *
 * This function creates and initializes a Scroller structure for text scrolling. It reads the text
 * from the specified file, initializes SDL TTF for font rendering, and sets up the necessary
 * resources for text scrolling, including loading a font, initializing the scroller buffer, and
 * creating the text texture.
 *
 * @param filename A string representing the path to the file containing the text to scroll.
 * @param winfo A WindowInfo structure containing information about the window, such as the renderer 
 *              and font size.
 *
 * @note The function performs several critical operations:
 *       - Reads the text from the file.
 *       - Initializes SDL TTF and opens a specified font.
 *       - Sets up the scroller buffer and calculates the width of characters.
 *       - Renders the text to a surface, then creates a texture from it.
 *       - Initializes a sine wave for varying color effects.
 * 
 * @warning If TTF initialization, font loading, or any other critical step fails, the program will 
 *          print an error message and exit.
 * 
 * @return Returns a Scroller structure, initialized with the provided text and window information.
 */
Scroller scrollerInit(const char* filename, const WindowInfo winfo);

/**
 * @brief Scrolls text across the screen with visual effects.
 *
 * This function is responsible for creating a scrolling text effect on the screen, using the Scroller
 * structure for managing the text and its properties. It handles text movement, color cycling, and
 * rendering the scrolled text with various visual effects.
 *
 * @param winfo A WindowInfo structure containing information about the window, such as the renderer.
 * @param scroller A pointer to a Scroller structure containing text and properties for scrolling.
 *
 * The function performs the following operations:
 *  - Checks if the text needs to roll over and updates the buffer and texture accordingly.
 *  - Applies color cycling to the text for visual effects.
 *  - Renders the text to the screen with a sine wave distortion and a mirrored effect.
 *  - Handles text movement by adjusting the delta_x property of the Scroller structure.
 *
 * @note The function uses `SDL_RenderCopyEx` for rendering the text with effects and handles both 
 *       the main scrolling text and its mirrored counterpart.
 *
 * @warning This function assumes that the Scroller and WindowInfo structures are properly initialized 
 *          and contain valid data.
 */
void scroll(WindowInfo winfo, Scroller *scroller);

/**
 * @brief Destroys the resources associated with a Scroller object.
 * 
 * This function releases the surface and texture resources of a 
 * Scroller object to prevent memory leaks.
 *
 * @param scroller The Scroller object whose resources are to be released.
 */
void destroyScroller(Scroller *scroller);




