#include "ecs/physicComponent.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

void PhysicComponent::init() noexcept {
    if(!entity->hasComponent<HitboxComponent>()) {
        hitbox = &entity->addComponent<HitboxComponent>();
    } else {
        hitbox = &entity->getComponent<HitboxComponent>();
    }

    movement = &entity->getComponent<MovementComponent>();

    setSpeed(DoubleVector2D(PHYSIC_DEFAULT_SPEED, PHYSIC_DEFAULT_SPEED));
    setMaxSpeed(DoubleVector2D(PHYSIC_DEFAULT_SPEED, PHYSIC_DEFAULT_SPEED));
    setFriction(DoubleVector2D(0.4f, 0.4f));

    setMasse(PHYSIC_DEFALULT_MASSE);
}

void PhysicComponent::collisionWithPhysicEntity(Entity* e) {
    PhysicComponent& e_physic = e->getComponent<PhysicComponent>();
    
    auto sMid = getHitbox()->getCenter();
    auto oMid = e_physic.getHitbox()->getCenter();

    auto dir = DoubleVector2D(
        (oMid.x - sMid.x) / e_physic.getHitbox()->getWidth() / 2, 
        (oMid.y - sMid.y) / e_physic.getHitbox()->getHeight() / 2
    );
    auto absDir = dir.abs();

    if(abs(absDir.x - absDir.y) < .0001) {
        if(absDir.x > 0) { movement->acc.x = 0; movement->acc.x = 0; }
        if(absDir.y > 0) { movement->acc.y = 0; movement->acc.y = 0; }

        if((rand() % 2) == 0) {
            movement->vel.x = -movement->vel.x;
            movement->acc.x = 0;
        } else {
            movement->vel.y = -movement->vel.y;
            movement->acc.y = 0;
        }
    } else if(absDir.x > absDir.y) {
        if(absDir.x > 0) movement->acc.x = 0;

        movement->vel.x = -movement->vel.x * e_physic.getMasse();
        movement->acc.x = 0;
    } else {
        if(absDir.y > 0) movement->acc.y = 0;

        movement->vel.y = -movement->vel.y * e_physic.getMasse();
        movement->acc.y = 0;
    }
}

void PhysicComponent::update() noexcept {
    movement->move();
}

void PhysicComponent::render() noexcept {
    if(!hitbox->isInsideScreen()) return;

    // Render the hitbox
    if(handler->getGame()->isShowingHitbox()) {
        handler->getGraphic()->setRenderColor(0xff, 0xff, 0xff);
        handler->getGraphic()->renderLine(
            hitbox->getCenter(), 
            hitbox->getCenter() + movement->vel.clampMagnitude(getSpeed().x).scalar(getSpeed().x * 4));
    }
    // Render the pointer address
    if(handler->getGame()->isShowingPointerEntities()) {
        std::ostringstream text;
        text << std::hex << (intptr_t) entity;

        handler->getGraphic()->renderText(
            hitbox->getCenter().x - hitbox->getWidth() - handler->getGraphic()->getCamera()->getPosition().x,
            movement->getPosition().y - 32 - handler->getGraphic()->getCamera()->getPosition().y,
            hitbox->getWidth() * 2,
            32,
            text.str(),
            handler->getGraphic()->getFont("res/FreeRoyalty.ttf", 20)
        );
    }
}