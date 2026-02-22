#include "ecs/spriteComponent.hpp"

#include "handler.hpp"

using namespace exocet;
using namespace std;

void SpriteComponent::init() noexcept {
    if(!entity->hasComponent<MovementComponent>())
        movement = &entity->addComponent<MovementComponent>();
    else
        movement = &entity->getComponent<MovementComponent>();
    
    if(!entity->hasComponent<HitboxComponent>())
        hitbox = &entity->addComponent<HitboxComponent>();
    else
        hitbox = &entity->getComponent<HitboxComponent>();

    fps = FPS;
    frame = 0;
    frameStart = SDL_GetTicks64();
    
    a = 0;

    setSize(hitbox->getWidth(), hitbox->getHeight());
}

void SpriteComponent::update() noexcept {
    if(1000/fps < SDL_GetTicks64() - frameStart ) {
        if(frame >= sprite->size() - 1)
            frame = 0;
        else
            frame++;
        frameStart = SDL_GetTicks64();
    }
}

void SpriteComponent::render() noexcept {
    if(hitbox->isInsideScreen())
        sprite->renderAngle(movement->getPosition(), a, w, h, frame);
}