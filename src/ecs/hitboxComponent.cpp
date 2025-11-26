#include <climits>

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

    polygons = Polygon(0, 0, HITBOX_DEFAULT_SIZE, HITBOX_DEFAULT_SIZE);
    shape = RECTANGULAR_SHAPE;

    setColor(0xff, 0x00, 0x00);
}

int HitboxComponent::getRight() const {
    int tmp = INT32_MIN;
    for(Vertex p: polygons.getVertices()) {
        tmp = std::max(tmp, p.x);
    }
    return tmp;
}
int HitboxComponent::getLeft() const {
    int tmp = INT32_MAX;
    for(Vertex p: polygons.getVertices()) {
        tmp = std::min(tmp, p.x);
    }
    return tmp;
}
int HitboxComponent::getTop() const {
    int tmp = INT32_MAX;
    for(Vertex p: polygons.getVertices()) {
        tmp = std::min(tmp, p.y);
    }
    return tmp;
}
int HitboxComponent::getBottom() const {
    int tmp = INT32_MIN;
    for(Vertex p: polygons.getVertices()) {
        tmp = std::max(tmp, p.y);
    }
    return tmp;
}


void projection(const Polygon& poly, const Vector2D<double> axis, double* max, double* min) {
    *max = *min = poly[0].convert<double>().dot(axis);

    for(size_t i = 1; i < poly.length(); i++) {
        double proj = poly[i].convert<double>().dot(axis);
        *min = std::min(*min, proj);
        *max = std::max(*max, proj);
    }
}

bool overlaps(double max1, double max2, double min1, double min2) {
    return !(min1 > max2 || min2 > max1);
}

bool HitboxComponent::isCollide(HitboxComponent* hitbox) const {
    // Use the Separating Axis Theorem

    double max1, max2, min1, min2;

    // Get the transpos of the hitbox
    Polygon p1 = polygons.translate(transform->getPosition());
    Polygon p2 = hitbox->getPolygon().translate(hitbox->getPosition());

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
    handler->getGraphic()->renderPolygon(transform->getPosition(), polygons);
}

bool HitboxComponent::isInsideMouse() const {
    Vector2D<int> pos = handler->getMousePosition() + handler->getGraphic()->getCamera()->getPosition();
    
    return (
        pos.x >= getLeft()  &&
        pos.x <= getRight() &&
        pos.y >= getTop()   &&
        pos.y <= getBottom()
    );
}

bool HitboxComponent::isOutsideScreen() {
    Vector2D<int> posCam = handler->getGraphic()->getCamera()->getPosition();
    return (
        (getRight() < posCam.x) ||
        (getLeft() > posCam.x + handler->getWinWidth()) ||
        (getBottom() > posCam.y + handler->getWinHeight()) ||
        (getTop() < posCam.y)
    );
}