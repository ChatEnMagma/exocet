#include "ecs/spriteComponent.hpp"

#include "handler.hpp"

using namespace exocet;
using namespace std;

void SpriteComponent::init() {
    if(!entity->hasComponent<TransformComponent>())
        transform = &entity->addComponent<TransformComponent>();
    else
        transform = &entity->getComponent<TransformComponent>();

    fps = FPS;
    frame = 0;
    frameStart = SDL_GetTicks();
    
    a = 0;

    setSize(32, 32);
}

void SpriteComponent::update() {
    if(1000/fps < SDL_GetTicks() - frameStart ) {
        if(frame >= sprite->size() - 1)
            frame = 0;
        else
            frame++;
        frameStart = SDL_GetTicks();
    }
}

void SpriteComponent::render() {
    sprite->renderAngle(transform->getPosition(), a, w, h, frame);
}

void SpriteComponent::fitSizeWithHitbox() {
    if(entity->hasComponent<HitboxComponent>()) {
        HitboxComponent& hitbox = entity->getComponent<HitboxComponent>();
        setSize(hitbox.getWidth(), hitbox.getHeight());
    }
}