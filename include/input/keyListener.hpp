#pragma once

#include <iostream>

#include "constantes.hpp"

namespace exocet {
    class KeyListener {
        private:
            bool keys[SDL_NUM_SCANCODES];
            Uint16 scancode;
        public:
            KeyListener() { memset(keys, false, SDL_NUM_SCANCODES * sizeof(bool)); }

            /**
             * \brief Set the key interact if it is pressing
             */
            inline void interactKey(Uint16 scancode, bool isPressing) { this->scancode = scancode; keys[scancode] = isPressing; }

            inline bool getKey(Uint16 scancode) { return keys[scancode]; }
            inline Uint16 getKeyCode() { return scancode; }
    };
}