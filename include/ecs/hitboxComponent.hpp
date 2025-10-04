#pragma once

#include "ecs/transformComponent.hpp"

namespace exocet {
    class HitboxComponent: public Component {
        private:
            int x, y, w, h;
            TransformComponent* transform;

            Uint8 color[3];
        public:
            void init() override;

            void render() override;

            bool isCollide(HitboxComponent* hitbox) const;
            bool isCollideHorizontal(HitboxComponent* hitbox) const;
            bool isCollideVertical(HitboxComponent* hitbox) const;

            // ALL GETTERS POINT HITBOX
            inline Vector2D<int> getCenter() const { return Vector2D<int>(transform->getPosition().x + (x + w) / 2, transform->getPosition().y + (y + h) / 2); }
            inline int getLeft() const { return transform->getPosition().x + x; }
            inline int getRight() const { return transform->getPosition().x + x + w; }
            inline int getTop() const { return transform->getPosition().y + y; }
            inline int getBottom() const { return transform->getPosition().y + y + h; }

            inline float getMoveLeft() const { return transform->getVelocity().x + (float) getLeft(); }
            inline float getMoveRight() const { return transform->getVelocity().x + (float) getRight(); }
            inline float getMoveTop() const { return transform->getVelocity().y + (float) getTop(); }
            inline float getMoveBottom() const { return transform->getVelocity().y + (float) getBottom(); }

            inline Vector2D<int> getOffset() const { return Vector2D<int>(x, y); }
            inline int getWidth() const { return w; }
            inline int getHeight() const { return h; }

            inline void setOffset(int xoffset, int yoffset) { x = xoffset; y = yoffset; }
            inline void setSize(int width, int height) { w = width; h = height; }
            inline void setHitbox(int xoffset, int yoffset, int width, int height) { setOffset(xoffset, yoffset); setSize(width, height); }
            inline void setColor(Uint8 red, Uint8 green, Uint8 blue) { color[0] = red; color[1] = green; color[2] = blue; }
    };
}