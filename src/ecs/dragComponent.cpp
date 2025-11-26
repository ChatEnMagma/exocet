#include "ecs/dragComponent.hpp"
#include "handler.hpp"

using namespace exocet;
using namespace std;

void DragComponent::init() {
    if(!entity->hasComponent<HitboxComponent>()) {
        hitbox = &entity->addComponent<HitboxComponent>();
    } else {
        hitbox = &entity->getComponent<HitboxComponent>();
    }
    transform = &entity->getComponent<TransformComponent>();
    drag = false;
}

void DragComponent::update() {
    drag = handler->getButton(0) && hitbox->isInsideMouse();
}