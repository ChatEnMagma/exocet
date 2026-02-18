#pragma once

#include <memory>

#include "subsystem.hpp"
#include "game.hpp"

namespace exocet {
    /**
     * \brief Class will initiate all for exocet game 2D engin
     */
    class Engine {
        private:
            std::unique_ptr<Game> game;
            std::unique_ptr<Subsystem> subsys;
        public:
            /**
             * \brief init the game engine
             * \param width the window width
             * \param height the window height
             * \param title the window title
             */
            void init(int width, int height, std::string title, bool fullscreen = false);

            /**
             * \brief Run the game engine
             */
            void run();
    };
}