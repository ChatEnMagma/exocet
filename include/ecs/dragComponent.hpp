#pragma once

#include "ecs/ecs.hpp"
#include "ecs/hitboxComponent.hpp"

namespace exocet {
    class DragComponent: public Component {
        private:
            int drag;
            HitboxComponent* hitbox;
            TransformComponent* transform;
        public:
            void init() override;
            void update() override;

            /**
             * \return If the entity is dragging
             */
            inline bool isDragging() const { return drag; }
    };
}