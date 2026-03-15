#pragma once

#include "constantes.hpp"

#include "subsystem.hpp"
#include "game.hpp"

namespace exocet {
    class Handler {
        private:
            Subsystem& subsys;
            Game& game;
        public:
            Handler(Game& game, Subsystem& subsystem)
                : subsys(subsystem), game(game) {}
            ~Handler() = default;

            inline Subsystem& getSubsystem() noexcept { return subsys; }
            /**
             * \brief Close the game, will exit the excucatable
             */
            inline void closeGame() noexcept { subsys.close(); }
            /** 
             * \return Get the width of the game window
            */
            inline int getWinWidth() const noexcept { return subsys.getWinWidth(); }
            /** 
             * \return Get the height of the game window
            */
            inline int getWinHeight() const noexcept { return subsys.getWinHeight(); }
            /** 
             * \brief Return if the key is pressing
             * \param scancode the scancode of the key with SDLK
             * \return get true if the key is pressing else false
            */
            inline bool getKey(Uint16 scancode) noexcept { return subsys.getKeyListener().getKey(scancode); }
            /** 
             * \brief Return if the key is just pressing
             * \param scancode the scancode of the key with SDLK
             * \return get true if the key is just pressing else false
            */
            inline bool getJustKey(Uint16 scancode) noexcept { return subsys.getKeyListener().getJustKey(scancode); }
            /**
             * \brief Tell is any key is pressing
             */
            inline bool getAnyKey() const noexcept { return subsys.getKeyListener().isPressing(); }
            inline bool getJustAnyKey() const noexcept { return subsys.getKeyListener().isJustPressing(); }
            /** 
             * \brief Return if the button is pressing
             * \param scancode the scancode of the key with SDL
             * \return get true if the button is pressing else false
            */
            inline bool getButton(Uint16 scancode) noexcept { return subsys.getMouseListener().getButton(scancode); }
            /** 
             * \brief Return if the button is just pressing
             * \param scancode the scancode of the key with SDL
             * \return get true if the button is just pressing else false
            */
            inline bool getJustButton(Uint16 scancode) const noexcept { return subsys.getMouseListener().getJustButton(scancode); }
            /**
             * \return the position of the mouse in the game frame
             */
            inline EngineVector2D getMousePosition() const noexcept { return subsys.getMouseListener().getPosition(); }
            /**
             * \return Graphics class with all functions graphics
             */
            inline Graphic& getGraphic() noexcept { return subsys.getGraphic(); }

            inline Game& getGame() noexcept { return game; }
            inline double getDeltaTime() noexcept { return game.getDeltaTime(); }
            /**
             * \return True if game show the all hitbox of entities
             */
            inline bool isShowingHitbox() const noexcept { return game.isShowingHitbox(); }
            inline State& getState() noexcept { return game.getState(); }
            /** 
             * \return Get the lua with all libs and functions
             */
            inline sol::state& getLua() noexcept { return game.getLua(); }
            inline EntityManager& getEntityManager() noexcept { return game.getEntityManager(); }
            /**
             * \brief Set the current state
             * \param state the state become current
             */
            inline void setState(std::size_t state) { game.setState(state); } 
    };
}