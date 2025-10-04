#pragma once

#include "ecs/ecs.hpp"
#include "tool/vectors.hpp"

namespace exocet {
    class TransformComponent: public Component {
        public:
            Vector2D<int> pos;
            Vector2D<float> vel;

            void init() override {
                setPointsPosition(0, 0);
                setPointsVelocity(0.f, 0.f);
            }

            /**
             * \brief Calculate the new position depend of velocity
             * \return the new position
             */
            Vector2D<int> move() const;

            // All methods to fetch the direction
            inline bool isMovingLeft() const { return vel.x < 0; }
            inline bool isMovingRight() const { return vel.x > 0; }
            inline bool isMovingUp() const { return vel.y < 0; }
            inline bool isMovingDown() const { return vel.y > 0; }

            // ALL GETTERS
            inline Vector2D<int> getPosition() const { return pos; }
            inline int getPositionX() const { return pos.x; }
            inline Vector2D<float> getVelocity() const { return vel; }

            // ALL SETTERS
            // setters of position
            inline void setPosition(Vector2D<int> position) { pos = position; }
            inline void setPointsPosition(int xpos, int ypos) { pos.x = xpos; pos.y = ypos; }

            // setters of velocity
            inline void setVelocity(Vector2D<float> velocity) { vel = velocity; }
            inline void setPointsVelocity(int xvel, int yvel) { vel.x = xvel; vel.y = yvel; }
            inline void setVelocityX(float xvel) { vel.x = xvel; }
            inline void setVelocityY(float yvel) { vel.y = yvel; }

            inline friend std::ostream& operator<<(std::ostream& os, const TransformComponent* component) {
                return os << "Transform: {pos: " << component->getPosition() << " ; vel: " << component->getVelocity() << "}";
            }
    };
}