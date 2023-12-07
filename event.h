#pragma once

#include <stdbool.h>
#include <SDL2/SDL.h>

/**
 * @brief Checks for specific SDL events to determine if the game should end.
 *
 * This function polls SDL events and returns true if any of the following
 * conditions are met: 
 *   - The SDL_QUIT event is triggered (e.g., user closes the game window).
 *   - A mouse button is released (SDL_MOUSEBUTTONUP event).
 *   - The 'J' key is pressed on the keyboard (to return to neovim).
 *
 * These conditions are designed to provide various ways for the user to
 * signal that the game should end, such as exiting the window or performing
 * specific user inputs.
 *
 * @return A boolean value. Returns true if any of the specified events
 *         have occurred, signaling that the game should end. Otherwise,
 *         returns false.
 */
bool is_game_over(void);



