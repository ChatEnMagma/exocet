#pragma once

#include "ecs/controllerDirectionsComponent.hpp"

namespace exocet {
    class InputComponent: public Component {
        private:
            ControllerDirectionsComponent* controller;

            int typeController;

            void controllerKeyboard();
            void controllerGamepad();
        public:
            enum CONTROLLER {
                KEYBOARD = 0b01,
                GAMEPAD = 0b10
            };

            ~InputComponent() = default;

            void init() override;
            void update() override;
    };
}