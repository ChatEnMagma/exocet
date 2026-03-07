#pragma once

#include <vector>
#include "constantes.hpp"
#include "gfx/graphic.hpp"

namespace exocet {
    class Background {
        private:
            std::vector<Sprite*> sprites;

            EngineVector2D position;
            int w, h;
            bool loop;

            Handler* handler;
        public:
            Background(Handler* handler, bool loop = false) noexcept {
                this->handler = handler;

                this->loop = loop;

                w = 0;
                h = 0;
            }
            ~Background() noexcept { refresh(); }

            void update() noexcept;
            void render() noexcept;

            void refresh();
            inline void setSize(const int width, const int height) noexcept { w = width; h = height; }

            inline void append(Sprite* sprite, const int zindex = 0) { 
                sprites.insert(sprites.begin() + zindex, sprite);
            }
            inline EngineVector2D getPosition() const noexcept { return position; }
            inline void setPosition(const EngineVector2D& position) noexcept { this->position = position; }
            inline int getWidth() const noexcept { return w; }
            inline int getHeight() const noexcept { return h; }
            inline void setLoop(bool loop) noexcept { this->loop = loop; }
    };
}