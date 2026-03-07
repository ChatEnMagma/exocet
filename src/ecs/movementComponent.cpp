#include "ecs/movementComponent.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

void MovementComponent::move() noexcept {
    if(abs(vel.x) < 0.001) vel.x = 0;
    if(abs(vel.y) < 0.001) vel.y = 0;

    vel += acc.scalar(handler->getDeltaTime());
    
    if(isMovingRight())
        pos.x += ceil(vel.x);
    else if(isMovingLeft())
        pos.x += floor(vel.x);     

    if(isMovingUp())
        pos.y += floor(vel.y);
    else if(isMovingDown())
       pos.y += ceil(vel.y);
     
    vel *= friction;
}
