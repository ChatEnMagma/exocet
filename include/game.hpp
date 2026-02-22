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
        public:
            Game(Subsystem* subsystem);
            ~Game();

            void update();
            void render();

            /**
             * \return True if game show the all hitbox of entities
             */
            inline bool isShowingHitbox() const noexcept { return showingHitbox; }
            /**
             * \brief Show the hitbox all entities
             */
            inline void showHitbox() noexcept { showingHitbox = true; }
            /**
             * \brief Unshow the hitbox all entities
             */
            inline void unshowHitbox() noexcept { showingHitbox = false; }

            /**
             * \return True if game show the all hitbox of entities
             */
            inline bool isShowingPointerEntities() const noexcept { return showingPointerEntities; }
            /**
             * \brief Show the hitbox all entities
             */
            inline void showPointerEntities() noexcept { showingPointerEntities = true; }
            /**
             * \brief Unshow the hitbox all entities
             */
            inline void unshowPointerEntities() noexcept { showingPointerEntities = false; }

            inline State* getState() noexcept { return sManager->getState(); }
            inline StateManager* getStateManager() noexcept { return sManager; }
            inline EntityManager* getEntityManager() noexcept { return sManager->getEntityManager(); }
            inline void setState(std::size_t state) { sManager->setState(state); }

            inline Handler* getHandler() noexcept { return handler; };
            /** 
             * \return Get the lua with all libs and functions
             */
            inline LuaSystem* getLua() noexcept { return lua; }
    };
}