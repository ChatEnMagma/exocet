#include "ecs/controllerDirectionsComponent.hpp"
#include "handler.hpp"

using namespace exocet;
using namespace std;

void ControllerDirectionsComponent::init() {
    if(!entity->hasComponent<HitboxComponent>()) {
        hitbox = &entity->addComponent<HitboxComponent>();
    } else {
        hitbox = &entity->getComponent<HitboxComponent>();
    }
                
    movement = &entity->getComponent<MovementComponent>();
    direction = DoubleVector2D::vectorZeros();
}

void ControllerDirectionsComponent::update() {
    movement->acc.x = clamp(movement->acc.x, -movement->getMaxSpeed().x, movement->getMaxSpeed().x);
    movement->acc.y = clamp(movement->acc.y, -movement->getMaxSpeed().y, movement->getMaxSpeed().y);

    if(abs(direction.x) > 0.05)
        movement->acc.x += movement->getSpeed().x;
    else movement->acc.x = 0;
    if(abs(direction.y) > 0.05)
        movement->acc.y += movement->getSpeed().y;
    else movement->acc.y = 0;
    
    movement->vel = direction.normalized() * movement->getAccelation();
}