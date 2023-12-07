#include "water.h"


Water waterInit(const WindowInfo winfo) {

  Water water = { 0 };
  water.surf = IMG_Load("./assets/water.png");
  water.text = SDL_CreateTextureFromSurface(winfo.renderer, water.surf);
  water.rect.x = 0;
  water.rect.y = winfo.rpos_water * winfo.window_height;
  water.rect.w = winfo.window_width;
  water.rect.h = (int) (winfo.window_height * (1-winfo.rpos_water));
  return water;

}

void paintWater(WindowInfo *winfo, Water *water) {

    SDL_SetTextureAlphaMod(water->text, 150);
    SDL_RenderCopy(winfo->renderer, water->text, NULL, &water->rect);

}

/**
 * @brief Destroys the resources associated with a Water object.
 * 
 * This function releases the surface and texture resources of a 
 * Water object to prevent memory leaks.
 *
 * @param water The Water object whose resources are to be released.
 */
void destroyWater(Water *water) {
    if (water->surf != NULL) {
        SDL_FreeSurface(water->surf);
        water->surf = NULL;
    }
    if (water->text != NULL) {
        SDL_DestroyTexture(water->text);
        water->text = NULL;
    }
}
