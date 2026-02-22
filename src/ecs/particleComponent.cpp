#include "ecs/particleComponent.hpp"

using namespace exocet;
using namespace std;

void ParticleComponent::init() noexcept {
    if(!entity->hasComponent<MovementComponent>()) {
        movement = &entity->addComponent<MovementComponent>();
    } else {
        movement = &entity->getComponent<MovementComponent>();
    }

    time = PARTICLE_DEFAULT_TIME;
}

void ParticleComponent::update() noexcept {
    if(time == 0) entity->destroy();
    time--;

    movement->move();
}