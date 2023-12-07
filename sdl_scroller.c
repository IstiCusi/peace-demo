#include "sdl_scroller.h"

#define PI 3.14159265358979323846

static double* wave = NULL;

static double* generateSinWave(int amplitude, int width, int offset, int nodes) {
    if (wave == NULL) {
        wave = (double*)malloc(width * sizeof(double));
    }
    double frequency = (double)nodes / width;
    for (int x = 0; x < width; ++x) {
        wave[x] = amplitude * sin(2 * PI * frequency * x) + offset;
    }
    return wave;
}


Scroller scrollerInit(const char* filename, const WindowInfo winfo) {

  Scroller scroller = { 0 };
  SC_read(filename, &scroller.txt);

  if (TTF_Init() < 0) { 
    fprintf(stderr, "TTF could not be initalized\n");
    exit(EXIT_FAILURE);
  }

  scroller.font = TTF_OpenFont("./assets/Font.ttf", winfo.fontsize);
  if (!scroller.font) {
    fprintf(stderr, "No Font was found\n");
    exit(EXIT_FAILURE);
  }

  SC_init(scroller.txt, 13, &scroller.buffer);

  scroller.char_width = get_char_offset_by_string(scroller.buffer, scroller.font);

  scroller.surf = TTF_RenderText_Blended(scroller.font, scroller.buffer, WHITE);
  scroller.text = SDL_CreateTextureFromSurface(winfo.renderer, scroller.surf);
  
  SDL_Color color = WHITE;
  scroller.varyingColor = color;

  wave = generateSinWave(20, 4000, 0, 5);

  return scroller;
}



void scroll(WindowInfo winfo, Scroller *scroller) {

  if (scroller->delta_x == - scroller->char_width ) {

    scroller->delta_x = 0; // TODO Do we need to start at 0 or at 1 because of following delta_x--
    scroller->left_character  = SC_roll(&scroller->buffer, false);
    scroller->char_width = get_char_offset_by_string(scroller->buffer, scroller->font);

    if (DEBUG == 1) {
      printf(">%c< of width %.3d - [%s]\n", scroller->left_character, scroller->char_width, scroller->buffer);
    }

    if (scroller->surf != NULL)  SDL_FreeSurface(scroller->surf);
    if (scroller->text != NULL)  SDL_DestroyTexture(scroller->text);

    scroller->surf = TTF_RenderText_Blended(scroller->font, scroller->buffer, WHITE);
    scroller->text = SDL_CreateTextureFromSurface(winfo.renderer, scroller->surf);

  }

  cycleColor(&scroller->varyingColor);
  SetTextureColorMod(scroller->text, scroller->varyingColor);

  SDL_SetTextureAlphaMod(scroller->text, 255);

  int width, height;
  SDL_QueryTexture(scroller->text, NULL, NULL, &width, &height);

  #if 1
    // TODO This loop needs only to go over the visual part of the texture ; saving time
    for(int x = 0; x < width; ++x) {

      SDL_Rect srcRect =  {x - scroller->delta_x, 0, 1, height};

      double frequency1 = (double)1 / winfo.window_width;
      double frequency2 = (double)5 / winfo.window_width;
      float scaleY = 1.0f + 0.40f  * sin(2 * PI * frequency1 * x - PI/2) * sin(2 * PI * frequency2 * x  -  PI/2);

      SDL_Rect destRect_S = {x,  winfo.rpos_scroller * winfo.window_height - (int)(height * scaleY/2), 1, (int)(height * scaleY) };
      SDL_SetTextureAlphaMod(scroller->text, 255);
      SDL_RenderCopyEx(winfo.renderer, scroller->text, &srcRect, &destRect_S, 0, NULL, SDL_FLIP_NONE);

      SDL_Rect destRect_M = {x,  winfo.rpos_mirror * winfo.window_height- (int)(0.5 * height * scaleY/2), 1, (int)(0.5 * height * scaleY) };
      SDL_SetTextureAlphaMod(scroller->text, 50);
      SDL_RenderCopyEx(winfo.renderer, scroller->text, &srcRect, &destRect_M , 0, NULL, SDL_FLIP_VERTICAL);

    }
  #else
    SDL_Rect text_rect;
    text_rect.x = scroller->delta_x;
    text_rect.y = winfo.rpos_scroller * winfo.window_height - (int)(height/2);
    text_rect.w = scroller->surf->w;
    text_rect.h = scroller->surf->h;
    SDL_RenderCopy(winfo.renderer, scroller->text, NULL, &text_rect);

    SDL_Rect mirror_rect;
    mirror_rect.x = scroller->delta_x;
    mirror_rect.y = winfo.rpos_mirror * winfo.window_height - (int)(0.5 * height/2);
    mirror_rect.w = scroller->surf->w * 1.0;
    mirror_rect.h = scroller->surf->h * 0.50;

    SDL_SetTextureAlphaMod(scroller->text, 50);
    SDL_RenderCopyEx(winfo.renderer, scroller->text, NULL, &mirror_rect , 0, NULL, SDL_FLIP_VERTICAL);

  #endif

// -------------------------------------------------------------------------------------------------

  scroller->delta_x--;

}

void destroyScroller(Scroller *scroller) {
    if (scroller->surf != NULL) {
        SDL_FreeSurface(scroller->surf);
        scroller->surf = NULL;
    }
    if (scroller->text != NULL) {
        SDL_DestroyTexture(scroller->text);
        scroller->text = NULL;
    }
  // TODO: Check here
  free(scroller->txt);
  TTF_CloseFont(scroller->font);

}

