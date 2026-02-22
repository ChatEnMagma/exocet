#pragma once

#include "ecs/movementComponent.hpp"

namespace exocet {
    class ParticleComponent: public Component {
        private:
            MovementComponent* movement;
            std::size_t time;
        public:
            void init() noexcept override;
            void update() noexcept override;

            inline void setPosition(const IntVector2D& position) noexcept { movement->setPosition(position); }
            inline void setVelocity(const DoubleVector2D& velocity) noexcept { movement->setVelocity(velocity); }
            inline void setTime(std::size_t time) noexcept { this->time = time; }
            inline int getTime() const noexcept { return time; }
    };
}