#pragma once

#include "physicComponent.hpp"

namespace exocet {
    class AnchorComponent: public Component {
        private:
            PhysicComponent* physic;
        public:
            using Component::Component;
            ~AnchorComponent() = default;

            void init() noexcept override;

            inline bool isCollide(Entity& e) const { return physic->isCollide(e); }

            inline const EngineVector2D& getPosition() const noexcept { return physic->getPosition(); }

            void setPosition(const EngineVector2D& position) noexcept { return physic->setPosition(position); }

            void setHitbox(int x, int y, int width, int height) noexcept { physic->setHitbox(x, y, width, height); }
    };
}