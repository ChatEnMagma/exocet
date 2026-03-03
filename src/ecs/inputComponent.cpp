#include "ecs/inputComponent.hpp"
#include "handler.hpp"

using namespace exocet;
using namespace std;

void InputComponent::init() {
    if(!entity->hasComponent<ControllerDirectionsComponent>())
        controller = &entity->addComponent<ControllerDirectionsComponent>();
    else
        controller = &entity->getComponent<ControllerDirectionsComponent>();
    
    typeController = KEYBOARD;
}

void InputComponent::controllerKeyboard() {
    if(handler->getKey(SDLK_z) || handler->getKey(SDLK_UP))
        controller->setDirectionY(-1.f);
    else if(handler->getKey(SDLK_s) || handler->getKey(SDLK_DOWN))
        controller->setDirectionY(1.f);
    else controller->setDirectionY(0.f);

    if(handler->getKey(SDLK_d) || handler->getKey(SDLK_RIGHT))
        controller->setDirectionX(1.f);
    else if(handler->getKey(SDLK_q) || handler->getKey(SDLK_LEFT))
        controller->setDirectionX(-1.f);
    else controller->setDirectionX(0.f);
}

void InputComponent::controllerGamepad() {

}

void InputComponent::update() {
    if(typeController == KEYBOARD)
        controllerKeyboard();
    if(typeController == GAMEPAD)
        controllerGamepad();
}