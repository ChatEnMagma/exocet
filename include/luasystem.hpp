#pragma once

#include <string>

#include "constantes.hpp"

namespace exocet {
    struct luaVector2D {
        public:
            sol::object x, y;
    };

    class LuaSystem: public sol::state {
        private:
            Handler* handler;

            void initEngine();
            void initEntity();

            void preloadPackages(const std::string pathPackage, const std::string name);
        public:
            LuaSystem(Handler* handler);
    };
}