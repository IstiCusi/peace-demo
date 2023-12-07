#pragma once

#include <stdio.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL.h"

extern const SDL_Color WHITE;
extern const SDL_Color RED;
extern const SDL_Color BORDER;
extern const SDL_Color BACKGROUND;

/**
 * @brief This function wrapper allows to set the SDL render draw color not by RGB values but
 * by providing SDL_Color variable.
 *
 * @param char   Render context, where to change the color 
 * @param font   A SDL_Color variable
 *
 * @return 0 on success or a negative error code on failure; call SDL_GetError() for more information.  
 */
int SetRenderDrawColor(SDL_Renderer* renderer, SDL_Color color);

/**
 * @brief This function wrapper allows to set the SDL texture color not by RGB values but
 * by providing SDL_Color variable.
 *
 * @param char   Render context, where to change the color 
 * @param font   A SDL_Color variable
 *
 * @return 0 on success or a negative error code on failure; call SDL_GetError() for more information.  
 */
int SetTextureColorMod(SDL_Texture *texture, SDL_Color color);

/**
 * Modifies the given SDL_Color object to cycle its color values.
 *
 * This function cyclically alters the red, green, and blue components
 * of an SDL_Color object. Each call to this function will increment or
 * decrement these values, causing them to oscillate between 0 and 255.
 * The alpha component is set to 255 and remains constant.
 *
 * @param color A pointer to an SDL_Color object that will be modified. 
 *              The color components of this object are altered with each call.
 *
 * @note The function uses static variables to keep track of the current value 
 *       and the direction of change (incrementing or decrementing). Thus, 
 *       the function maintains state between calls.
 */void cycleColor(SDL_Color  *color);

