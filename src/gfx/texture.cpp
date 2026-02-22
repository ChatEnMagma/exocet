#include "gfx/texture.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

Texture::Texture(Handler* handler, const string& path) {
    this->handler = handler;

    openTexture(path);
}

void Texture::openTexture(const string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());

    if(surface == NULL) throw runtime_error("Failed to load the texture from `" + path + "`: " + IMG_GetError());

    this->h = surface->h;
    this->w = surface->w;

    tex = SDL_CreateTextureFromSurface(handler->getSubsystem()->getRenderer(), surface);
    SDL_FreeSurface(surface);

    if(tex == NULL) throw runtime_error("Failed to create the texture from `" + path + "`: " + SDL_GetError());
  
    cout << "Success open the texture from `" << path << "`..." << endl;
}

void Texture::render(const IntVector2D& position, int wdest, int hdest, int xsrc, int ysrc, int wsrc, int hsrc) noexcept {
    renderAnchor(
        position - handler->getGraphic()->getCamera()->getPosition(),
        wdest,
        hdest,
        xsrc,
        ysrc,
        wsrc,
        hsrc
    );
}

void Texture::renderAnchor(const IntVector2D& position, int wdest, int hdest, int xsrc, int ysrc, int wsrc, int hsrc) noexcept {
    SDL_Rect src = { xsrc, ysrc, wsrc, hsrc };
    SDL_Rect dest = { position.x, position.y, wdest, hdest };

    SDL_RenderCopy(handler->getSubsystem()->getRenderer(), tex, &src, &dest);
}

void Texture::renderAnchorAngle(const IntVector2D& position, double angle, int wdest, int hdest, int xsrc, int ysrc, int wsrc, int hsrc) noexcept {
    SDL_Rect src = { xsrc, ysrc, wsrc, hsrc };
    SDL_Rect dest = { position.x, position.y, wdest, hdest };

    SDL_RenderCopyEx(handler->getSubsystem()->getRenderer(), tex, &src, &dest, angle, NULL, SDL_FLIP_NONE);
}

void Texture::renderAngle(const IntVector2D& position, double angle, int wdest, int hdest, int xsrc, int ysrc, int wsrc, int hsrc) noexcept {
    renderAnchorAngle(
        position - handler->getGraphic()->getCamera()->getPosition(),
        angle,
        wdest,
        hdest,
        xsrc,
        ysrc,
        wsrc,
        hsrc
    );
}