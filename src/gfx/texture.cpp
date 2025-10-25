#include "gfx/texture.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

Texture::Texture(Handler* han, string path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    
    setHandler(han);

    if(surface == NULL) {
        clog << "Failed to load the texture from `" << path << "`: " << IMG_GetError() << endl;
        return;
    }

    w = surface->w;
    h = surface->h;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(handler->getSubsystem()->getRenderer(), surface);
    SDL_FreeSurface(surface);

    if(texture == NULL) {
        clog << "Failed to create the texture from `" << path << "`: " << SDL_GetError() << endl;
    }

    tex = texture;
}

void Texture::render(Vector2D<int> pos, int w, int h) {
    renderAnchor(pos - handler->getGraphic()->getCamera()->getPosition(), w, h);
}

void Texture::renderAnchor(Vector2D<int> pos, int w, int h) {
    SDL_Rect src = { x, y, this->w, this->h };
    SDL_Rect dest = { 
        pos.x, 
        pos.y, 
        w, h 
    };

    SDL_RenderCopy(handler->getSubsystem()->getRenderer(), tex, &src, &dest);
}