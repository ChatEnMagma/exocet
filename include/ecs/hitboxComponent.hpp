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

            bool isInsideMouse() const;

            bool isOutsideScreen();
            inline void destroyOutsideScreen() { if(isOutsideScreen()) entity->destroy(); }

            // ALL GETTERS POINT HITBOX
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

            inline Vector2D<int> getOffset() const { return Vector2D<int>(x, y); }
            int getWidth() const {
                int tmp = INT32_MIN;
                for(Vector2D<int> p: polygons.getVertices()) {
                    tmp = std::max(tmp, p.x);
                    //cout << p << endl;
                }
                return tmp;
            }
            inline int getHeight() const {
                int tmp = INT32_MIN;
                for(Vector2D<int> p: polygons.getVertices())
                    tmp = std::max(tmp, p.y);
                return tmp;
            }

            inline void setOffset(int xoffset, int yoffset) { x = xoffset; y = yoffset; }
            inline void setSize(int width, int height) { w = width; h = height; }
            inline void setRect(int xpos, int ypos, int width, int height) {
                polygons = Polygon(xpos, ypos, width, height); shape = RECTANGULAR_SHAPE; 
            }
            inline void setPoly(Polygon polygon) { this->polygons = polygon; }
            inline void setHitbox(Polygon polygon) { polygons = polygon; }
            inline void setColor(Uint8 red, Uint8 green, Uint8 blue) { color[0] = red; color[1] = green; color[2] = blue; }

            inline int getPositionX() const { return transform->getPosition().x; }
            inline int getPositionY() const { return transform->getPosition().y; }
            inline Vector2D<int> getPosition() const { return transform->getPosition(); } 

            inline Uint8 getTypeShaped() const { return shape; }
            inline Polygon getPolygon() const { return polygons; }
            inline std::size_t length() const { return polygons.length(); }
    };
}