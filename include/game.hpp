#pragma once

#include "constantes.hpp"
#include "subsystem.hpp"

#include "state/states.hpp"

namespace exocet {
    class Game {
        private:
            Handler* handler = nullptr;

            StateManager* sManager;
            lua_State* lua;
            
            bool showingHitbox = false;
        public:
            Game(Subsystem* subsystem);

            void update();
            void render();

            inline bool isShowingHitbox() const { return showingHitbox; }
            inline void showHitbox() { showingHitbox = true; }
            inline void unshowHitbox() { showingHitbox = false; }

            inline State* getState() { return sManager->getState(); }
            inline EntityManager* getEntityManager() { return sManager->getEntityManager(); }
            inline void setState(std::size_t state) { sManager->setState(state); }

            inline Handler* getHandler() { return handler; };
            inline lua_State* getLua() { return lua; }
    };
}