#include <climits>
#include <cfloat>

#include "game.hpp"

#include "tool/vectors.hpp"
#include "tool/playSong.hpp"
#include "handler.hpp"

#include "luasystem.hpp"

using namespace std;
using namespace exocet;

Game::Game(Subsystem* subsys) {
    handler = new Handler(this, subsys);

    // set handler graphics parts
    handler->getGraphic()->initTextures(handler);
    handler->getGraphic()->getCamera()->setHandler(handler);

    // Init all modules and function lua
    lua = new LuaSystem(handler);
    cout << "Success to initiate the luaSystem" << endl;

    // init StateManager
    sManager = new StateManager();
    sManager->setHandler(handler);
    sManager->initStates();

    cout << "Success to initiate all states" << endl;

    // set the state, and try to fetch the config file lua
    if((*lua)["config"]["init_state"] != sol::nil)
        setState((*lua)["config"]["init_state"].get<size_t>());
    else setState(0);

    cout << (*lua)["config"]["init_state"].get<int>() << endl;

    // All debug functions pre-define bu config lua file
    if((*lua)["config"]["showHitbox"] != sol::nil && (*lua)["config"]["showHitbox"].get<bool>()) showHitbox();
    if((*lua)["config"]["showPointerEntities"] != sol::nil && (*lua)["config"]["showPointerEntities"].get<bool>()) showPointerEntities();

    cout << "Success to config the game" << endl;
}

void Game::update() {
    if(handler->getJustKey(SDLK_ESCAPE))
        handler->closeGame();
    
    sManager->update();

    handler->getSubsystem()->setTitle("Exocet state: " + to_string(sManager->getCurrentState()) + " | e: " + to_string(sManager->getEntityManager()->getNumberEntities()));
}

void Game::render() {
    handler->getGraphic()->setRenderColor(0x00, 0x00, 0x00);
    handler->getGraphic()->renderClear();

    // render all game here
    sManager->render();

    handler->getGraphic()->renderPresent();
}