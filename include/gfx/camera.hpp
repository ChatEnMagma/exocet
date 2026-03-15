#pragma once

#include "ecs/components.hpp"
#include "tool/vectors.hpp"

namespace exocet {
    class Subsystem;

    class Camera {
        private:
            Subsystem& subsys;
            EngineVector2D pos;
        public:
            Camera(Subsystem& subsys): subsys(subsys) {}

            /**
             * \brief Center the camera on entity
             * \param entity The entity
             */
            void centerOnEntity(Entity* entity);
            /**
             * \return the position of offset camera
             */
            inline EngineVector2D getPosition() const noexcept { return pos; }
            inline void setPosition(const EngineVector2D position) noexcept { pos = position; }
    };
}