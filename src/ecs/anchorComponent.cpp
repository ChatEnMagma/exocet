#include "ecs/anchorComponent.hpp"

using namespace exocet;
using namespace std;

void AnchorComponent::init() {
    if(!entity->hasComponent<PhysicComponent>())
        physic = &entity->addComponent<PhysicComponent>();
    physic = &entity->getComponent<PhysicComponent>();

    physic->setMasse(MAXFLOAT);
    physic->setFriction(0);
    physic->setSpeed(0);
}