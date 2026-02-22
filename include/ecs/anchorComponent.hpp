#pragma once

#include "physicComponent.hpp"

namespace exocet {
    class AnchorComponent: public Component {
        private:
            PhysicComponent* physic;
        public:
            AnchorComponent() = default;

            void init() noexcept override;

            IntVector2D getPosition() const noexcept { return physic->getPosition(); }
            HitboxComponent* getHitbox() noexcept { return physic->getHitbox(); }

            void setPosition(const IntVector2D& position) noexcept { return physic->setPosition(position); }
    };
}