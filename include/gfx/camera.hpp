#pragma once

#include "ecs/components.hpp"
#include "tool/vectors.hpp"

namespace exocet {
    class Camera {
        private:
            Handler* handler;
            Vector2D<int> pos;
        public:
            void centerOnEntity(Entity* entity);
            inline Vector2D<int> getPosition() { return pos; }

            inline void setHandler(Handler* handler) { this->handler = handler; }
    };
}