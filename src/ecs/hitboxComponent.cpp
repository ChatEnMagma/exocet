#include <climits>
#include <ranges>

#include "ecs/hitboxComponent.hpp"
#include "handler.hpp"

using namespace std;
using namespace exocet;

void HitboxComponent::init() noexcept {
    if(!entity->hasComponent<TransformComponent>()) {
        transform = &entity->addComponent<TransformComponent>();
    } else {
        transform = &entity->getComponent<TransformComponent>();
    }

    polygons = Polygon(0, 0, HITBOX_DEFAULT_SIZE, HITBOX_DEFAULT_SIZE);
    
    setColor(0xff, 0x00, 0x00);

    handler.getEntityManager().addToGroup(entity, GROUP_COLLIDER);
}

void projection(const Polygon& poly, const Vector2D<double> axis, double* max, double* min) noexcept {
    *max = *min = poly[0].dot(axis);

    for(size_t i = 1; i < poly.size(); i++) {
        double proj = poly[i].dot(axis);
        *min = std::min(*min, proj);
        *max = std::max(*max, proj);
    }
}

bool overlaps(double max1, double max2, double min1, double min2) noexcept {
    return !(min1 > max2 || min2 > max1);
}

bool HitboxComponent::isCollide(const HitboxComponent& hitbox) const noexcept {
    // Use the Separating Axis Theorem

    double max1, max2, min1, min2;

    // Get the transpos of the hitbox
    Polygon p1 = polygons.translate(transform->getPosition());
    Polygon p2 = hitbox.getPolygon().translate(hitbox.getTransform().getPosition());

    auto axes1 = p1.getAxes();
    auto axes2 = p2.getAxes();

    // Check axis of p1
    for(const Vector2D<double>& p: axes1) {
        projection(p1, p, &max1, &min1);
        projection(p2, p, &max2, &min2);

        if(!overlaps(max1, max2, min1, min2)) return false;
    }
    // Check acis of p2
    for(const Vector2D<double>& p: axes2) {
        projection(p1, p, &max1, &min1);
        projection(p2, p, &max2, &min2);

        if(!overlaps(max1, max2, min1, min2)) return false;
    }

    return true;
}

optional<Entity*> HitboxComponent::getCollide() const {
    auto group = handler.getEntityManager().getGroup(GROUP_COLLIDER);

    auto it = ranges::find_if(group, [this](const Entity* e) { return e != this->entity && this->isCollide(e->getComponent<HitboxComponent>()); } );

    if(it != group.end())
        return optional<Entity*>(*it);

    return nullopt;
}

vector<Entity*> HitboxComponent::getCollideEntities() const {
    auto group = handler.getEntityManager().getGroup(GROUP_COLLIDER);

    auto colliding = group
        | views::filter([this](const Entity* e) { return e != entity && e->hasComponent<HitboxComponent>(); })
        | views::filter([this](const Entity* e) { return this->isCollide(e->getComponent<HitboxComponent>()); });
    
    return { colliding.begin(), colliding.end() };
}

bool HitboxComponent::isCollideHorizontal(const HitboxComponent& hitbox) const noexcept {
    return transform->isMoving() && (
        ((((float) (hitbox.getLeft() - getRight()) / transform->getVelocity().x) > 1.f) ||
        (((float) (hitbox.getRight() - getLeft()) /transform->getVelocity().x) > 1.f)) &&
        ((((float) (hitbox.getUp() - getDown()) / transform->getVelocity().y) < 0.f) ||
        (((float) (hitbox.getDown() - getUp()) / transform->getVelocity().y) < 0.f))
    );
}

bool HitboxComponent::isCollideVertical(const HitboxComponent& hitbox) const noexcept {
    return transform->isMoving() && (
        (((float) ((hitbox.getUp() - getDown()) / transform->getVelocity().y) > 1.f) ||
        (((float) (hitbox.getDown() - getUp()) / transform->getVelocity().y) > 1.f)) &&
        (((float) ((hitbox.getLeft() - getRight()) / transform->getVelocity().x) < 0.f) ||
        (((float) (hitbox.getRight() - getLeft()) / transform->getVelocity().x) < 0.f))
    );
}

void HitboxComponent::render() noexcept {
    if(!isInsideScreen() || !handler.isShowingHitbox()) return;

    handler.getGraphic().setRenderColor(color[0], color[1], color[2]);
    handler.getGraphic().renderPolygon(getRenderPosition(), polygons);
}

bool HitboxComponent::isInsideMouse() const noexcept {
    auto pos = handler.getMousePosition() + handler.getGraphic().getCamera().getPosition();
    
    return (
        pos.x >= getLeft()  &&
        pos.x <= getRight() &&
        pos.y >= getUp()   &&
        pos.y <= getDown()
    );
}

bool HitboxComponent::isInsideScreen() const noexcept {
    auto posCam = handler.getGraphic().getCamera().getPosition();

    return (
        transform->getPosition().x > posCam.x - getWidth() && 
        transform->getPosition().x + getWidth() < posCam.x + handler.getWinWidth() + getWidth() &&
        transform->getPosition().y > posCam.y - getHeight() &&
        transform->getPosition().y + getHeight() < posCam.y + handler.getWinHeight() + getHeight()
    );
}
