#include "title.h"

Title titleInit(WindowInfo *winfo) {

  Title title = { 0 };

  IMG_Init(IMG_INIT_PNG);
  title.surf = IMG_Load("./assets/Pro-Peace.png");
  if (title.surf ==  NULL) {
    printf("Could not load title picture\n");
    exit(EXIT_FAILURE);
  }

  float im_width = (float)(winfo->window_width - 2 * winfo->borderthickness);
  float im_scale = (float) im_width / title.surf->w;

  title.text = SDL_CreateTextureFromSurface(winfo->renderer, title.surf);
  title.rect.x=winfo->borderthickness;
  title.rect.y=winfo->rpos_title * winfo->window_height;
  title.rect.w = (int) im_width;
  title.rect.h = (int) (im_scale * title.surf->h);

  if (DEBUG == 1) {
    printf("Loaded Title Image %d - %d\n", title.surf->w, title.surf->h);
    printf("Scale: %f\n", im_scale);
  }

  return title;
}

void clearBottomScreen(WindowInfo* winfo) {

  SDL_Rect btmClearRec;
  btmClearRec.x = 0;
  btmClearRec.y = winfo->window_height / 2;
  btmClearRec.w = winfo->window_width;
  btmClearRec.h = winfo->window_height / 2;
  SetRenderDrawColor(winfo->renderer, BACKGROUND); // Background Color
  SDL_RenderFillRect(winfo->renderer, &btmClearRec);

}

void destroyTitle(Title *title) {
    if (title->surf != NULL) {
        SDL_FreeSurface(title->surf);
        title->surf = NULL;
    }
    if (title->text != NULL) {
        SDL_DestroyTexture(title->text);
        title->text = NULL;
    }
}
