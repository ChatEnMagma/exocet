#pragma once

#include "constantes.hpp"

namespace exocet {
    class LuaSystem: public sol::state {
        private:
            void initEngine();
            void initEntity();
        public:
            LuaSystem(Handler* handler);
    };
}