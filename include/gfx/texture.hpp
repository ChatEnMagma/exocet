#pragma once

#include <iostream>
#include <string>

#include "constantes.hpp"
#include "tool/vectors.hpp"

namespace exocet {
    class Texture {
        private:
            Handler* handler;

            SDL_Texture* tex = NULL;

            int x = 0;
            int y = 0;
            int w = 0;
            int h = 0;
        public:
            Texture(Handler* handler, SDL_Renderer* renderer, std::string path);

            void render(Vector2D<int> postion, int width, int height);

            inline void setHandler(Handler* handler) { this->handler = handler; }
            inline void clean() { SDL_DestroyTexture(tex); }
    };
}