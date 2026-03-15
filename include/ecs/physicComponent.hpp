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
            using Component::Component;
            ~PhysicComponent() = default;

            void init() noexcept override;

            void update() noexcept override;
            void render() noexcept override;

            // ALL GETTERS
            /**
             * \return Get all entities in collid with this physicComponent, if nothing entities is collide then it returns empty vector
             */
            std::vector<Entity*> getCollideEntities() { return hitbox->getCollideEntities(); }
            std::optional<Entity*> getCollide() { return hitbox->getCollide(); }

            // Getters from PhysicComponent
            inline double getMasse() const noexcept { return masse; }
            inline EngineVector2D getSpeed() const noexcept { return movement->getSpeed(); }
            inline EngineVector2D getMaxSpeed() const noexcept { return movement->getMaxSpeed(); }
            inline EngineVector2D getFriction() const noexcept { return movement->getFriction(); }

            // Getters from movementComponent
            inline MovementComponent* getMovement() noexcept { return movement; }
            inline EngineVector2D getAccelation() const noexcept { return movement->getAccelation(); }
            inline EngineVector2D getPosition() const noexcept { return movement->getPosition(); }
            inline EngineVector2D getVelocity() const noexcept { return movement->getVelocity(); }

            inline HitboxComponent* getHitbox() noexcept { return hitbox; }

            // ALL SETTERS
            // Setters from PhysicComponent
            inline void setMasse(double masse) noexcept { this->masse = masse; }
            inline void setSpeed(const EngineVector2D& speed) noexcept { movement->setSpeed(speed); }
            inline void setMaxSpeed(const EngineVector2D& maxSpeed) noexcept { movement->setMaxSpeed(maxSpeed); }
            inline void setFriction(const EngineVector2D& friction) { movement->setFriction(friction); }

            // Setters from movementComponent
            inline void setAccelation(const EngineVector2D& accelaration) noexcept { movement->setAccelaration(accelaration); }
            inline void setPosition(const EngineVector2D& position) noexcept { movement->setPosition(position); }
            inline void setVelocity(const EngineVector2D& velocity) noexcept { movement->setVelocity(velocity); }

            inline friend std::ostream& operator<<(std::ostream& os, const PhysicComponent* component) noexcept {
                return os << "PhysicC: {vel: " << component->getVelocity();
            }
    };
}