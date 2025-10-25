#include "ecs/physicComponent.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

void PhysicComponent::init() {
    if(!entity->hasComponent<HitboxComponent>()) {
        hitbox = &entity->addComponent<HitboxComponent>();
    } else {
        hitbox = &entity->getComponent<HitboxComponent>();
    }

    transform = &entity->getComponent<TransformComponent>();

    setSpeed(PHYSIC_DEFAULT_SPEED);
    setMaxSpeed(PHYSIC_DEFAULT_MAXSPEED);
    setFriction(PHYSIC_DEFAULT_FRICTION);

    setMasse(PHYSIC_DEFALULT_MASSE);

    handler->getEntityManager()->addToGroup(entity, GROUP_COLLIDER);
}

void PhysicComponent::collisionWithPhysicEntity(Entity* e) {
    PhysicComponent* e_physic = &e->getComponent<PhysicComponent>();
    Vector2D<float> m_v1 = transform->vel;
    Vector2D<float> e_v1 = e_physic->transform->vel;

    Vector2D<float> m_v2, e_v2;
    
    /*// Formular one-dimensional Newtonian

    // this-vel = (this->masse - e->masse) / (this->masse + e->masse) * this->vel + (2 * e->masse) / (this->masse + e->masse) * e->vel
    Vector2D<float> newVt = vt1.scalar((getMasse() - e_physic->getMasse()) / (getMasse() + e_physic->getMasse())) + 
                             ve1.scalar((2 * e_physic->getMasse()) / (getMasse() + e_physic->getMasse()));

    // (2 * this->masse) / (this->masse + e->masse) * this->vel + (e->masse - this->masse) / (this->masse + e->masse) * e->vel
    Vector2D<float> newVe =  vt1.scalar((2 * getMasse()) / (getMasse() + e_physic->getMasse())) +
                                ve1.scalar((e_physic->getMasse() - getMasse()) / (getMasse() + e_physic->getMasse()));
    */

    Vector2D<float> vCollide = e_physic->getVelocity() - getVelocity();
    float distance = Vector2D<float>::twoVectorsMagnitude(getVelocity(), e_physic->getVelocity());
    Vector2D<float> vCollideNorm = Vector2D<float>(vCollide.x / distance, vCollide.y / distance);

    Vector2D<float> vRelativeVel = getVelocity() - e_physic->getVelocity();

    float vSpeed = vRelativeVel.x * vCollideNorm.x + vRelativeVel.y * vCollideNorm.y;
    float impulse = 2 * vSpeed / (getMasse() + e_physic->getMasse());

    if(speed <= 0) return;

    transform->vel -= vCollideNorm.scalar(impulse * e_physic->getMasse());
    e_physic->transform->vel += vCollideNorm.scalar(impulse * getMasse());
}

void PhysicComponent::move() {
    // set the limite of velocity of abscie
    if(getVelocity().x > maxSpeed) {
        transform->vel.x = maxSpeed;
    } else if(getVelocity().x < -maxSpeed) {
        transform->vel.x = -maxSpeed;
    }

    // set the limite of velocity of ordonée
    if(getVelocity().y > maxSpeed) {
        transform->vel.y = maxSpeed;
    } else if(getVelocity().y < -maxSpeed) {
        transform->vel.y = -maxSpeed;
    }

    setPosition(transform->move());
    setVelocity(getVelocity().scalar(friction));
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

void PhysicComponent::update() {
    move();
}

void PhysicComponent::render() {
    // Render the hitbox
    if(handler->getGame()->isShowingHitbox()) {
        Vector2D<float> norm = transform->vel.normalized();
        float vSpeed = transform->vel.x * norm.x + transform->vel.y * norm.y;

        handler->getGraphic()->setRenderColor(0xff, 0xff, 0xff);
        handler->getGraphic()->renderLine(
            hitbox->getCenter(), 
            hitbox->getCenter() + norm.scalar(vSpeed * hitbox->getWidth() / 4).convert<int>() );
    }
    // Render the pointer address
    if(handler->getGame()->isShowingPointerEntities()) {
        std::ostringstream text;
        text << std::hex << (intptr_t) entity;

        handler->getGraphic()->renderText(
            hitbox->getCenter().x - hitbox->getWidth() - handler->getGraphic()->getCamera()->getPosition().x,
            transform->getPosition().y - 32 - handler->getGraphic()->getCamera()->getPosition().y,
            hitbox->getWidth() * 2,
            32,
            text.str(),
            handler->getGraphic()->freeRoyalty
        );
    }
}