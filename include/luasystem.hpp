#pragma once

#include <string>

#include "constantes.hpp"

namespace exocet {
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