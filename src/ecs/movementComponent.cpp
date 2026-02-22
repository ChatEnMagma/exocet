#include "ecs/movementComponent.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

void MovementComponent::move() noexcept {
    vel.x = clamp(vel.x, -maxSpeed.x * (1 + maxSpeed.x), maxSpeed.x * (1 + maxSpeed.x));
    vel.y = clamp(vel.y, -maxSpeed.y * (1 + maxSpeed.y), maxSpeed.y * (1 + maxSpeed.y));

    auto norm = computeMove();
                
    if(isMovingRight())
        pos.x += (int) floor(norm.x);
    else if(isMovingLeft())
        pos.x += (int) ceil(norm.x);
                
    if(isMovingUp())
        pos.y += (int) ceil(norm.y);
    else if(isMovingDown())
        pos.y += (int) floor(norm.y);

    vel *= friction;
}
