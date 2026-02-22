#include <limits>

#include "ecs/anchorComponent.hpp"

using namespace exocet;
using namespace std;

void AnchorComponent::init() noexcept {
    if(!entity->hasComponent<PhysicComponent>())
        physic = &entity->addComponent<PhysicComponent>();
    physic = &entity->getComponent<PhysicComponent>();

    physic->setMasse(numeric_limits<double>::max());
    physic->setFriction(DoubleVector2D(0, 0));
    physic->setSpeed(DoubleVector2D());
}