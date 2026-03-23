#include "ecs/transformComponent.hpp"
#include "handler.hpp"

using namespace std;
using namespace exocet;

void TransformComponent::update() noexcept {
    velocity += acceleration.scalar(handler.getDeltaTime());
    
    if(abs(velocity.x) < 0.001) velocity.x = 0;
    if(abs(velocity.y) < 0.001) velocity.y = 0;
}

EngineVector2D TransformComponent::computeNextMove() const {
    EngineVector2D nextMove;

    if(isMovingUp())
        nextMove.y = position.y + ceil(velocity.y);
    else if(isMovingDown())
        nextMove.y = position.y + floor(velocity.y);
    
    if(isMovingRight())
        nextMove.x = position.x + floor(velocity.x);
    else if(isMovingLeft())
        nextMove.x = position.x + ceil(velocity.x);
    
    return nextMove;
}

