#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "scroller.h"

#define WIDTH 8

int main() {

    char *buffer = NULL;
    char *text = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char carry = { 0 };

    SC_init(text, WIDTH, &buffer);

    printf("%3d -- %3p - %s\n", 0, buffer, buffer);
    
    for (int i = 1 ; i < 80 ; i++) {
      carry = SC_roll(&buffer, false);
      printf("%3d -- %3p - %c - %s\n", i, buffer, carry, buffer);
    }

    SC_free();
    return EXIT_SUCCESS;
}
