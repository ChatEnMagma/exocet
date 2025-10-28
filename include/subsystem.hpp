#pragma once

#include <iostream>
#include <string>

#include "constantes.hpp"

#include "input/keyListener.hpp"
#include "input/mouseListener.hpp"
#include "gfx/graphic.hpp"

namespace exocet {
    class Subsystem {
        private:
            SDL_Window* win = NULL;
            Graphic* gfx = nullptr;
            KeyListener keys;
            MouseListener mouse;

            SDL_Surface* icon;

            int w, h;
            std::string title;

            bool running;
        public:
            /**
             * \brief Init the subsystem
             * \param width the window width
             * \param height the window height
             * \param title the window title
             */
            bool init(int width, int height, std::string title);

            /**
             * \brief Handle all events from SDL
             */
            void handleEvents();
            /**
             * \brief Clean the subsystem
             */
            void clean();

            /**
             * \brief Set window title
             * \param title the title for window
             */
            inline void setTitle(std::string title) { SDL_SetWindowTitle(win, title.c_str()); }
            /**
             * \brief Close the game, will exit the excucatable
             */
            inline void close() { running = false; }
            /**
             * \return True if the subsystem run else false
             */
            inline bool isRunning() { return running; }

            inline Graphic* getGraphic() { return gfx; }
            inline KeyListener* getKeyListener() { return &keys; }
            inline MouseListener* getMouseListener() { return &mouse; }
            
            inline int getWinWidth() const { return w; }
            inline int getWinHeight() const { return h; }
            inline std::string getWinTitle() const { return title; }

            inline SDL_Renderer* getRenderer() { return gfx->getRenderer(); }
    };
}