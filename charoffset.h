#pragma once

#include <SDL2/SDL_ttf.h>


/**
 * @brief Calculates the width offset of a single character when rendered with
 * a specified SDL font.
 *
 * This function computes the lateral offset (in pixels) of a single character
 * within a text string, when rendered using a specified SDL TrueType font. The
 * offset represents the horizontal spacing from the beginning of the text string
 * to the right edge of the specified character.
 *
 * @param char   The character whose offset is to be calculated.
 * @param font   A pointer to the SDL_TTF font object used for rendering the text.
 *
 * @return The lateral offset (in pixels) of the specified character within the text
 *         string.
 *
 * @note In many fonts, the width offset of a character within a text string may
 * be influenced by adjacent characters. For a more accurate calculation of character
 * offsets within strings, consider using the `get_char_offset_by_string` function.
 */
int get_char_offset(char offset_char, TTF_Font* font);


/**
 * @brief Calculates the width offset of the first character within a given
 *        string when rendered with a specified SDL font.
 *
 * This function computes the lateral offset (in pixels) of the first character
 * within a given text string, when rendered using a specified SDL TrueType font.
 * The offset represents the horizontal spacing from the beginning of the text
 * string to the right edge of the specified character.
 *
 * @param buffer  The string containing the character whose offset is to be calculated.
 * @param font    A pointer to the SDL_TTF font object used for rendering the text.
 *
 * @return The lateral offset (in pixels) of the specified character within the text string.
 *
 * @note The function assumes that the character to be analyzed is the first
 * character in the string. If the character appears more than once in the string,
 * only the offset of the first occurrence is considered.
 */
int get_char_offset_by_string(char *buffer, TTF_Font* font);


