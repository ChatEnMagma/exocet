#pragma once

#include "subsystem.hpp"
#include "game.hpp"

namespace exocet {
    /**
     * \brief Class will initiate all for exocet game 2D engin
     */
    class Engine {
        private:
            Game* game;
            Subsystem* subsys;
        public:
            /**
             * \brief init the game engine
             * \param width the window width
             * \param height the window height
             * \param title the window title
             */
            bool init(int width, int height, std::string title);

            /**
             * \brief Run the game engine
             */
            void run();
            /**
             * \brief Clean the game engine
             */
            void clean();
    };
}