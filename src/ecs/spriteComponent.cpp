#include "ecs/spriteComponent.hpp"

#include "handler.hpp"

using namespace exocet;
using namespace std;

void SpriteComponent::init() noexcept {    
    if(!entity->hasComponent<MovementComponent>())
        movement = &entity->addComponent<MovementComponent>();
    else
        movement = &entity->getComponent<MovementComponent>();

    fps = FPS;
    frame = 0;
    frameStart = SDL_GetTicks64();
    
    a = 0;

    fitSizeWithHitbox();
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
    if(movement->getHitbox().isInsideScreen())
        sprite->renderAngle(movement->getHitbox().getRenderPosition(), a, w, h, frame);
}