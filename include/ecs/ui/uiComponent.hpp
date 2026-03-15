#pragma once

#include "tool/vectors.hpp"
#include "ecs/ecs.hpp"

namespace exocet {
    class UIComponent: public Component {
        private:
            EngineVector2D position;
            int w, h;
        public:
            using Component::Component;

            void init() noexcept override {
                setSize(0, 0);
            }

            inline EngineVector2D getPosition() const noexcept { return position; }
            inline int getWidth() const noexcept { return w; }
            inline int getHeight() const noexcept { return h; }

            inline void setSize(int width, int height) noexcept { w = width; h = height; }
            inline void setPosition(const EngineVector2D& position) noexcept { this->position = position; }
            inline void setPointsPosition(int xpos, int ypos) noexcept {
                position.x = static_cast<double>(xpos); 
                position.y = static_cast<double>(ypos); 
            }
            inline void setRect(int xpos, int ypos, int width, int height) noexcept { setPointsPosition(xpos, ypos); setSize(width, height); }
    };
}