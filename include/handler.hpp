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
             * \brief Return if the key is just pressing
             * \param scancode the scancode of the key with SDLK
             * \return get true if the key is just pressing else false
            */
            inline bool getJustKey(Uint16 scancode) { return subsys->getKeyListener()->getJustKey(scancode); }
            /**
             * \brief Tell is any key is pressing
             */
            inline bool getAnyKey() const { return subsys->getKeyListener()->isPressing(); }
            inline bool getJustAnyKey() const { return subsys->getKeyListener()->isJustPressing(); }
            /** 
             * \brief Return if the button is pressing
             * \param scancode the scancode of the key with SDL
             * \return get true if the button is pressing else false
            */
            inline bool getButton(Uint16 scancode) { return subsys->getMouseListener()->getButton(scancode); }
            /** 
             * \brief Return if the button is just pressing
             * \param scancode the scancode of the key with SDL
             * \return get true if the button is just pressing else false
            */
            inline bool getJustButton(Uint16 scancode) { return subsys->getMouseListener()->getJustButton(scancode); }
            /**
             * \return the position of the mouse in the game frame
             */
            inline Vector2D<int> getMousePosition() const { return subsys->getMouseListener()->getPosition(); }
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