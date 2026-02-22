#include "gfx/camera.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

void Camera::centerOnEntity(Entity* e) {
    // Check if the entity has the physicComponent
    if(!e->hasComponent<HitboxComponent>()) 
        throw invalid_argument("this entity does not have HitboxComponent");

    auto center = e->getComponent<HitboxComponent>().getCenter();

    // Set the new offset
    this->pos.x = static_cast<int>(center.x - handler->getWinWidth() / 2);
    this->pos.y = static_cast<int>(center.y - handler->getWinHeight() / 2);
}