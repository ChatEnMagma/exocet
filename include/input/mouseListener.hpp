#pragma once

#include "constantes.hpp"
#include "tool/vectors.hpp"

#define NB_BUTTONS 6

namespace exocet {
    class MouseListener {
        private:
            bool buttons[NB_BUTTONS];
            bool cantPress[NB_BUTTONS];
            bool justPress[NB_BUTTONS];
            Vector2D<int> pos;

            Uint16 scancode;
        public:
            MouseListener() {
                memset(buttons,   false, NB_BUTTONS * sizeof(bool));
                memset(cantPress, false, NB_BUTTONS * sizeof(bool));
                memset(justPress, false, NB_BUTTONS * sizeof(bool));
            }

            void update() {
                for(size_t i = 0; i < NB_BUTTONS; i++) {
                    if(buttons[i] && !cantPress[i]) {
                        cantPress[i] = true;
                        justPress[i] = true;
                    } else if (buttons[i] && cantPress[i]) {
                        justPress[i] = false;
                    } else {
                        cantPress[i] = false;
                    }
                }
            }

            inline void interact(Uint16 scancode, bool pressing) { this->scancode = scancode; buttons[scancode] = pressing; }
            inline void move(int x, int y) { pos.x = x; pos.y = y; }
            inline Vector2D<int> getPosition() const { return pos; }
            inline bool getButton(Uint16 scancode) const { return buttons[scancode]; }
            inline bool getJustButton(Uint16 scancode) const { return justPress[scancode]; }

            inline Uint16 getButtonCode() const { return scancode; }
    };
}