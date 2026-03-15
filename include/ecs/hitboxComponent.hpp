#pragma once

#include "ecs/movementComponent.hpp"

#include "tool/polygon.hpp"

namespace exocet {
    class HitboxComponent: public Component {
        private:
            Polygon polygons;
            MovementComponent* movement;
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
            inline EngineVector2D getCenter() const noexcept { return movement->pos.convert<double>() + EngineVector2D(getWidth() / 2, getHeight() / 2); }
            double getLeft() const noexcept { return polygons.getLeft() + static_cast<double>(movement->pos.x); }
            double getRight() const noexcept { return polygons.getRight() + static_cast<double>(movement->pos.x); }
            double getUp() const noexcept { return polygons.getUp() + static_cast<double>(movement->pos.y); }
            double getDown() const noexcept { return polygons.getDown() + static_cast<double>(movement->pos.y); }

            inline double getMovementLeft() const noexcept { return movement->getVelocity().x + getLeft(); }
            inline double getMovementRight() const noexcept { return movement->getVelocity().x + getRight(); }
            inline double getMovementUp() const noexcept { return movement->getVelocity().y + getUp(); }
            inline double getMovementDown() const noexcept { return movement->getVelocity().y + getDown(); }
            /**
             * \return The width of the entity
             */
            inline int getWidth() const noexcept { return polygons.getWidth(); }
            /**
             * \return The height of the entity
             */
            inline int getHeight() const noexcept { return polygons.getHeight(); }
            /**
             * \brief Set a rectangular hitbox for the entity
             */
            inline void setRect(int xpos, int ypos, int width, int height) noexcept { polygons = Polygon(xpos, ypos, width, height); }
            inline void setHitbox(const Polygon& polygon) noexcept { polygons = polygon; }
            inline void setColor(Uint8 red, Uint8 green, Uint8 blue) noexcept { color[0] = red; color[1] = green; color[2] = blue; }

            inline int getPositionX() const noexcept { return movement->getPosition().x; }
            inline int getPositionY() const noexcept { return movement->getPosition().y; }
            inline EngineVector2D getPosition() const noexcept { return movement->getPosition(); } 

            inline const Polygon& getPolygon() const noexcept { return polygons; }
    };
}