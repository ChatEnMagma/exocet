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

    handler->getEntityManager()->addToGroup(entity, GROUP_COLLIDER);
}

void PhysicComponent::collisionWithPhysicEntity(Entity* e) {
    PhysicComponent* e_physic = &e->getComponent<PhysicComponent>();
    //Vector2D<float> m_v1 = movement->vel;
    //Vector2D<float> e_v1 = e_physic->movement->vel;

    DoubleVector2D m_v2, e_v2;
    
    /*// Formular one-dimensional Newtonian

    // this-vel = (this->masse - e->masse) / (this->masse + e->masse) * this->vel + (2 * e->masse) / (this->masse + e->masse) * e->vel
    Vector2D<float> newVt = vt1.scalar((getMasse() - e_physic->getMasse()) / (getMasse() + e_physic->getMasse())) + 
                             ve1.scalar((2 * e_physic->getMasse()) / (getMasse() + e_physic->getMasse()));

    // (2 * this->masse) / (this->masse + e->masse) * this->vel + (e->masse - this->masse) / (this->masse + e->masse) * e->vel
    Vector2D<float> newVe =  vt1.scalar((2 * getMasse()) / (getMasse() + e_physic->getMasse())) +
                                ve1.scalar((e_physic->getMasse() - getMasse()) / (getMasse() + e_physic->getMasse()));
    */

    auto vCollide = e_physic->getVelocity() - getVelocity();
    float distance = DoubleVector2D::twoVectorsMagnitude(getVelocity(), e_physic->getVelocity());
    auto vCollideNorm = DoubleVector2D(vCollide.x / distance, vCollide.y / distance);

    auto vRelativeVel = getVelocity() - e_physic->getVelocity();

    float vSpeed = vRelativeVel.x * vCollideNorm.x + vRelativeVel.y * vCollideNorm.y;
    float impulse = 2 * vSpeed / (getMasse() + e_physic->getMasse());

    movement->vel -= vCollideNorm.scalar(impulse * e_physic->getMasse());
    e_physic->movement->vel += vCollideNorm.scalar(impulse * getMasse());
}

vector<Entity*> PhysicComponent::getCollideEntities() {
    vector<Entity*> entities = {}; // empty vector

    for(auto& e: handler->getEntityManager()->getGroup(GROUP_COLLIDER)) {
        if(e == entity) continue;
        // if this physicCompenent is well collid with the other entity grouped collide
        if(hitbox->isCollide(&e->getComponent<HitboxComponent>())) {
            entities.emplace_back(e);
        }
    }
    return entities;
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
            hitbox->getCenter().convert<int>(), 
            (hitbox->getCenter() + movement->computeMove() * movement->getSpeed()).convert<int>());
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