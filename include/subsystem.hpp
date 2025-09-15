#pragma once

#include <iostream>
#include <string>

#include "constantes.hpp"

#include "input/keyListener.hpp"
#include "gfx/graphic.hpp"

namespace exocet {
    class Subsystem {
        private:
            SDL_Window* win = NULL;
            Graphic* gfx = nullptr;
            KeyListener keys;

            int w, h;
            std::string title;

            bool running;
        public:
            bool init(int width, int height, std::string title);

            void handleEvents();

            void clean();

            inline void setTitle(std::string title) { SDL_SetWindowTitle(win, title.c_str()); }

            inline void close() { running = false; }
            inline bool isRunning() { return running; }

            inline Graphic* getGraphic() { return gfx; }
            inline KeyListener* getKeyListener() { return &keys; }
            
            inline int getWinWidth() const { return w; }
            inline int getWinHeight() const { return h; }
            inline std::string getWinTitle() const { return title; }

            inline SDL_Renderer* getRenderer() { return gfx->getRenderer(); }
    };
}