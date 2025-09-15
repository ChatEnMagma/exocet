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
    Vector2D<float> vt1 = transform->vel;
    Vector2D<float> ve1 = e_physic->transform->vel;
    
    // Formular one-dimensional Newtonian

    // this-vel = (this->masse - e->masse) / (this->masse + e->masse) * this->vel + (2 * e->masse) / (this->masse + e->masse) * e->vel
    Vector2D<float> newVt = vt1.scalar((getMasse() - e_physic->getMasse()) / (getMasse() + e_physic->getMasse())) + 
                             ve1.scalar((2 * e_physic->getMasse()) / (getMasse() + e_physic->getMasse()));

    // (2 * this->masse) / (this->masse + e->masse) * this->vel + (e->masse - this->masse) / (this->masse + e->masse) * e->vel
    Vector2D<float> newVe =  vt1.scalar((2 * getMasse()) / (getMasse() + e_physic->getMasse())) +
                                ve1.scalar((e_physic->getMasse() - getMasse()) / (getMasse() + e_physic->getMasse()));
    
    if(hitbox->isCollideHorizontal(e_physic->getHitbox())) {
        transform->vel.x = newVt.x;
        e_physic->transform->vel.x = newVe.x;
    }
    if(hitbox->isCollideVertical(e_physic->getHitbox())) {
        transform->vel.y = newVt.y;
        e_physic->transform->vel.y = newVe.y;
    } 
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
    vector<Entity*> entities = getCollideEntities();

    // Calcul new vectors for each collisions
    if(!entities.empty()) {
        for(auto& e: entities) {
            collisionWithPhysicEntity(e);
        }
    }

    setPosition(transform->move());

    setVelocity(getVelocity().scalar(friction));
}

vector<Entity*> PhysicComponent::getCollideEntities() {
    vector<Entity*> entities;

    for(auto& e: handler->getEntityManager()->getGroup(GROUP_COLLIDER)) {
        if(e == entity) continue;
        if(hitbox->isCollide(&e->getComponent<HitboxComponent>())) // if this physicCompenent is well collid with the other entity grouped collide
            entities.emplace_back(e);
    }
    return entities;
}

void PhysicComponent::update() {
    move();
}

void PhysicComponent::render() {

}