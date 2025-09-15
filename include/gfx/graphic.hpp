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
            static Texture* player;

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

            void renderText(int x, int y, int w, int h, std::string text, TTF_Font* font) {
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
                } else
                    std::cerr << "Failed to create a texture: " << SDL_GetError() << std::endl;

                SDL_FreeSurface(text_s);
                SDL_DestroyTexture(texture);
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