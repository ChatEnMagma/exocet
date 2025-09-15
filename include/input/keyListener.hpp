#pragma once

#include <iostream>

#include "constantes.hpp"

namespace exocet {
    class KeyListener {
        private:
            bool keys[SDL_NUM_SCANCODES];
        public:
            KeyListener() { memset(keys, false, SDL_NUM_SCANCODES * sizeof(bool)); }

            inline void interactKey(Uint16 scancode, bool isPressing) { keys[scancode] = isPressing; }

            inline bool getKey(Uint16 scancode) { return keys[scancode]; }
    };
}