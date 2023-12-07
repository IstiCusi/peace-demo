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

/**
 * @brief Initializes the scroller with the given text and width.
 *
 * @param text The text to be scrolled.
 * @param width The width of the scrolling area.
 * @param buf A pointer to a pointer where the initial buffer will be stored.
 * @return Returns 0 on success, -1 if the length of text is less than or equal to width.
 */
int SC_init (const char *text, size_t width, char **buf) {

  if (strlen(text) <= width) return -1; // Nothing to scroll

  counter = 0 ;
  stored_width = width;

  size = strlen(text);

  internal_buffer = malloc( 2 * size );
  if (internal_buffer == NULL) {
    return -1;  // Memory allocation failed
  }

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

/**
 * @brief Rolls the scroller one character to the left or right.
 *
 * @param buf A pointer to a pointer where the updated buffer will be stored.
 * @param former Indicates whether to roll to the left (true) or right (false).
 * @return Returns the character that was rolled off.
 */
char SC_roll(char **buf, bool former) {

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

int portable_fopen(FILE** f, const char* filename, const char* mode) {
#ifdef _MSC_VER
    return fopen_s(f, filename, mode);  // Für MSVC, verwenden Sie fopen_s
#else
    * f = fopen(filename, mode);         // Für andere Compiler, verwenden Sie fopen
    return *f != NULL ? 0 : 1;
#endif
}

size_t SC_read(const char* filename, char** buffer) {
    FILE* stream = NULL;
    // Verwende die portable_fopen-Funktion
    if (portable_fopen(&stream, filename, "rb") != 0 || stream == NULL) {
        return -1; // Fehler beim Öffnen der Datei
    }

    // Gehe ans Ende der Datei, um die Größe zu bestimmen
    fseek(stream, 0L, SEEK_END);
    size_t size = ftell(stream);
    fseek(stream, 0L, SEEK_SET);

    // Reserviere Speicher für den Inhalt der Datei plus das Nullzeichen
    *buffer = malloc((size + 1) * sizeof(char));
    if (*buffer == NULL) {
        fclose(stream);
        return -1; // Fehler bei der Speicherreservierung
    }

    char* ptr = *buffer; // Zeiger auf die aktuelle Position im Puffer
    int ch; // Variable zum Speichern des gelesenen Zeichens
    while ((ch = fgetc(stream)) != EOF) {
        // Überspringe Nullzeichen und Zeilenumbrüche
        if (ch != '\0' && ch != '\n' && ch != '\r') {
            *ptr++ = ch; // Füge das Zeichen zum Puffer hinzu und bewege den Zeiger
        }
    }
    *ptr = '\0'; // Füge das abschließende Nullzeichen hinzu

    fclose(stream);
    return 0; // Erfolg
}
