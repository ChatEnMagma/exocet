#pragma once

#include "constantes.hpp"
#include "tool/vectors.hpp"
#include "tool/polygon.hpp"

#include "gfx/camera.hpp"
#include "gfx/texture.hpp"

namespace exocet {
    class Graphic {
        private:
            SDL_Renderer* ren = NULL;

            Camera camera;

            void openFont(TTF_Font** font, std::string path);

            SDL_Color color;
        public:
            static TTF_Font* freeRoyalty;

            inline void setColor(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 0xFF) {
                color.r = red;
                color.g = green;
                color.b = blue;
                color.a = alpha;

                SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
            }

            Graphic(SDL_Renderer* renderer) { 
                ren = renderer; 

                color.r = 0x00;
                color.g = 0x00;
                color.b = 0x00;
                color.a = 0xFF;
            }

            void initTextures(Handler* handler);
            void clean();

            inline void renderAnchorRect(Vector2D<int> position, int width, int height) {
                SDL_Rect rect = { position.x, position.y, width, height };
                SDL_RenderDrawRect(ren, &rect);
            }
            inline void renderAnchorFillRect(Vector2D<int> position, int width, int height) {
                SDL_Rect rect = { position.x, position.y, width, height };
                SDL_RenderFillRect(ren, &rect);
            }

            inline void renderRect(Vector2D<int> position, int width, int height) { renderAnchorRect(position - camera.getPosition(), width, height); }
            inline void renderFillRect(Vector2D<int> position, int width, int height) { renderAnchorFillRect(position - camera.getPosition(), width, height); }

            void renderText(int x, int y, int w, int h, std::string text, TTF_Font* font);

            inline void setRenderColor(Uint8 red, Uint8 blue, Uint8 green, Uint8 alpha = 0xff) { SDL_SetRenderDrawColor(ren, red, blue, green, alpha); }
            inline void renderClear() { SDL_RenderClear(ren); }
            inline void renderPresent() { SDL_RenderPresent(ren); }

            inline void renderAnchorLine(const Vector2D<int> pos1, const Vector2D<int> pos2) { SDL_RenderDrawLine(ren, pos1.x, pos1.y, pos2.x, pos2.y); }
            inline void renderLine(const Vector2D<int> pos1, const Vector2D<int> pos2) {
                renderAnchorLine(pos1 - camera.getPosition(), pos2 - camera.getPosition());
            }

            void renderAnchorPolygon(const Vector2D<int>& position, const Polygon& polygon) {
                for(std::size_t i = 0; i < polygon.length(); i++) {
                    int nxt = (i + 1) % polygon.length();
                    renderAnchorLine(position + polygon[i], position + polygon[nxt]);
                }
            }
            inline void renderPolygon(const Vector2D<int>& position, const Polygon& polygon) { renderAnchorPolygon(position - camera.getPosition(), polygon); }

            inline SDL_Renderer* getRenderer() { return ren; }
            inline void setRenderer(SDL_Renderer* renderer) { ren = renderer; }

            inline Camera* getCamera() { return &camera; }
            inline void centerOnEntity(Entity* entity) { camera.centerOnEntity(entity); }
    };
}