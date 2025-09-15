#include "gfx/camera.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

void Camera::centerOnEntity(Entity* e) {
    if(!e->hasComponent<PhysicComponent>()) return;

    auto& e_physic = e->getComponent<PhysicComponent>();

    this->pos.x = e_physic.getPosition().x - handler->getWinWidth() / 2 + e_physic.getHitbox()->getWidth() / 2;
    this->pos.y = e_physic.getPosition().y - handler->getWinHeight() / 2 + e_physic.getHitbox()->getHeight() / 2;
}