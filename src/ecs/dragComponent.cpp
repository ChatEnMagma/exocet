#include "ecs/dragComponent.hpp"
#include "handler.hpp"

using namespace exocet;
using namespace std;

void DragComponent::init() noexcept {
    if(!entity->hasComponent<MovementComponent>()) {
        movement = &entity->addComponent<MovementComponent>();
    } else {
        movement = &entity->getComponent<MovementComponent>();
    }

    drag = false;
}

void DragComponent::update() noexcept {
    drag = handler.getButton(0) && movement->getHitbox().isInsideMouse();
}