#pragma once

#include <string>

#include "constantes.hpp"
#include "tool/vectors.hpp"
#include "tool/polygon.hpp"

#define USERTYPE_LUAVECTOR2D "Vector2D"
#define USERTYPE_POLYGON "Polygon"
#define USERTYPE_SPRITE "Sprite"

#define USERTYPE_ENTITY "Entity"

#define USERTYPE_ANCHOR_COMPONENT "AnchorComponent"
#define USERTYPE_PHYSIC_COMPONENT "PhysicComponent"
#define USERTYPE_SPRITE_COMPONENT "SpriteComponent"
#define USERTYPE_SCRIPT_COMPONENT "ScriptComponent"

namespace exocet {
        class LuaSystem: public sol::state {
        private:
            Handler* handler;

            void initRectClass();

            void initUsertypeLuaVector2D();
            void initUsertypePolygon();
            void initUsertypeSprite();

            void initUsertypeEntity();
            void initUsertypeComponents();

            void initEngine();

            void preloadPackages(const std::string pathPackage, const std::string name);
        public:
            LuaSystem(Handler* handler);
            ~LuaSystem() {
                this->collect_garbage();

                this->clear_package_loaders();
            };
    };
}