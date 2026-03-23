#pragma once

#include <climits>
#include "ecs/movementComponent.hpp"

namespace exocet {
    class PhysicComponent: public Component {
        private:
            MovementComponent* movement;

            double masse;
            
            /**
             * \brief Interact the collision with other entityPhysic
             * \param e the entity in collide
             */
            void collisionWithPhysicEntity(Entity& e);
        public:
            using Component::Component;
            ~PhysicComponent() = default;

            void init() noexcept override;

            void update() noexcept override;
            void render() noexcept override;

            // ALL GETTERS
            bool isCollide(Entity& e) const {
                if(!e.hasComponent<HitboxComponent>())
                    throw std::runtime_error("The entity `" + e.getTag() + "` must have HitboxComponent");
                return movement->getHitbox().isCollide(e.getComponent<HitboxComponent>());
            }
            /**
             * \return Get all entities in collid with this physicComponent, if nothing entities is collide then it returns empty vector
             */
            std::vector<Entity*> getCollideEntities() { return movement->getHitbox().getCollideEntities(); }
            std::optional<Entity*> getCollide() { return movement->getHitbox().getCollide(); }

            // Getters from PhysicComponent
            inline double getMasse() const noexcept { return masse; }
            inline const EngineVector2D& getSpeed() const noexcept { return movement->getSpeed(); }
            inline const EngineVector2D& getMaxSpeed() const noexcept { return movement->getMaxSpeed(); }
            inline const EngineVector2D& getFriction() const noexcept { return movement->getFriction(); }

            // Getters from movementComponent
            inline MovementComponent& getMovement() noexcept { return *movement; }
            inline const EngineVector2D& getAccelation() const noexcept { return movement->getAcceleration(); }
            inline const EngineVector2D& getPosition() const noexcept { return movement->getPosition(); }
            inline const EngineVector2D& getVelocity() const noexcept { return movement->getVelocity(); }

            // ALL SETTERS
            // Setters from PhysicComponent
            inline void setMasse(double masse) noexcept { this->masse = masse; }
            inline void setSpeed(const EngineVector2D& speed) noexcept { movement->setSpeed(speed); }
            inline void setMaxSpeed(const EngineVector2D& maxSpeed) noexcept { movement->setMaxSpeed(maxSpeed); }
            inline void setFriction(const EngineVector2D& friction) { movement->setFriction(friction); }

            // Setters from movementComponent
            inline void setAccelation(const EngineVector2D& accelaration) noexcept { movement->setAcceleration(accelaration); }
            inline void setPosition(const EngineVector2D& position) noexcept { movement->setPosition(position); }
            inline void setVelocity(const EngineVector2D& velocity) noexcept { movement->setVelocity(velocity); }

            inline void setHitbox(int x, int y, int width, int height) noexcept { movement->getHitbox().setRect(x, y, width, height); }
    };
}