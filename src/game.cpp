#include "game.hpp"
#include "handler.hpp"

using namespace std;
using namespace exocet;

Game::Game(Subsystem* subsys) {
    handler = new Handler(this, subsys);

    lua = luaL_newstate();

    if(lua == (lua_State*)0) {
        cerr << "Failed to create Lua State" << endl;
        handler->closeGame();
    }

    luaL_openlibs(lua);

    handler->getGraphic()->initTextures(handler);
    handler->getGraphic()->getCamera()->setHandler(handler);

    sManager = new StateManager();
    sManager->setHandler(handler);
    sManager->loadState();
    
    setState(0);

    showHitbox();
}

void Game::update() {
    if(handler->getKey(SDLK_ESCAPE))
        handler->closeGame();
    if(handler->getKey(SDLK_F2))
        sManager->previousState();
    if(handler->getKey(SDLK_F3))
        sManager->nextState();
    if(handler->getKey(SDLK_F5))
        sManager->restart();
    
    sManager->update();
}

void Game::render() {
    handler->getGraphic()->setRenderColor(0x00, 0x00, 0x00);
    handler->getGraphic()->renderClear();

    // render all game here
    sManager->render();

    handler->getGraphic()->renderText(10, 10, handler->getWinWidth() / 4, 100, string("State: ") + to_string(sManager->getCurrentState()), handler->getGraphic()->freeRoyalty);

    handler->getGraphic()->renderPresent();
}