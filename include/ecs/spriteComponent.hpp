#pragma once

#include "gfx/sprite.hpp"
#include "ecs/transformComponent.hpp"

namespace exocet {
    class SpriteComponent: public Component {
        private:
            Sprite* sprite;
            std::size_t frame;
            Uint32 fps;
            Uint32 frameStart, frameTime;

            TransformComponent* transform;
            
            double a;
            int w, h;
        public:
            void init() override;
            void update() override;
            void render() override;

            void fitSizeWithHitbox();

            inline std::size_t getCurrentFrame() const { return frame; }
            inline Uint32 getFPS() const { return fps; }

            inline double getAngle() const { return a; }
            inline int getWidth() const { return w; }
            inline int getHeight() const { return h; }
            
            inline void setAngle(const double angle) { a = angle; }
            inline void setSize(int width, int height) { w = width; h = height; }
            inline void setFPS(const Uint32 fps) { this->fps = fps; }
            inline void setSprite(Sprite* sprite) { this->sprite = sprite; }
    };
}