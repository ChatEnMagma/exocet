#pragma once

#include "gfx/sprite.hpp"
#include "ecs/movementComponent.hpp"

namespace exocet {
    class SpriteComponent: public Component {
        private:
            Sprite* sprite;
            std::size_t frame;
            Uint64 fps;
            Uint64 frameStart, frameTime;

            MovementComponent* movement;
            
            double a;
            int w, h;
        public:
            using Component::Component;
            
            void init() noexcept override;
            void update() noexcept override;
            void render() noexcept override;

            inline void fitSizeWithHitbox() noexcept { setSize(movement->getHitbox().getWidth(), movement->getHitbox().getHeight()); }

            inline std::size_t getCurrentFrame() const noexcept { return frame; }
            inline Uint64 getFPS() const noexcept { return fps; }

            inline double getAngle() const noexcept { return a; }
            inline int getWidth() const noexcept { return w; }
            inline int getHeight() const noexcept { return h; }
            
            inline void setAngle(const double angle) noexcept { a = angle; }
            inline void setSize(int width, int height) noexcept { w = width; h = height; }
            inline void setFPS(const Uint64 fps) noexcept { this->fps = fps; }
            inline void setSprite(Sprite* sprite) noexcept { this->sprite = sprite; }
    };
}