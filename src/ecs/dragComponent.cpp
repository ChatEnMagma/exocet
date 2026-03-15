#include "ecs/dragComponent.hpp"
#include "handler.hpp"

using namespace exocet;
using namespace std;

void DragComponent::init() noexcept {
    if(!entity->hasComponent<HitboxComponent>()) {
        hitbox = &entity->addComponent<HitboxComponent>();
    } else {
        hitbox = &entity->getComponent<HitboxComponent>();
    }
    movement = &entity->getComponent<MovementComponent>();
    drag = false;
}

void DragComponent::update() noexcept {
    drag = handler.getButton(0) && hitbox->isInsideMouse();
}