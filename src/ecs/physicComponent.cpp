#include "ecs/physicComponent.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

void PhysicComponent::init() noexcept {
    if(!entity->hasComponent<MovementComponent>()) {
        movement = &entity->addComponent<MovementComponent>();
    } else {
        movement = &entity->getComponent<MovementComponent>();
    }

    setSpeed(DoubleVector2D(PHYSIC_DEFAULT_SPEED, PHYSIC_DEFAULT_SPEED));
    setMaxSpeed(DoubleVector2D(PHYSIC_DEFAULT_SPEED, PHYSIC_DEFAULT_SPEED));
    setFriction(DoubleVector2D(0.4f, 0.4f));

    setMasse(PHYSIC_DEFALULT_MASSE);
}

void PhysicComponent::collisionWithPhysicEntity([[maybe_use]] Entity& e) {
    
}

void PhysicComponent::update() noexcept {
    movement->move();
}

void PhysicComponent::render() noexcept {
    if(!movement->getHitbox().isInsideScreen()) return;

    // Render the hitbox
    if(handler.getGame().isShowingHitbox()) {
        handler.getGraphic().setRenderColor(0xff, 0xff, 0xff);
        handler.getGraphic().renderLine(
            movement->getPosition(), 
            movement->getPosition() + movement->getVelocity().clampMagnitude(getSpeed().x).scalar(getSpeed().x * 4));
    }
    // Render the pointer address
    if(handler.getGame().isShowingPointerEntities()) {
        std::ostringstream text;
        text << std::hex << (intptr_t) entity;

        handler.getGraphic().renderText(
            movement->getPosition().x - movement->getWidth() - handler.getGraphic().getCamera().getPosition().x,
            movement->getPosition().y - movement->getHeight() / 2 - 32 - handler.getGraphic().getCamera().getPosition().y,
            movement->getWidth() * 2,
            32,
            text.str(),
            handler.getGraphic().getFont("res/FreeRoyalty.ttf", 20)
        );
    }
}