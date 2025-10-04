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
             * \brief Close the game, will exit the excucatable
             */
            inline void closeGame() { subsys->close(); }
            /** 
             * \return Get the width of the game window
            */
            inline int getWinWidth() const { return subsys->getWinWidth(); }
            /** 
             * \return Get the height of the game window
            */
            inline int getWinHeight() const { return subsys->getWinHeight(); }
            /** 
             * \brief Return if the key is pressing
             * \param scancode the scancode of the key with SDLK
             * \return get true if the key is pressing else false
            */
            inline bool getKey(Uint16 scancode) { return subsys->getKeyListener()->getKey(scancode); }
            /**
             * \return Graphics class with all functions graphics
             */
            inline Graphic* getGraphic() { return subsys->getGraphic(); }

            inline Game* getGame() { return game; }
            /**
             * \return True if game show the all hitbox of entities
             */
            inline bool isShowingHitbox() const { return game->isShowingHitbox(); }
            inline State* getState() { return game->getState(); }
            /** 
             * \return Get the lua with all libs and functions
             */
            inline sol::state* getLua() { return game->getLua(); }
            inline EntityManager* getEntityManager() { return game->getEntityManager(); }
            /**
             * \brief Set the current state
             * \param state the state become current
             */
            inline void setState(std::size_t state) { game->setState(state); } 
    };
}