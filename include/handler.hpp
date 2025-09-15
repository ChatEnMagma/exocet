#pragma once

#include "constantes.hpp"

#include "subsystem.hpp"
#include "game.hpp"

namespace exocet {
    class Handler {
        private:
            Subsystem* subsys;
            Game* game;
        public:
            Handler(Game* game, Subsystem* subsystem) {
                this->subsys = subsystem;
                this->game = game;
            }

            inline Subsystem* getSubsystem() { return subsys; }
            /**
             * \brief It closes the game, will exit the excucatable
             */
            inline void closeGame() { subsys->close(); }
            /** 
             * \return gets the width of the game window
            */
            inline int getWinWidth() const { return subsys->getWinWidth(); }
            /** 
             * \return gets the height of the game window
            */
            inline int getWinHeight() const { return subsys->getWinHeight(); }
            /** 
             * \brief It return if the key is pressing
             * \param scancode the scancode of the key with SDLK
             * \return get true if the key is pressing else false
            */
            inline bool getKey(Uint16 scancode) { return subsys->getKeyListener()->getKey(scancode); }
            inline Graphic* getGraphic() { return subsys->getGraphic(); }

            inline Game* getGame() { return game; }
            inline lua_State* getLua() { return game->getLua(); }
            inline bool isShowingHitbox() const { return game->isShowingHitbox(); }
            inline State* getState() { return game->getState(); }
            inline EntityManager* getEntityManager() { return game->getEntityManager(); }
            inline void setState(std::size_t state) { game->setState(state); }
    };
}