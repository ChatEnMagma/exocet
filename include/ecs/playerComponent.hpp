#pragma once

#include "physicComponent.hpp"

namespace exocet {
    class PlayerComponent: public Component {
        private:
            PhysicComponent* physic;
        public:
            void init() override;

            void update() override;
            void render() override;

            inline PhysicComponent* getPhysic() { return physic; }
            inline void setPointsPosition(int xpos, int ypos) { physic->setPointsPosition(xpos, ypos); }
    };
}