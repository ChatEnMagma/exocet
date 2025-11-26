#pragma once

#include "ecs/transformComponent.hpp"

namespace exocet {
    class ParticleComponent: public Component {
        private:
            TransformComponent* transform;
            int time;
        public:
            void init() override;
            void update() override;

            inline void setPosition(const Vector2D<int> position) { transform->setPosition(position); }
            inline void setPointsPosition(int xpos, int ypos) { transform->setPointsPosition(xpos, ypos); }
            inline void setVelocity(const Vector2D<float> velocity) { transform->setVelocity(velocity); }
            inline void setPointsVelocity(float xvel, float yvel) { transform->setPointsVelocity(xvel, yvel); }
            inline void setTime(int time) { this->time = time; }
            inline int getTime() const { return time; }
    };
}