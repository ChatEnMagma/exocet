#pragma once

#include "ecs/ecs.hpp"
#include "tool/vectors.hpp"

namespace exocet {
    class TransformComponent: public Component {
        private:
            EngineVector2D acceleration;
            EngineVector2D position;
            EngineVector2D velocity;
        public:
            using Component::Component;
            ~TransformComponent() = default;

            void init() noexcept override {
                acceleration = EngineVector2D::vectorZeros();
                position = EngineVector2D::vectorZeros();
                velocity = EngineVector2D::vectorZeros();
            }

            void update() noexcept override;
            
            void computeUp() noexcept { position.y += ceil(velocity.y); }
            void computeDown() noexcept { position.y += floor(velocity.y); }
            void computeRight() noexcept { position.x += floor(velocity.x); }
            void computeLeft() noexcept { position.x += ceil(velocity.x); }

            void computeFriction(const EngineVector2D& friction) { velocity *= friction; }

            EngineVector2D computeNextMove() const;

            inline bool isMovingUp() const noexcept { return velocity.y < 0.f; }
            inline bool isMovingDown() const noexcept { return velocity.y > 0.f; }
            inline bool isMovingRight() const noexcept { return velocity.x > 0.f; }
            inline bool isMovingLeft() const noexcept { return velocity.x < 0.f; }
            inline bool isMoving() const noexcept { return !velocity.isVectorNull(); }

            inline const EngineVector2D& getAcceleration() const noexcept { return acceleration; }
            inline const EngineVector2D& getPosition() const noexcept { return position; }
            inline const EngineVector2D& getVelocity() const noexcept { return velocity; }

            inline void setAcceleration(const EngineVector2D& acceleration) noexcept { this->acceleration = acceleration; }
            /**
             * Set a new position, you dont need trunc digit because this method already done
             * \param position the new position
             */
            inline void setPosition(const EngineVector2D& position) noexcept { this->position = position.trunc(); }
            inline void setVelocity(const EngineVector2D& velocity) noexcept { this->velocity = velocity; }

            inline void setPositionX(int positionX) noexcept { this->position.x = static_cast<double>(positionX); }
            inline void setPositionY(int positionY) noexcept { this->position.y = static_cast<double>(positionY); }
            inline void setAccelerationX(double accelerationX) noexcept { this->acceleration.x = accelerationX; }
            inline void setAccelerationY(double accelerationY) noexcept { this->acceleration.y = accelerationY; }
            inline void setVelocityX(double velocityX) noexcept { this->velocity.x = velocityX; }
            inline void setVelocityY(double velocityY) noexcept { this->velocity.y = velocityY; }
    };
}