#include "ecs/spriteComponent.hpp"
#include "handler.hpp"

using namespace exocet;
using namespace std;

void SpriteComponent::init() {
    if(!entity->hasComponent<TransformComponent>()) {
        transform = &entity->addComponent<TransformComponent>();
    } else {
        transform = &entity->getComponent<TransformComponent>();
    }

    tex = nullptr;

    setSize(0, 0);
}

SpriteComponent::~SpriteComponent() {
    if(tex != nullptr) {
        tex->clean();
    }
}

void SpriteComponent::render() {
    if(tex != nullptr)
        tex->render(transform->getPosition(), w, h);
}

void SpriteComponent::fitSizeWithHitbox() {
    if(entity->hasComponent<HitboxComponent>()) {
        HitboxComponent& hitbox = entity->getComponent<HitboxComponent>();
        setSize(hitbox.getWidth(), hitbox.getHeight());
    }
}