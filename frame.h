#pragma once

#include "color.h"
#include "window.h"

/**
 * @brief Draws a border frame similar to the non-programmable border area seen on classic home computers like the Commodore 64.
 *
 * This function creates a border frame around the main content area of a window. The border is drawn on all four sides 
 * (top, bottom, left, right) of the window based on the specified border thickness. This simulates the non-programmable 
 * border area that was commonly found in older home computer displays, where the border area was used to frame the main 
 * display or screen content.
 *
 * @param winfo A WindowInfo structure containing information about the window, such as dimensions, border thickness, 
 *              and the SDL_Renderer to be used for drawing.
 *
 * The function uses the 'borderthickness' field from the WindowInfo structure to determine the thickness of the border 
 * and the 'window_width' and 'window_height' fields to calculate the size and positioning of the border rectangles. 
 * The 'renderer' field is used to draw these rectangles onto the window.
 */
void paintFrame(WindowInfo winfo);

