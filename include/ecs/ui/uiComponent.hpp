#pragma once

#include "tool/vectors.hpp"
#include "ecs/ecs.hpp"

namespace exocet {
    class UIComponent: public Component {
        private:
            Vector2D<int> position;
            int w, h;
        public:
            void init() override {
                setSize(0, 0);
            }

            inline Vector2D<int> getPosition() const { return position; }
            inline int getWidth() const { return w; }
            inline int getHeight() const { return h; }

            inline void setSize(int width, int height) { w = width; h = height; }
            inline void setPosition(const Vector2D<int> position) { this->position = position; }
            inline void setPointsPosition(int xpos, int ypos) { position.x = xpos; position.y = ypos; }
            inline void setRect(int xpos, int ypos, int width, int height) { setPointsPosition(xpos, ypos); setSize(width, height); }
    };
}