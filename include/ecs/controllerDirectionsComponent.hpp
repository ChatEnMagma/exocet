#pragma once

#include "ecs/hitboxComponent.hpp"

namespace exocet {
    class ControllerDirectionsComponent: public Component {
        private:
            MovementComponent* movement;
            HitboxComponent* hitbox;

            DoubleVector2D direction;
        public:
            ~ControllerDirectionsComponent() = default;

            void init() override;
            void update() override;

            inline DoubleVector2D getDirection() const noexcept { return direction; }
            inline DoubleVector2D getSpeed() const noexcept { return movement->getSpeed(); }

            inline void setDirection(const DoubleVector2D& direction) noexcept { this->direction = direction; }

            inline void setDirectionX(double x) noexcept { direction.x = x; }
            inline void setDirectionY(double y) noexcept { direction.y = y; }
    };
}