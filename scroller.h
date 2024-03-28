#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

/**
 * @brief Initializes the scroller and reserves memory on the heap.
 *
 * This function initializes the scroller by setting up a string buffer to scroll the provided text. 
 * It allocates memory on the heap for this buffer.
 *
 * @param text A C string pointing to the text to be scrolled.
 * @param width The width in characters of the string shown on screen.
 * @param buf A reference to the string buffer (char pointer) on the stack.
 *
 * @note The buffer `buf` maintains at its end the string to be displayed after each scroll.
 * 
 * @return Returns an integer status code (0 for success, non-zero for error).
 */
// int SC_init(const char *text, size_t width, char **buf);
int SC_init(const char * const __restrict text, size_t width, char ** __restrict buf);


/**
 * @brief Rolls the text one character to the left.
 *
 * This function rolls the text in the buffer one character to the left. The roll is implemented as
 * an infinite loop, giving the appearance of continuous scrolling.
 *
 * @param buffer A reference to the string buffer (char pointer) on the stack.
 * @param former A boolean flag. If `false`, returns the first character of the buffer after the roll;
 *               if `true`, returns the left character while rolling. This can be used to estimate 
 *               the pixels necessary to animate the scroll text about one character.
 *
 * @return Returns the character according to the `former` parameter.
 */
// char SC_roll(char **buffer, bool former);
char SC_roll(char ** __restrict buf, bool former);

/**
 * @brief Opens a file in a portable manner.
 *
 * TODO: Detailed description of the function.
 *
 * @param f A pointer to a FILE pointer, to store the file handle.
 * @param filename The name of the file to open.
 * @param mode The mode in which to open the file.
 *
 * @return Returns an integer status code (0 for success, non-zero for error).
 */
int portable_fopen(FILE** f, const char* filename, const char* mode);

/**
 * @brief Reads text from a file into a buffer, ignoring new line breaks.
 *
 * This function reads text from the specified file and stores it in a buffer, 
 * stripping out any new line breaks. This is useful for preparing text for the scroller.
 *
 * @param filename The filename of the text file to load.
 * @param buffer A pointer to the buffer on the stack (provide &buffer).
 *
 * @return Returns the size of the read data.
 */
// size_t SC_read(const char *filename, char  **buffer);
size_t SC_read(const char* const __restrict filename, char** __restrict buffer);

/**
 * @brief Resets the Scroller to show the result after SC_init.
 *
 * This function resets the state of the Scroller to its initial state as set by SC_init.
 *
 * @return Returns an integer status code (0 for success, non-zero for error).
 */
int SC_reset(void);

/**
 * @brief Cleans up memory used by the scroller.
 *
 * This function frees up the memory allocated by the scroller, ensuring no memory leaks.
 *
 * @return Returns an integer status code (0 for success, non-zero for error).
 */
int SC_free(void);


