#pragma once

#include "ecs/ecs.hpp"
#include "ecs/movementComponent.hpp"

namespace exocet {
    class DragComponent: public Component {
        private:
            int drag;
            MovementComponent* movement;
        public:
            using Component::Component;
            DragComponent() = default;

            void init() noexcept override;
            void update() noexcept override;

            /**
             * \return If the entity is dragging
             */
            inline bool isDragging() const noexcept { return drag; }
    };
}