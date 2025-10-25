#include "gfx/camera.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

void Camera::centerOnEntity(Entity* e) {
    // Check if the entity has the physicComponent
    if(!e->hasComponent<PhysicComponent>()) {
        cout << "Warning: `" << e->getTag() << "` does not have physicComponent" << endl;
        return;
    }

    auto& e_physic = e->getComponent<PhysicComponent>();

    // Set the new offset
    this->pos.x = e_physic.getPosition().x - handler->getWinWidth() / 2 + e_physic.getHitbox()->getWidth() / 2;
    this->pos.y = e_physic.getPosition().y - handler->getWinHeight() / 2 + e_physic.getHitbox()->getHeight() / 2;
}