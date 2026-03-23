#pragma once

#include "ecs/transformComponent.hpp"

#include "tool/polygon.hpp"

namespace exocet {
    class HitboxComponent: public Component {
        private:
            Polygon polygons;
            TransformComponent* transform;
            Uint8 color[3];
        public:
            using Component::Component;
            ~HitboxComponent() noexcept = default;

            void init() noexcept override;
            void render() noexcept override;

            std::optional<Entity*> getCollide() const;
            std::vector<Entity*> getCollideEntities() const;

            bool isCollide(const HitboxComponent& hitbox) const noexcept;
            bool isCollideHorizontal(const HitboxComponent& hitbox) const noexcept;
            bool isCollideVertical(const HitboxComponent& hitbox) const noexcept;

            /**
             * \return True if the mouse is inside the entity else false
             */
            bool isInsideMouse() const noexcept;
            /**
             * \return True if the entity is ouside the screen (depend of the camera) else false
             */
            bool isInsideScreen() const noexcept;
            /**
             * \brief If the entity is outside the screen, then it destroyes
             */
            inline void destroyOutsideScreen() noexcept { if(!isInsideScreen()) entity->destroy(); }

            // ALL GETTERS POINT HITBOX
            /**
             * \return The focal point of the entity
             */
            inline const EngineVector2D getCenter() const noexcept { return transform->getPosition() + EngineVector2D(getWidth() / 2, getHeight() / 2); }
            inline double getLeft() const noexcept { return polygons.getLeft() + transform->getPosition().x; }
            inline double getRight() const noexcept { return polygons.getRight() + transform->getPosition().x; }
            inline double getUp() const noexcept { return polygons.getUp() + transform->getPosition().y; }
            inline double getDown() const noexcept { return polygons.getDown() + transform->getPosition().y; }

            inline double getMovementLeft() const noexcept { return transform->getVelocity().x + getLeft(); }
            inline double getMovementRight() const noexcept { return transform->getVelocity().x + getRight(); }
            inline double getMovementUp() const noexcept { return transform->getVelocity().y + getUp(); }
            inline double getMovementDown() const noexcept { return transform->getVelocity().y + getDown(); }
            /**
             * \return The width of the entity
             */
            inline int getWidth() const noexcept { return polygons.getWidth(); }
            /**
             * \return The height of the entity
             */
            inline int getHeight() const noexcept { return polygons.getHeight(); }
            inline EngineVector2D getRenderPosition() const { return transform->getPosition() - EngineVector2D(getWidth() / 2, getHeight() / 2); }
            /**
             * \brief Set a rectangular hitbox for the entity
             */
            inline void setRect(int xpos, int ypos, int width, int height) noexcept { polygons = Polygon(xpos, ypos, width, height); }
            inline void setHitbox(const Polygon& polygon) noexcept { polygons = polygon; }
            inline void setColor(Uint8 red, Uint8 green, Uint8 blue) noexcept { color[0] = red; color[1] = green; color[2] = blue; }

            inline const Polygon& getPolygon() const noexcept { return polygons; }
            inline const TransformComponent& getTransform() const { return *transform; }
    };
}