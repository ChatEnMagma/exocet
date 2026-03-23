#pragma once

#include "ecs/movementComponent.hpp"

namespace exocet {
    class ControllerDirectionsComponent: public Component {
        private:
            MovementComponent* movement;

            EngineVector2D direction;
        public:
            using Component::Component;
            ~ControllerDirectionsComponent() = default;

            void init() override;
            void update() override;

            inline const EngineVector2D& getDirection() const noexcept { return direction; }
            inline const EngineVector2D& getSpeed() const noexcept { return movement->getSpeed(); }

            inline void setDirection(const EngineVector2D& direction) noexcept { this->direction = direction; }

            inline void setDirectionX(double x) noexcept { direction.x = x; }
            inline void setDirectionY(double y) noexcept { direction.y = y; }
    };
}