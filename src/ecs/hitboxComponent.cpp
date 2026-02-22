#include <climits>

#include "ecs/hitboxComponent.hpp"
#include "handler.hpp"

using namespace std;
using namespace exocet;

void HitboxComponent::init() noexcept {
    if(!entity->hasComponent<MovementComponent>()) {
        movement = &entity->addComponent<MovementComponent>();
    } else {
        movement = &entity->getComponent<MovementComponent>();
    }

    polygons = Polygon(0, 0, HITBOX_DEFAULT_SIZE, HITBOX_DEFAULT_SIZE);

    setColor(0xff, 0x00, 0x00);
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

bool HitboxComponent::isCollide(HitboxComponent* hitbox) const noexcept {
    // Use the Separating Axis Theorem

    double max1, max2, min1, min2;

    // Get the transpos of the hitbox
    Polygon p1 = polygons.translate(movement->getPosition().convert<double>());
    Polygon p2 = hitbox->getPolygon().translate(hitbox->getPosition().convert<double>());

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

bool HitboxComponent::isCollideHorizontal(HitboxComponent* hitbox) const noexcept {
    return movement->vel.x != 0 && movement->vel.y != 0 && (
        ((((float) (hitbox->getLeft() - getRight()) / movement->vel.x) > 1.f) ||
        (((float) (hitbox->getRight() - getLeft()) / movement->vel.x) > 1.f)) &&
        ((((float) (hitbox->getUp() - getDown()) / movement->vel.y) < 0.f) ||
        (((float) (hitbox->getDown() - getUp()) / movement->vel.y) < 0.f))
    );
}

bool HitboxComponent::isCollideVertical(HitboxComponent* hitbox) const noexcept {
    return movement->vel.x != 0 && movement->vel.y != 0 && (
        (((float) ((hitbox->getUp() - getDown()) / movement->vel.y) > 1.f) ||
        (((float) (hitbox->getDown() - getUp()) / movement->vel.y) > 1.f)) &&
        (((float) ((hitbox->getLeft() - getRight()) / movement->vel.x) < 0.f) ||
        (((float) (hitbox->getRight() - getLeft()) / movement->vel.x) < 0.f))
    );
}

void HitboxComponent::render() noexcept {
    if(!isInsideScreen() || !handler->isShowingHitbox()) return;

    handler->getGraphic()->setRenderColor(color[0], color[1], color[2]);
    handler->getGraphic()->renderPolygon(movement->getPosition(), polygons);
}

bool HitboxComponent::isInsideMouse() const noexcept {
    Vector2D<int> pos = handler->getMousePosition() + handler->getGraphic()->getCamera()->getPosition();
    
    return (
        pos.x >= getLeft()  &&
        pos.x <= getRight() &&
        pos.y >= getUp()   &&
        pos.y <= getDown()
    );
}

bool HitboxComponent::isInsideScreen() const noexcept {
    IntVector2D posCam = handler->getGraphic()->getCamera()->getPosition();

    return (
        movement->pos.x > posCam.x - getWidth() && 
        movement->pos.x + getWidth() < posCam.x + handler->getWinWidth() + getWidth() &&
        movement->pos.y > posCam.y - getHeight() &&
        movement->pos.y + getHeight() < posCam.y + handler->getWinHeight() + getHeight()
    );
}
