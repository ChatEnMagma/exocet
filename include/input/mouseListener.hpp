#pragma once

#include "constantes.hpp"

#define NB_BUTTONS 6

namespace exocet {
    class MouseListener {
        private:
            bool buttons[NB_BUTTONS];
            bool cantPress[NB_BUTTONS];
            bool justPress[NB_BUTTONS];
            EngineVector2D pos;

            Uint16 scancode;
        public:
            MouseListener() noexcept {
                memset(buttons,   false, NB_BUTTONS * sizeof(bool));
                memset(cantPress, false, NB_BUTTONS * sizeof(bool));
                memset(justPress, false, NB_BUTTONS * sizeof(bool));
            }
            ~MouseListener() noexcept = default;

            void update() noexcept {
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

            inline void interact(Uint16 scancode, bool pressing) noexcept { this->scancode = scancode; buttons[scancode] = pressing; }
            inline void move(int x, int y) noexcept { pos.x = x; pos.y = y; }
            inline EngineVector2D getPosition() const noexcept { return pos; }
            inline bool getButton(Uint16 scancode) const noexcept { return buttons[scancode]; }
            inline bool getJustButton(Uint16 scancode) const noexcept { return justPress[scancode]; }

            inline Uint16 getButtonCode() const noexcept { return scancode; }
    };
}