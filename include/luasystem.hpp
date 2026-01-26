#pragma once

#include <string>

#include "constantes.hpp"
#include "tool/vectors.hpp"

#define USERDATA_LUAVECTOR2D "Vector2D"

namespace exocet {
        class LuaSystem: public sol::state {
        private:
            Handler* handler;

            void initUserdateLuaVector2D();

            void initEngine();
            void initEntity();

            void preloadPackages(const std::string pathPackage, const std::string name);
        public:
            LuaSystem(Handler* handler);
    };
}