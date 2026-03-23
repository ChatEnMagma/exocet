#include "gfx/camera.hpp"
#include "ecs/ecs.hpp"
#include "subsystem.hpp"

using namespace std;
using namespace exocet;

void Camera::centerOnEntity(Entity* e) {
    // Check if the entity has the physicComponent
    if(!e->hasComponent<TransformComponent>()) 
        throw invalid_argument("this entity does not have TransfromComponent");

    auto pos = e->getComponent<TransformComponent>().getPosition();

    // Set the new offset
    this->pos.x = pos.x - subsys.getWinWidth() / 2;
    this->pos.y = pos.y - subsys.getWinHeight() / 2;
}