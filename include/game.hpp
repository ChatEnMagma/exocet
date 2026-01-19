#pragma once

#include "constantes.hpp"
#include "subsystem.hpp"
#include "luasystem.hpp"

#include "state/state.hpp"

namespace exocet {
    class Game {
        private:
            Handler* handler = nullptr;
            StateManager* sManager = nullptr;

            bool showingHitbox = false;
            bool showingPointerEntities = false;

            LuaSystem* lua;

            /**
             * \brief Init lua with lib and functions
             */
            void initLua();
        public:
            Game(Subsystem* subsystem);

            void update();
            void render();

            /**
             * \return True if game show the all hitbox of entities
             */
            inline bool isShowingHitbox() const { return showingHitbox; }
            /**
             * \brief Show the hitbox all entities
             */
            inline void showHitbox() { showingHitbox = true; }
            /**
             * \brief Unshow the hitbox all entities
             */
            inline void unshowHitbox() { showingHitbox = false; }

            /**
             * \return True if game show the all hitbox of entities
             */
            inline bool isShowingPointerEntities() const { return showingPointerEntities; }
            /**
             * \brief Show the hitbox all entities
             */
            inline void showPointerEntities() { showingPointerEntities = true; }
            /**
             * \brief Unshow the hitbox all entities
             */
            inline void unshowPointerEntities() { showingPointerEntities = false; }

            inline State* getState() { return sManager->getState(); }
            inline StateManager* getStateManager() { return sManager; }
            inline EntityManager* getEntityManager() { return sManager->getEntityManager(); }
            inline void setState(std::size_t state) { sManager->setState(state); }

            inline Handler* getHandler() { return handler; };
            /** 
             * \return Get the lua with all libs and functions
             */
            inline LuaSystem* getLua() { return lua; }
    };
}