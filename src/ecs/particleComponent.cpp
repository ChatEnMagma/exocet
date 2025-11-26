#include "ecs/particleComponent.hpp"

using namespace exocet;
using namespace std;

void ParticleComponent::init() {
    if(!entity->hasComponent<TransformComponent>()) {
        transform = &entity->addComponent<TransformComponent>();
    } else {
        transform = &entity->getComponent<TransformComponent>();
    }

    time = PARTICLE_DEFAULT_TIME;
}

void ParticleComponent::update() {
    if(time < 0) entity->destroy();
    time--;

    transform->setPosition(transform->move());
}