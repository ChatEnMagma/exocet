#pragma once

#include <string>

#include "constantes.hpp"
#include "tool/vectors.hpp"
#include "tool/polygon.hpp"

#define USERTYPE_LUAVECTOR2D "Vector2D"
#define USERTYPE_POLYGON "Polygon"

namespace exocet {
        class LuaSystem: public sol::state {
        private:
            Handler* handler;

            void initRectClass();

            void initUsertypeLuaVector2D();
            void initUsertypePolygon();

            void initEngine();
            void initEntity();

            void preloadPackages(const std::string pathPackage, const std::string name);
        public:
            LuaSystem(Handler* handler);
    };
}