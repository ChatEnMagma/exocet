#pragma once

#include <limits>

#include "ecs/ecs.hpp"
#include "tool/vectors.hpp"

namespace exocet {
    class MovementComponent: public Component {
        public:
            MovementComponent() noexcept = default;

            IntVector2D pos;
            DoubleVector2D vel;
            DoubleVector2D speed, maxSpeed;
            DoubleVector2D friction;

            void init() noexcept override {
                setPosition(IntVector2D());
                setVelocity(DoubleVector2D());

                setSpeed(DoubleVector2D(1.l, 1.f));
                setMaxSpeed(DoubleVector2D(std::numeric_limits<double>::max(), std::numeric_limits<double>::max()));
            }

            /**
             * \brief Calculate the new position depend of velocity
             * \return the new position
             */
            void move() noexcept;

            inline DoubleVector2D computeMove() const noexcept { return vel.normalized().scalar(vel.magnitude()); }

            // All methods to fetch the direction
            inline bool isMovingLeft() const noexcept { return vel.x < 0; }
            inline bool isMovingRight() const noexcept { return vel.x > 0; }
            inline bool isMovingUp() const noexcept { return vel.y < 0; }
            inline bool isMovingDown() const noexcept { return vel.y > 0; }

            // ALL GETTERS
            inline IntVector2D getPosition() const noexcept { return pos; }
            inline DoubleVector2D getVelocity() const noexcept { return vel.normalized() * speed; }
            inline DoubleVector2D getFriction() const noexcept { return friction; }
            inline DoubleVector2D getSpeed() const noexcept { return speed; }
            inline DoubleVector2D getMaxSpeed() const noexcept { return maxSpeed; }
            inline double getAngle() const noexcept { return vel.getAngle(); }

            // ALL SETTERS
            inline void setPosition(const IntVector2D& position) noexcept { pos = position; }
            inline void setVelocity(const DoubleVector2D& velocity) noexcept { vel = velocity; }
            inline void setFriction(const DoubleVector2D& friction) {
                if(friction.x > 1 || friction.x < 0 || friction.y > 1 || friction.y < 0) throw new std::runtime_error("your friction must be in [0, 1]");
                this->friction = friction; 
            }
            inline void setSpeed(const DoubleVector2D& speed) noexcept { this->speed = speed; }
            inline void setMaxSpeed(const DoubleVector2D& maxSpeed) noexcept { this->maxSpeed = maxSpeed; }

            inline friend std::ostream& operator<<(std::ostream& os, const MovementComponent* component) noexcept {
                return os << "move: {pos: " << component->getPosition() << " ; vel: " << component->getVelocity() << "}";
            }
    };
}