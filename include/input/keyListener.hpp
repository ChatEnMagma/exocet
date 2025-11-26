#pragma once

#include <iostream>

#include "constantes.hpp"

namespace exocet {
    class KeyListener {
        private:
            bool keys[SDL_NUM_SCANCODES];
            bool justPress[SDL_NUM_SCANCODES];
            bool cantPress[SDL_NUM_SCANCODES];

            Uint16 scancode;
            bool pressing;
            bool justPressing;
            bool cantPressing;
        public:
            KeyListener() { 
                memset(keys, false, SDL_NUM_SCANCODES * sizeof(bool)); 
                memset(justPress, false, SDL_NUM_SCANCODES * sizeof(bool)); 
                memset(cantPress, false, SDL_NUM_SCANCODES * sizeof(bool));

                pressing = false;
                cantPressing = false;
                justPressing = false;
            }
            
            void update() {
                for(size_t i = 0; i < SDL_NUM_SCANCODES; i++) {
                    if(keys[i] && !cantPress[i]) {
                        cantPress[i] = true;
                        justPress[i] = true;
                    } else if (keys[i] && cantPress[i]) {
                        justPress[i] = false;
                    } else {
                        cantPress[i] = false;
                    }
                }
                if(pressing && !cantPressing) {
                    cantPressing = true;
                    justPressing = true;
                } else if (pressing && cantPressing) {
                    justPressing = false;
                } else {
                    cantPressing = false;
                }
            }

            /**
             * \brief Set the key interact if it is pressing
             */
            inline void interactKey(Uint16 scancode, bool isPressing) { pressing = isPressing; this->scancode = scancode; keys[scancode] = isPressing; }

            inline bool getKey(Uint16 scancode) const { return keys[scancode]; }
            inline bool getJustKey(Uint16 scancode) const { return justPress[scancode]; }
            inline Uint16 getKeyCode() const { return (pressing)? scancode: 0; }
            inline bool isPressing() const { return pressing; }
            inline bool isJustPressing() const { return justPressing; }
    };
}