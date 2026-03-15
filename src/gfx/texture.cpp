#include "gfx/texture.hpp"
#include "gfx/camera.hpp"

using namespace std;
using namespace exocet;

Texture::Texture(Camera& camera, SDL_Renderer* ren, const string& path): camera(camera) {
    this->ren = ren;
    openTexture(path);
}

void Texture::openTexture(const string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());

    if(surface == NULL) throw runtime_error("Failed to load the texture from `" + path + "`: " + IMG_GetError());

    this->h = surface->h;
    this->w = surface->w;

    tex = SDL_CreateTextureFromSurface(ren, surface);
    SDL_FreeSurface(surface);

    if(tex == NULL) throw runtime_error("Failed to create the texture from `" + path + "`: " + SDL_GetError());
  
    cout << "Success open the texture from `" << path << "`..." << endl;
}

void Texture::render(const EngineVector2D& position, int wdest, int hdest, int xsrc, int ysrc, int wsrc, int hsrc) noexcept {
    renderAnchor(
        position - camera.getPosition(),
        wdest,
        hdest,
        xsrc,
        ysrc,
        wsrc,
        hsrc
    );
}

void Texture::renderAnchor(const EngineVector2D& position, int wdest, int hdest, int xsrc, int ysrc, int wsrc, int hsrc) noexcept {
    SDL_Rect src = { xsrc, ysrc, wsrc, hsrc };
    SDL_Rect dest = { static_cast<int>(position.x), static_cast<int>(position.y), wdest, hdest };

    SDL_RenderCopy(ren, tex, &src, &dest);
}

void Texture::renderAnchorAngle(const EngineVector2D& position, double angle, int wdest, int hdest, int xsrc, int ysrc, int wsrc, int hsrc) noexcept {
    SDL_Rect src = { xsrc, ysrc, wsrc, hsrc };
    SDL_Rect dest = { static_cast<int>(position.x), static_cast<int>(position.y), wdest, hdest };

    SDL_RenderCopyEx(ren, tex, &src, &dest, angle, NULL, SDL_FLIP_NONE);
}

void Texture::renderAngle(const EngineVector2D& position, double angle, int wdest, int hdest, int xsrc, int ysrc, int wsrc, int hsrc) noexcept {
    renderAnchorAngle(
        position - camera.getPosition(),
        angle,
        wdest,
        hdest,
        xsrc,
        ysrc,
        wsrc,
        hsrc
    );
}