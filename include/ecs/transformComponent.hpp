#pragma once

#include "ecs/ecs.hpp"
#include "tool/vectors.hpp"

namespace exocet {
    class TransformComponent: public Component {
        public:
            TransformComponent() = default;

            IntVector2D pos;
            DoubleVector2D vel;

            void init() override {
                setPosition(IntVector2D());
                setVelocity(DoubleVector2D());
            }

            /**
             * \brief Calculate the new position depend of velocity
             * \return the new position
             */
            IntVector2D move() const;

            // All methods to fetch the direction
            inline bool isMovingLeft() const { return vel.x < 0; }
            inline bool isMovingRight() const { return vel.x > 0; }
            inline bool isMovingUp() const { return vel.y < 0; }
            inline bool isMovingDown() const { return vel.y > 0; }

            // ALL GETTERS
            inline IntVector2D getPosition() const { return pos; }
            inline int getPositionX() const { return pos.x; }
            inline DoubleVector2D getVelocity() const { return vel; }
            inline double getAngle() const { return vel.getAngle(); }

            // ALL SETTERS
            // setters of position
            inline void setPosition(const IntVector2D& position) { pos = position; }
            inline void setPointsPosition(int xpos, int ypos) { pos.x = xpos; pos.y = ypos; }

            // setters of velocity
            inline void setVelocity(const DoubleVector2D& velocity) { vel = velocity; }
            inline void setPointsVelocity(int xvel, int yvel) { vel.x = xvel; vel.y = yvel; }
            inline void setVelocityX(double xvel) { vel.x = xvel; }
            inline void setVelocityY(double yvel) { vel.y = yvel; }

            inline friend std::ostream& operator<<(std::ostream& os, const TransformComponent* component) {
                return os << "Transform: {pos: " << component->getPosition() << " ; vel: " << component->getVelocity() << "}";
            }
    };
}