#include "charoffset.h"

int get_char_offset(char offset_char, TTF_Font* font) {

  int width_char = 0;
  int height_char = 0;

  char one_char_string[2] = {0};
  one_char_string[0] = offset_char;
  one_char_string[1] = '\0';

  TTF_SizeText(font, one_char_string, &width_char, &height_char);
  return width_char;
}

int get_char_offset_by_string(char *buffer, TTF_Font* font) {

  int width_string_buffer;
  int width_string_rolled;
  int height;

  // TODO: SizeTextUTF8 seems to be the better function

  TTF_SizeText(font, buffer, &width_string_buffer, &height);
  TTF_SizeText(font, buffer + 1 , &width_string_rolled, &height);

  return (width_string_buffer - width_string_rolled);
}


