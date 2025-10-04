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
            inline Vector2D<int> getPosition() { return pos; }

            inline void setHandler(Handler* handler) { this->handler = handler; }
    };
}