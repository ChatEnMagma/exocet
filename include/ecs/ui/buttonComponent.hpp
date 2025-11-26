#pragma once

#include "ecs/ui/uiComponent.hpp"

namespace exocet {
    class ButtonComponent: public Component {
        private:
            UIComponent* ui;
            std::function<void()> function;
        public:
            void init() override;
            void update() override;

            bool isMouseover() const;
            bool click() const;

            inline void setFunction(std::function<void()> function) { this->function = function; }
            inline void setRect(int xpos, int ypos, int width, int height) { ui->setRect(xpos, ypos, width, height); }
    };
}