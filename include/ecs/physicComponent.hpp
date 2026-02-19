#pragma once

#include <climits>
#include "ecs/hitboxComponent.hpp"

namespace exocet {
    class PhysicComponent: public Component {
        private:
            TransformComponent* transform;
            HitboxComponent* hitbox;

            double speed, maxSpeed;
            double friction;
            double masse;

            /**
             * \brief Calculates all movement of the physic component
             */
            void move();

            /**
             * \brief Interact the collision with other entityPhysic
             * \param e the entity in collide
             */
            void collisionWithPhysicEntity(Entity* e);
        public:
            ~PhysicComponent() = default;

            void init() override;

            void update() override;
            void render() override;

            // ALL GETTERS
            /**
             * \return Get all entities in collid with this physicComponent, if nothing entities is collide then it returns empty vector
             */
            std::vector<Entity*> getCollideEntities();

            // Getters from PhysicComponent
            inline double getMasse() const { return masse; }
            inline double getSpeed() const { return speed; }
            inline double getMaxSpeed() const { return maxSpeed; }
            inline double getFriction() const { return friction; }

            // Getters from TransformComponent
            inline TransformComponent* getTransform() { return transform; }
            inline IntVector2D getPosition() const { return transform->getPosition(); }
            inline int getPositionX() const { return transform->pos.x; }
            inline int getPositionY() const { return transform->pos.y; }
            inline DoubleVector2D getVelocity() const { return transform->getVelocity(); }

            inline HitboxComponent* getHitbox() { return hitbox; }

            // ALL SETTERS
            // Setters from PhysicComponent
            inline void setMasse(double masse) { this->masse = masse; }
            inline void setSpeed(double speed) { this->speed = speed; }
            inline void setMaxSpeed(double maxSpeed) { this->maxSpeed = maxSpeed; }
            inline void setFriction(double friction) { this->friction = friction; }

            // Setters from TransformComponent
            inline void setPosition(const IntVector2D& position) { transform->setPosition(position); }
            inline void setPointsPosition(int xpos, int ypos) { transform->setPointsPosition(xpos, ypos); }
            inline void setVelocity(const DoubleVector2D& velocity) { transform->setVelocity(velocity); }
            inline void setPointsVelocity(double xvel, double yvel) { transform->setPointsVelocity(xvel, yvel); }

            inline friend std::ostream& operator<<(std::ostream& os, const PhysicComponent* component) {
                return os << "PhysicC: {vel: " << component->getVelocity();
            }
    };
}