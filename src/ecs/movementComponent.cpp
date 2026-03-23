#include "ecs/movementComponent.hpp"
#include <cmath>

#include "handler.hpp"

using namespace std;
using namespace exocet;

void MovementComponent::init() noexcept {
    if(!entity->hasComponent<HitboxComponent>()) {
        hitbox = &entity->addComponent<HitboxComponent>();
    } else {
        hitbox = &entity->getComponent<HitboxComponent>();
    }
    transform = &entity->getComponent<TransformComponent>();

    setSpeed(EngineVector2D(1.f, 1.f));
    setMaxSpeed(EngineVector2D(std::numeric_limits<double>::max(), std::numeric_limits<double>::max()));
}

void MovementComponent::move() noexcept {
    setAcceleration({
            clamp(getAcceleration().x, -getMaxSpeed().x, getMaxSpeed().x),
            clamp(getAcceleration().y, -getMaxSpeed().y, getMaxSpeed().y)
        }
    );

    auto& state = handler.getState();
    auto nextMove = transform->computeNextMove();
    
    double left = getPosition().x + getWidth() / 2;
    double right = getPosition().x - getWidth() / 2;
    double up = getPosition().y - getHeight() / 2;
    double down = getPosition().y + getHeight() / 2;

    bool collide;

    auto posTile = [](double tile) noexcept { return trunc(tile / Tile::size) * Tile::size; };

    if(transform->isMovingRight()) {
        double tx = nextMove.x + getWidth() / 2;

        collide = false;

        for(double ty = up; ty <= down; ty++)
            collide |= state.getTileFlags({tx, ty}, TILE_FALGS::SOLID_LEFT_TILE);

        if(!collide) {
            transform->computeRight();
        } else {
            transform->setPositionX(posTile(tx) - getWidth() / 2 - 1);
            transform->setAccelerationX(0.f);
        }
    } else if(transform->isMovingLeft()) {
        double tx = nextMove.x - getWidth() / 2;

        collide = false;

        for(double ty = up; ty <= down; ty++)
            collide |= state.getTileFlags({tx, ty}, TILE_FALGS::SOLID_RIGHT_TILE);

        if(!collide) {
            transform->computeLeft(); 
        } else {
            transform->setPositionX(posTile(tx) + Tile::size + getWidth() / 2);
            transform->setAccelerationX(0.f);
        }
    }

    if(transform->isMovingUp()) {
        double ty = nextMove.y - getHeight() / 2;

        collide = false;

        for(double tx = right; tx <= left; tx++)
            collide |= state.getTileFlags({tx, ty}, TILE_FALGS::SOLID_DOWN_TILE);

        if(!collide) {
            transform->computeUp();
        } else {
            transform->setPositionY(posTile(ty) + Tile::size + getHeight() / 2);
            transform->setAccelerationY(0.f);
        }
    } else if(transform->isMovingDown()) {
        double ty = nextMove.y + getHeight() / 2;

        collide = false;

        for(double tx = right; tx <= left; tx++)
            collide |= state.getTileFlags({tx, ty}, TILE_FALGS::SOLID_UP_TILE);

        if(!collide) {
            transform->computeDown();
        } else {
            transform->setPositionY(posTile(ty) - getHeight() / 2 - 1);
            transform->setAccelerationY(0.f);
        }
    }
     
    transform->computeFriction(friction);
}
