#include "gfx/graphic.hpp"

using namespace std;
using namespace exocet;

Texture* Graphic::player = nullptr;

TTF_Font* Graphic::freeRoyalty = NULL;

void Graphic::openFont(TTF_Font** font, string path) {
    *font = TTF_OpenFont(path.c_str(), 20);
    if(*font == NULL) {
        cerr << "Failed to load the font from `" << path << "`: " << TTF_GetError() << endl;
    }
}

void Graphic::initTextures(Handler* handler) {
    // All textures
    Graphic::player = new Texture(handler, ren, "res/realexocet.png");

    // All fonts
    openFont(&Graphic::freeRoyalty, "res/FreeRoyalty.ttf");
}

void Graphic::clean() {
    // All textures
    player->clean();

    // All fonts
    TTF_CloseFont(Graphic::freeRoyalty);

    SDL_DestroyRenderer(ren);
}