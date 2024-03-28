#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "scroller.h"

// ------------ Implementation hidden state of the Scroller library ------------

static size_t stored_width;
static size_t size;
static char *internal_buffer;
static char character_buffer;
static char *head_ref;
static int counter;

// ----------- Implementation of the fast light weight ring puffer  -----------

int SC_init (const char * const __restrict text, size_t width, char ** __restrict buf) {

  if (strlen(text) <= width) return -1; // Nothing to scroll

  counter = 0 ;
  stored_width = width;

  size = strlen(text); internal_buffer = malloc( 2 * size ); 
  if (internal_buffer == NULL) return -1; 

  memset(internal_buffer, 32, 2 * size );

  memcpy(internal_buffer, text, size);

  char *right_chunk = internal_buffer + size;
  memcpy(right_chunk, text, size);

  *buf = internal_buffer + counter;

  head_ref = internal_buffer + counter + width;
  character_buffer = *head_ref;
  *head_ref = '\0';

  return 0;
}


char SC_roll(char ** __restrict buf, bool former) {

  counter = counter % size;
  *head_ref = character_buffer;
  counter++;
  counter = counter % size;
  *buf = internal_buffer + counter;
  head_ref = internal_buffer + counter + stored_width;
  character_buffer = *head_ref;
  *head_ref = '\0';

  if (former == true ) {
    if ( counter > 0 ) {
      return *(internal_buffer+counter - 1);
    } else {
      return *(internal_buffer+size - 1);
    }
  } else {
    return *(internal_buffer + counter);
  }
}

/**
 * @brief Frees the allocated memory for the scroller.
 *
 * @return Returns 0 on success.
 */
int SC_free(void) {

  free(internal_buffer);
  internal_buffer = NULL;
  return 0;
}

/**
 * @brief Reads a text file and stores its content to be scrolled.
 *
 * @param filename The name of the file to be read.
 * @param buffer A pointer to a pointer where the file content will be stored.
 * @return Returns 0 on success.
 */

// int portable_fopen(FILE** f, const char* filename, const char* mode) {
int portable_fopen(FILE** __restrict f, const char* const __restrict filename, const char* const __restrict mode) {
#ifdef _MSC_VER
    return fopen_s(f, filename, mode);  
#else
    * f = fopen(filename, mode);
    return *f != NULL ? 0 : 1;
#endif
}

// size_t SC_read(const char* filename, char** buffer) {
size_t SC_read(const char* const __restrict filename, char** __restrict buffer) {
    FILE* stream = NULL;
    if (portable_fopen(&stream, filename, "rb") != 0 || stream == NULL) {
        return -1; 
    }

    fseek(stream, 0L, SEEK_END);
    size_t size = ftell(stream);
    fseek(stream, 0L, SEEK_SET);

    *buffer = malloc((size + 1) * sizeof(char));
    if (*buffer == NULL) {
        fclose(stream);
        return -1; 
    }

    char* ptr = *buffer; 
    int ch; 
    while ((ch = fgetc(stream)) != EOF) {
        if (ch != '\0' && ch != '\n' && ch != '\r') {
            *ptr++ = ch; 
        }
    }
    *ptr = '\0'; 

    fclose(stream);
    return 0; 
}
