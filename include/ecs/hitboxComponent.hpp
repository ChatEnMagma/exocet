#pragma once

#include "ecs/transformComponent.hpp"

#include "tool/polygon.hpp"

namespace exocet {
    class HitboxComponent: public Component {
        private:
            int x, y, w, h;
            Polygon polygons;
            TransformComponent* transform;
            Uint8 shape;
            Uint8 color[3];
        public:
            enum SHAPES {
                POLYGON_SHAPE = 0,
                RECTANGULAR_SHAPE
            };

            void init() override;
            void render() override;

            bool isCollide(HitboxComponent* hitbox) const;
            bool isCollideHorizontal(HitboxComponent* hitbox) const;
            bool isCollideVertical(HitboxComponent* hitbox) const;

            /**
             * \return True if the mouse is inside the entity else false
             */
            bool isInsideMouse() const;
            /**
             * \return True if the entity is ouside the screen (depend of the camera) else false
             */
            bool isOutsideScreen();
            /**
             * \brief If the entity is outside the screen, then it destroyes
             */
            inline void destroyOutsideScreen() { if(isOutsideScreen()) entity->destroy(); }

            // ALL GETTERS POINT HITBOX
            /**
             * \return The focal point of the entity
             */
            inline Vector2D<int> getCenter() const { 
                return Vector2D<int>(
                    transform->getPosition().x + (x + getWidth()) / 2, 
                    transform->getPosition().y + (y + getHeight()) / 2
                ); 
            }
            int getLeft() const;
            int getRight() const;
            int getTop() const;
            int getBottom() const;

            inline float getMoveLeft() const { return transform->getVelocity().x + (float) getLeft(); }
            inline float getMoveRight() const { return transform->getVelocity().x + (float) getRight(); }
            inline float getMoveTop() const { return transform->getVelocity().y + (float) getTop(); }
            inline float getMoveBottom() const { return transform->getVelocity().y + (float) getBottom(); }
            /**
             * \return The width of the entity
             */
            int getWidth() const { return polygons.getWidth(); }
            /**
             * \return The height of the entity
             */
            int getHeight() const { return polygons.getHeight(); }
            /**
             * \brief Set a rectangular hitbox for the entity
             */
            inline void setRect(int xpos, int ypos, int width, int height) {
                polygons = Polygon(xpos, ypos, width, height); shape = RECTANGULAR_SHAPE; 
            }
            inline void setPolygon(Polygon polygon) { this->polygons = polygon; }
            inline void setHitbox(Polygon polygon) { polygons = polygon; }
            inline void setColor(Uint8 red, Uint8 green, Uint8 blue) { color[0] = red; color[1] = green; color[2] = blue; }

            inline int getPositionX() const { return transform->getPosition().x; }
            inline int getPositionY() const { return transform->getPosition().y; }
            inline Vector2D<int> getPosition() const { return transform->getPosition(); } 

            inline Uint8 getTypeShaped() const { return shape; }
            inline Polygon getPolygon() const { return polygons; }
    };
}