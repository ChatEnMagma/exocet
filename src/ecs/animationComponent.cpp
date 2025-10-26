#include "ecs/animationComponent.hpp"

#include "handler.hpp"

using namespace exocet;
using namespace std;

void AnimationComponent::init() {
    if(!entity->hasComponent<TransformComponent>())
        transform = &entity->addComponent<TransformComponent>();
    else
        transform = &entity->getComponent<TransformComponent>();

    fps = FPS;
    frame = 0;

    setSize(32, 32);
}

void AnimationComponent::update() {
    if(frame >= getFrame() - 1)
        frame = 0;
    else
        frame++;
}

void AnimationComponent::render() {
    if(!tex.empty())
        tex[frame]->render(transform->getPosition(), w, h);
}

void AnimationComponent::fitSizeWithHitbox() {
    if(entity->hasComponent<HitboxComponent>()) {
        HitboxComponent& hitbox = entity->getComponent<HitboxComponent>();
        setSize(hitbox.getWidth(), hitbox.getHeight());
    }
}