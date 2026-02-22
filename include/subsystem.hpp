#pragma once

#include <iostream>
#include <string>
#include <memory>

#include "constantes.hpp"

#include "input/keyListener.hpp"
#include "input/mouseListener.hpp"
#include "gfx/graphic.hpp"

namespace exocet {
    class Subsystem {
        private:
            SDL_Window* win;
            std::unique_ptr<Graphic> gfx;
            KeyListener keys;
            MouseListener mouse;

            SDL_Surface* icon;

            int w, h;
            std::string title;

            bool muting;
            bool resizing;

            bool running;
        public:
            ~Subsystem() noexcept { clean(); };

            /**
             * \brief Init the subsystem
             * \param width the window width
             * \param height the window height
             * \param title the window title
             */
            void init(int width, int height, std::string title);

            /**
             * \brief Handle all events from SDL
             */
            void handleEvents() noexcept;
            /**
             * \brief Clean the subsystem
             */
            void clean() noexcept;

            /**
             * \brief Set window title
             * \param title the title for window
             */
            inline void setTitle(const std::string& title) noexcept { SDL_SetWindowTitle(win, title.c_str()); }
            /**
             * \brief Close the game, will exit the excucatable
             */
            inline void close() noexcept { running = false; }
            /**
             * \return True if the subsystem run else false
             */
            inline bool isRunning() noexcept { return running; }
            inline void mute() noexcept { 
                muting = true;
                Mix_Volume(-1, 0);
            }
            inline void unmute() noexcept { 
                muting = false; 
                Mix_Volume(-1, 128);
            }
            inline bool isMuting() const noexcept { return muting; }
            inline bool isResizing() const noexcept { return resizing; }

            inline Graphic* getGraphic() noexcept { return gfx.get(); }
            inline KeyListener* getKeyListener() noexcept { return &keys; }
            inline MouseListener* getMouseListener() noexcept { return &mouse; }
            
            inline int getWinWidth() const noexcept { return w; }
            inline int getWinHeight() const noexcept { return h; }
            inline std::string getWinTitle() const noexcept { return title; }

            inline SDL_Renderer* getRenderer() noexcept { return gfx->getRenderer(); }

            inline void setFullscreen() noexcept { SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN); }
    };
}