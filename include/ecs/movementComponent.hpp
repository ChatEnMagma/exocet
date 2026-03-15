#pragma once

#include <limits>

#include "ecs/ecs.hpp"
#include "tool/vectors.hpp"

namespace exocet {
    class MovementComponent: public Component {
        private:
            EngineVector2D speed, maxSpeed;
            EngineVector2D friction;
        public:
            using Component::Component;
            MovementComponent() noexcept = default;

            EngineVector2D pos;
            EngineVector2D vel;
            EngineVector2D acc;

            void init() noexcept override {
                setAccelaration(EngineVector2D::vectorZeros());
                setPosition(EngineVector2D::vectorZeros());
                setVelocity(EngineVector2D::vectorZeros());

                setSpeed(EngineVector2D(1.l, 1.f));
                setMaxSpeed(EngineVector2D(std::numeric_limits<double>::max(), std::numeric_limits<double>::max()));
            }

            /**
             * \brief Calculate the new position depend of velocity
             * \return the new position
             */
            void move() noexcept;

            // All methods to fetch the direction
            inline bool isMovingLeft() const noexcept { return vel.x < 0; }
            inline bool isMovingRight() const noexcept { return vel.x > 0; }
            inline bool isMovingUp() const noexcept { return vel.y < 0; }
            inline bool isMovingDown() const noexcept { return vel.y > 0; }

            // ALL GETTERS
            inline EngineVector2D getAccelation() const noexcept { return acc; }
            inline EngineVector2D getPosition() const noexcept { return pos; }
            inline EngineVector2D getVelocity() const noexcept { return vel.normalized() * speed; }
            inline EngineVector2D getFriction() const noexcept { return friction; }
            inline EngineVector2D getSpeed() const noexcept { return speed; }
            inline EngineVector2D getMaxSpeed() const noexcept { return maxSpeed; }
            inline double getAngle() const noexcept { return vel.getAngle(); }

            // ALL SETTERS
            inline void setAccelaration(const EngineVector2D& accelaration) noexcept { acc = accelaration; }
            inline void setPosition(const EngineVector2D& position) noexcept { pos = position; }
            inline void setVelocity(const EngineVector2D& velocity) noexcept { vel = velocity; }
            inline void setFriction(const EngineVector2D& friction) {
                if(friction.x > 1 || friction.x < 0 || friction.y > 1 || friction.y < 0) throw new std::runtime_error("your friction must be in [0, 1]");
                this->friction = friction; 
            }
            inline void setSpeed(const EngineVector2D& speed) noexcept { this->speed = speed; }
            inline void setMaxSpeed(const EngineVector2D& maxSpeed) noexcept { this->maxSpeed = maxSpeed; }

            inline friend std::ostream& operator<<(std::ostream& os, const MovementComponent* component) noexcept {
                return os << "move: {pos: " << component->getPosition() << " ; vel: " << component->getVelocity() << "}";
            }
    };
}