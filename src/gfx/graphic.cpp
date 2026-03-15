#include "gfx/graphic.hpp"

using namespace std;
using namespace exocet;

Graphic::Graphic(Subsystem& subsys, SDL_Renderer* ren) {
    this->ren = ren;

    this->camera = make_unique<Camera>(subsys);

    color.r = 0x00;
    color.g = 0x00;
    color.b = 0x00;
    color.a = 0xFF;
}

void Graphic::renderText(int x, int y, int w, int h, string text, Font* font) {
    SDL_Rect dest = { x, y, w, h };

    SDL_Surface* text_s = TTF_RenderText_Solid(font->get(), text.c_str(), color);

    if(text_s == NULL) throw runtime_error("Failed to create a surface: " + string(TTF_GetError()));
                
    SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, text_s);

    if(texture == NULL) throw runtime_error("Failed to create a texture: " + string(SDL_GetError()));

    SDL_RenderCopy(ren, texture, NULL, &dest);
  
    SDL_FreeSurface(text_s);
    SDL_DestroyTexture(texture);
}