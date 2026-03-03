#pragma once

#include <climits>
#include "ecs/movementComponent.hpp"
#include "ecs/hitboxComponent.hpp"

namespace exocet {
    class PhysicComponent: public Component {
        private:
            MovementComponent* movement;
            HitboxComponent* hitbox;

            double masse;
            
            /**
             * \brief Interact the collision with other entityPhysic
             * \param e the entity in collide
             */
            void collisionWithPhysicEntity(Entity* e);
        public:
            ~PhysicComponent() = default;

            void init() noexcept override;

            void update() noexcept override;
            void render() noexcept override;

            // ALL GETTERS
            /**
             * \return Get all entities in collid with this physicComponent, if nothing entities is collide then it returns empty vector
             */
            std::vector<Entity*> getCollideEntities();

            // Getters from PhysicComponent
            inline double getMasse() const noexcept { return masse; }
            inline DoubleVector2D getSpeed() const noexcept { return movement->getSpeed(); }
            inline DoubleVector2D getMaxSpeed() const noexcept { return movement->getMaxSpeed(); }
            inline DoubleVector2D getFriction() const noexcept { return movement->getFriction(); }

            // Getters from movementComponent
            inline MovementComponent* getMovement() noexcept { return movement; }
            inline IntVector2D getPosition() const noexcept { return movement->getPosition(); }
            inline DoubleVector2D getVelocity() const noexcept { return movement->getVelocity(); }

            inline HitboxComponent* getHitbox() noexcept { return hitbox; }

            // ALL SETTERS
            // Setters from PhysicComponent
            inline void setMasse(double masse) noexcept { this->masse = masse; }
            inline void setSpeed(const DoubleVector2D& speed) noexcept { movement->setSpeed(speed); }
            inline void setMaxSpeed(const DoubleVector2D& maxSpeed) noexcept { movement->setMaxSpeed(maxSpeed); }
            inline void setFriction(const DoubleVector2D& friction) { movement->setFriction(friction); }

            // Setters from movementComponent
            inline void setPosition(const IntVector2D& position) noexcept { movement->setPosition(position); }
            inline void setVelocity(const DoubleVector2D& velocity) noexcept { movement->setVelocity(velocity); }

            inline friend std::ostream& operator<<(std::ostream& os, const PhysicComponent* component) noexcept {
                return os << "PhysicC: {vel: " << component->getVelocity();
            }
    };
}