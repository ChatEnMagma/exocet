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
            Texture(Handler* handler, std::string path);
            ~Texture() { clean(); }

            /**
             * \brief Render the texture
             */
            void render(Vector2D<int> postion, int width, int height);
            void renderAnchor(Vector2D<int> position, int width, int height);

            inline void setHandler(Handler* handler) { this->handler = handler; }
            inline void clean() { SDL_DestroyTexture(tex); }

            inline int getWidth() { return w; }
            inline int getHeight() { return h; }

            inline friend std::ostream& operator<<(std::ostream& os, const Texture& texture) {
                return os << &texture;
            }
    };
}