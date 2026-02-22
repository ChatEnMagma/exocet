#pragma once

#include "tool/vectors.hpp"
#include "ecs/ecs.hpp"

namespace exocet {
    class UIComponent: public Component {
        private:
            IntVector2D position;
            int w, h;
        public:
            void init() noexcept override {
                setSize(0, 0);
            }

            inline Vector2D<int> getPosition() const noexcept { return position; }
            inline int getWidth() const noexcept { return w; }
            inline int getHeight() const noexcept { return h; }

            inline void setSize(int width, int height) noexcept { w = width; h = height; }
            inline void setPosition(const IntVector2D& position) noexcept { this->position = position; }
            inline void setPointsPosition(int xpos, int ypos) noexcept { position.x = xpos; position.y = ypos; }
            inline void setRect(int xpos, int ypos, int width, int height) noexcept { setPointsPosition(xpos, ypos); setSize(width, height); }
    };
}