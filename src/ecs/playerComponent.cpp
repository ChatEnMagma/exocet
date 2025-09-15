#include "ecs/playerComponent.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

void PlayerComponent::init() {
    if(!entity->hasComponent<PhysicComponent>()) {
        physic = &entity->addComponent<PhysicComponent>();
    } else {
        physic = &entity->getComponent<PhysicComponent>();
    }

    physic->getHitbox()->setSize(64, 64);
}

void PlayerComponent::update() {
    if(handler->getKey(SDLK_d)) {
        physic->getTransform()->vel += Vector2D<float>(physic->getSpeed(), 0.f);
    }
    if(handler->getKey(SDLK_q)) {
        physic->getTransform()->vel += Vector2D<float>(-physic->getSpeed(), 0.f);
    }
    if(handler->getKey(SDLK_z)) {
        physic->getTransform()->vel += Vector2D<float>(0.f, -physic->getSpeed());
    }
    if(handler->getKey(SDLK_s)) {
        physic->getTransform()->vel += Vector2D<float>(0.f, physic->getSpeed());
    }

    handler->getGraphic()->centerOnEntity(entity);
    
    //cout << physic->getTransform() << endl;
}

void PlayerComponent::render() {
    handler->getGraphic()->player->render(entity->getComponent<TransformComponent>().getPosition(), 64, 64);
}