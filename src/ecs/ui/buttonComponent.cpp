#include "ecs/ui/buttonComponent.hpp"
#include "handler.hpp"

using namespace exocet;
using namespace std;

void ButtonComponent::init() {
    if(!entity->hasComponent<UIComponent>()) {
        ui = &entity->addComponent<UIComponent>();
    } else {
        ui = &entity->getComponent<UIComponent>();
    }

    function = []() {};
}

void ButtonComponent::update() {
    if(click())
        function();
}

bool ButtonComponent::isMouseover() const noexcept {
    Vector2D<int> mousePos = handler->getMousePosition();
    Vector2D<int> pos = ui->getPosition();

    return (
        mousePos.x >= pos.x &&
        mousePos.x <= pos.x + ui->getWidth() &&
        mousePos.y >= pos.y &&
        mousePos.y <= pos.y + ui->getHeight()
    );
}

bool ButtonComponent::click() const noexcept {
    return isMouseover() && handler->getJustButton(SDL_BUTTON_LEFT); 
}