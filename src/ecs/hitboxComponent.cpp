#include "ecs/hitboxComponent.hpp"
#include "handler.hpp"

using namespace std;
using namespace exocet;

void HitboxComponent::init() {
    if(!entity->hasComponent<TransformComponent>()) {
        transform = &entity->addComponent<TransformComponent>();
    } else {
        transform = &entity->getComponent<TransformComponent>();
    }
    setHitbox(0, 0, HITBOX_DEFAULT_SIZE, HITBOX_DEFAULT_SIZE);
    setColor(0xff, 0x00, 0x00);
}

bool HitboxComponent::isCollide(HitboxComponent* hitbox) const {
    return !(
        hitbox->getLeft() > getRight() ||
        getMoveLeft() > hitbox->getRight() ||
        hitbox->getTop() > getBottom() ||
        getMoveTop() > hitbox->getBottom()
    );
}

bool HitboxComponent::isCollideHorizontal(HitboxComponent* hitbox) const {
    return (
        ((((float) (hitbox->getLeft() - getRight()) / transform->vel.x) > 1.f) ||
        (((float) (hitbox->getRight() - getLeft()) / transform->vel.x) > 1.f)) &&
        ((((float) (hitbox->getTop() - getBottom()) / transform->vel.y) < 0.f) ||
        (((float) (hitbox->getBottom() - getTop()) / transform->vel.y) < 0.f))
    );
}

bool HitboxComponent::isCollideVertical(HitboxComponent* hitbox) const {
    return (
        (((float) ((hitbox->getTop() - getBottom()) / transform->vel.y) > 1.f) ||
        (((float) (hitbox->getBottom() - getTop()) / transform->vel.y) > 1.f)) &&
        (((float) ((hitbox->getLeft() - getRight()) / transform->vel.x) < 0.f) ||
        (((float) (hitbox->getRight() - getLeft()) / transform->vel.x) < 0.f))
    );
}

void HitboxComponent::render() {
    if(!handler->isShowingHitbox()) return;

    handler->getGraphic()->setRenderColor(color[0], color[1], color[2]);
    handler->getGraphic()->renderRect( transform->pos + Vector2D<int>(x, y), w, h);
}