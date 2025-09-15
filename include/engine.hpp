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
            bool init(int width, int height, std::string title);

            void run();
            void clean();
    };
}