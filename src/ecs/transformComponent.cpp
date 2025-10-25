#include "ecs/transformComponent.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

Vector2D<int> TransformComponent::move() const {
    Vector2D<int> tmp = pos;
                
    if(isMovingRight())
        tmp.x += (int) floor(vel.x);
    else if(isMovingLeft())
        tmp.x += (int) ceil(vel.x);
                
    if(isMovingUp())
        tmp.y += (int) ceil(vel.y);
    else if(isMovingDown())
        tmp.y += (int) floor(vel.y);

    return tmp;
}