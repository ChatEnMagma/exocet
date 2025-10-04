#pragma once

#include "constantes.hpp"
#include "tool/vectors.hpp"

#include "gfx/camera.hpp"
#include "gfx/texture.hpp"

namespace exocet {
    class Graphic {
        private:
            SDL_Renderer* ren = NULL;

            Camera camera;

            void openFont(TTF_Font** font, std::string path);
        public:
            static TTF_Font* freeRoyalty;

            Graphic(SDL_Renderer* renderer) { ren = renderer; }

            void initTextures(Handler* handler);
            void clean();

            inline void renderRect(Vector2D<int> position, int width, int height) {
                SDL_Rect rect = { 
                    position.x - camera.getPosition().x, 
                    position.y - camera.getPosition().y, 
                    width, 
                    height 
                };
                SDL_RenderDrawRect(ren, &rect);
            }

            void renderText(int x, int y, int w, int h, std::string text, TTF_Font* font);

            inline void renderLine(const Vector2D<int> position1, const Vector2D<int> position2) {
                SDL_RenderDrawLine(
                    ren, 
                    position1.x - camera.getPosition().x,
                    position1.y - camera.getPosition().y,
                    position2.x - camera.getPosition().x,
                    position2.y - camera.getPosition().y
                );
            }

            inline void setRenderColor(Uint8 red, Uint8 blue, Uint8 green, Uint8 alpha = 0xff) { SDL_SetRenderDrawColor(ren, red, blue, green, alpha); }
            inline void renderClear() { SDL_RenderClear(ren); }
            inline void renderPresent() { SDL_RenderPresent(ren); }

            inline SDL_Renderer* getRenderer() { return ren; }
            inline void setRenderer(SDL_Renderer* renderer) { ren = renderer; }

            inline Camera* getCamera() { return &camera; }
            inline void centerOnEntity(Entity* entity) { camera.centerOnEntity(entity); }
    };
}