#include "gfx/graphic.hpp"

using namespace std;
using namespace exocet;

TTF_Font* Graphic::freeRoyalty = NULL;

void Graphic::openFont(TTF_Font** font, string path) {
    *font = TTF_OpenFont(path.c_str(), 20);
    if(*font == NULL) {
        cerr << "Failed to load the font from `" << path << "`: " << TTF_GetError() << endl;
    }
}

void Graphic::initTextures(Handler* handler) {
    // All fonts
    openFont(&Graphic::freeRoyalty, "res/FreeRoyalty.ttf");
}

void Graphic::renderText(int x, int y, int w, int h, std::string text, TTF_Font* font) {
    SDL_Color color = { 0xff, 0xff, 0xff };
    SDL_Rect dest = { x, y, w, h };

    SDL_Surface* text_s = TTF_RenderText_Solid(font, text.c_str(), color);

    if(text_s == NULL) {
        std::cerr << "Failed to create a surface: " << TTF_GetError() << std::endl;
        return;
    }
                
    SDL_Texture* texture = SDL_CreateTextureFromSurface(ren, text_s);

    if(texture != NULL) {
        SDL_RenderCopy(ren, texture, NULL, &dest);
    } else {
        std::cerr << "Failed to create a texture: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(text_s);
    SDL_DestroyTexture(texture);
}

void Graphic::clean() {
    // All fonts
    TTF_CloseFont(Graphic::freeRoyalty);

    SDL_DestroyRenderer(ren);
}