#pragma once

#include "ecs/components.hpp"
#include "tool/vectors.hpp"

namespace exocet {
    class Camera {
        private:
            Handler* handler;
            Vector2D<int> pos;
        public:
            /**
             * \brief Center the camera on entity
             * \param entity The entity
             */
            void centerOnEntity(Entity* entity);
            /**
             * \return the position of offset camera
             */
            inline IntVector2D getPosition() const noexcept { return pos; }
            inline void setPosition(const IntVector2D position) noexcept { pos = position; }

            inline void setHandler(Handler* handler) noexcept { this->handler = handler; }
    };
}