#pragma once

#include <limits>

#include "ecs/hitboxComponent.hpp"
#include "ecs/transformComponent.hpp"
#include "tool/vectors.hpp"

namespace exocet {
    class MovementComponent: public Component {
        private:
            EngineVector2D speed, maxSpeed;
            EngineVector2D friction;

            HitboxComponent* hitbox;
            TransformComponent* transform;
        public:
            using Component::Component;
            MovementComponent() noexcept = default;

            void init() noexcept override;

            /**
             * \brief Calculate the new position depend of velocity
             * \return the new position
             */
            void move() noexcept;

            // ALL GETTERS
            inline const EngineVector2D& getAcceleration() const noexcept { return transform->getAcceleration(); }
            inline const EngineVector2D& getPosition() const noexcept { return transform->getPosition(); }
            inline const EngineVector2D& getVelocity() const noexcept { return transform->getVelocity(); }

            inline const EngineVector2D& getFriction() const noexcept { return friction; }
            inline const EngineVector2D& getSpeed() const noexcept { return speed; }
            inline const EngineVector2D& getMaxSpeed() const noexcept { return maxSpeed; }

            inline const EngineVector2D getCenter() const noexcept { return hitbox->getCenter(); }

            inline int getWidth() const noexcept { return hitbox->getWidth(); }
            inline int getHeight() const noexcept { return hitbox->getHeight(); }
            inline const Polygon& getPolygon() const noexcept { return hitbox->getPolygon(); }

            // ALL SETTERS
            inline void setAcceleration(const EngineVector2D& acceleration) noexcept { transform->setAcceleration(acceleration); }
            inline void setAccelerationX(double accelerationX) noexcept { transform->setAccelerationX(accelerationX); }
            inline void setAccelerationY(double accelerationY) noexcept { transform->setAccelerationY(accelerationY); }
            inline void setPosition(const EngineVector2D& position) noexcept { transform->setPosition(position); }
            inline void setVelocity(const EngineVector2D& velocity) noexcept { transform->setVelocity(velocity); }

            inline void setFriction(const EngineVector2D& friction) {
                if(friction.x > 1 || friction.x < 0 || friction.y > 1 || friction.y < 0) throw new std::runtime_error("your friction must be in [0, 1]");
                this->friction = friction; 
            }
            inline void setSpeed(const EngineVector2D& speed) noexcept { this->speed = speed; }
            inline void setMaxSpeed(const EngineVector2D& maxSpeed) noexcept { this->maxSpeed = maxSpeed; }

            inline HitboxComponent& getHitbox() const noexcept { return *hitbox; }
            inline TransformComponent& getTransform() const noexcept { return *transform; }
    };
}