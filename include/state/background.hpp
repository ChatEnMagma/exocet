#pragma once

#include <vector>
#include "constantes.hpp"
#include "gfx/graphic.hpp"

namespace exocet {
    class Background {
        private:
            std::vector<Texture*> tex;
            Vector2D<int> position;
            int w, h;
            bool loop;

            Handler* handler;
        public:
            Background(bool loop = false) {
                this->loop = loop;
                w = 0;
                h = 0;
            }
            ~Background() {
                refresh();
            }

            void update();
            void render();

            void refresh();
            inline void setSize(const int width, const int height) { w = width; h = height; }

            inline void append(const int zindex, Texture* texture) { 
                tex.insert(tex.begin() + zindex, texture);
            }
            inline Vector2D<int> getPosition() const { return position; }
            inline void setPosition(const Vector2D<int> position) { this->position = position; }
            inline int getWidth() const { return w; }
            inline int getHeight() const { return h; }
            inline void setLoop(bool loop) { this->loop = loop; }

            inline void setHandler(Handler* handler) { this->handler = handler; }
    };
}