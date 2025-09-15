#pragma once

#include <climits>

#include "ecs/hitboxComponent.hpp"

namespace exocet {
    class PhysicComponent: public Component {
        private:
            TransformComponent* transform;
            HitboxComponent* hitbox;

            float speed, maxSpeed;
            float friction;
            float masse;

            /**
             * \brief Calculates all movement of the physic component
             */
            void move();

            void collisionWithPhysicEntity(Entity* e);
        public:
            void init() override;

            void update() override;
            void render() override;

            // ALL GETTERS
            /**
             * \return Get all entities in collid with this physicComponent, if nothing entities is collide then it returns empty vector
             */
            std::vector<Entity*> getCollideEntities();

            // Getters from PhysicComponent
            inline float getMasse() const { return masse; }
            inline float getSpeed() const { return speed; }
            inline float getMaxSpeed() const { return maxSpeed; }
            inline float getFriction() const { return friction; }

            // Getters from TransformComponent
            inline TransformComponent* getTransform() { return transform; }
            inline Vector2D<int> getPosition() const { return transform->getPosition(); }
            inline Vector2D<float> getVelocity() const { return transform->getVelocity(); }

            inline HitboxComponent* getHitbox() { return hitbox; }

            // ALL SETTERS
            // Setters from PhysicComponent
            inline void setMasse(float masse) { this->masse = masse; }
            inline void setSpeed(float speed) { this->speed = speed; }
            inline void setMaxSpeed(float maxSpeed) { this->maxSpeed = maxSpeed; }
            inline void setFriction(float friction) { this->friction = friction; }

            // Setters from TransformComponent
            inline void setPosition(Vector2D<int> position) { transform->setPosition(position); }
            inline void setPointsPosition(int xpos, int ypos) { transform->setPointsPosition(xpos, ypos); }
            inline void setVelocity(Vector2D<float> velocity) { transform->setVelocity(velocity); }
            inline void setPointsVelocity(float xvel, float yvel) { transform->setPointsVelocity(xvel, yvel); }

            inline friend std::ostream& operator<<(std::ostream& os, const PhysicComponent* component) {
                return os << "PhysicC: {vel: " << component->getVelocity();
            }
    };
}