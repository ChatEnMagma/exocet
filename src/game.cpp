#include <climits>
#include <cfloat>

#include "game.hpp"

#include "tool/vectors.hpp"
#include "tool/playSong.hpp"
#include "handler.hpp"

#include "luasystem.hpp"

using namespace std;
using namespace exocet;

Game::Game(Subsystem& subsys) {
    handler = make_unique<Handler>(*this, subsys);

    // Init all modules and function lua
    lua = make_unique<LuaSystem>(*handler);
    
    cout << "Success to initiate the luaSystem" << endl;

    // init StateManager
    (sManager = make_unique<StateManager>(*handler))->initStates();

    cout << "Success to initiate all states" << endl;

    // All debug functions pre-define bu config lua file
    if(getLua()["config"]["showHitbox"].get_or<bool>(0)) showHitbox();
    if(getLua()["config"]["showPointerEntities"].get_or<bool>(0)) showPointerEntities();

    getLua()["config"]["init"]();

    // set the state, and try to fetch the config file lua
    setState(getLua()["config"]["init_state"].get_or<size_t>(0));

    deltaTime = 0.f;
}

Game::~Game() {
    sManager.reset();
    lua.reset();
    handler.reset();
}

void Game::update(double deltaTime) {
    this->deltaTime = deltaTime;

    if(handler->getJustKey(SDLK_ESCAPE))
        handler->closeGame();
    
    sManager->update();

    handler->getSubsystem().setTitle("Exocet state: " + to_string(sManager->getCurrentState()) + " | e: " + to_string(sManager->getEntityManager().size()));
}

void Game::render() {
    handler->getGraphic().setRenderColor(0x00, 0x00, 0x00);
    handler->getGraphic().renderClear();

    // render all game here
    sManager->render();

    handler->getGraphic().renderPresent();
}