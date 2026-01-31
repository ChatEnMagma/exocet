#pragma once

#include "physicComponent.hpp"

namespace exocet {
    class AnchorComponent: public Component {
        private:
            PhysicComponent* physic;
        public:
            void init() override;

            IntVector2D getPosition() const { return physic->getPosition(); }
            HitboxComponent* getHitbox() { return physic->getHitbox(); }

            void setPosition(const IntVector2D& position) { return physic->setPosition(position); }
    };
}