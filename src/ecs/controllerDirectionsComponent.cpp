#include "ecs/controllerDirectionsComponent.hpp"
#include "handler.hpp"

using namespace exocet;
using namespace std;

void ControllerDirectionsComponent::init() {
    if(!entity->hasComponent<MovementComponent>()) {
        movement = &entity->addComponent<MovementComponent>();
    } else {
        movement = &entity->getComponent<MovementComponent>();
    }

    direction = EngineVector2D::vectorZeros();
}

void ControllerDirectionsComponent::update() {
    if(abs(direction.x) > 0.05)
        movement->setAccelerationX(movement->getAcceleration().x + movement->getSpeed().x);
    else movement->setAccelerationX(0.f);
    if(abs(direction.y) > 0.05)
        movement->setAccelerationY(movement->getAcceleration().y + movement->getSpeed().y);
    else movement->setAccelerationY(0.f);
    
    movement->setVelocity(direction.normalized() * movement->getAcceleration());
}