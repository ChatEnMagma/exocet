#include "game.hpp"

#include "tool/vectors.hpp"
#include "handler.hpp"

using namespace std;
using namespace exocet;

Game::Game(Subsystem* subsys) {
    handler = new Handler(this, subsys);

    // set handler graphics parts
    handler->getGraphic()->initTextures(handler);
    handler->getGraphic()->getCamera()->setHandler(handler);

    initLua();

    // init StateManager
    sManager = new StateManager();
    sManager->setHandler(handler);
    sManager->loadState();

    // init state
    lua.script_file(DIR_SCRIPT + string("config.lua"));

    // set the state, and try to fetch the config file lua
    if(lua["config"]["init_state"] != sol::nil)
        setState((size_t) lua["config"]["init_state"]);
    else
        setState(0);

    // if all hitbox must show
    if(lua["config"]["showHitbox"] != sol::nil && (bool) lua["config"]["showHitbox"])
        showHitbox();
}

void Game::initLua() {
    // Load main lib and package
    lua.open_libraries(sol::lib::base, sol::lib::package);
    lua.require_file(SCRIPT_MODULE_ENGINE, SCRIPT_LIB_ENGINE);
    lua.require_file(SCRIPT_MODULE_VECTOR2D, SCRIPT_LIB_VECTOR2D);
    lua.require_file(SCRIPT_MODULE_ENTITIES, SCRIPT_LIB_ENTITIES);

    // set the handle for lua script

    // set the handler pointeur in engine.lua lib
    lua["engine"]["setHandler"]((intptr_t) handler);

    // add handler function into engine.lua lib
    // ====================== engine class lua ===========================

    lua["engine"]["cHandlerGetWinWidth"] = [](intptr_t handler_lua) { return ((Handler*) handler_lua)->getWinWidth(); };
    lua["engine"]["cHandlerGetWinHeight"] = [](intptr_t handler_lua) { return ((Handler*) handler_lua)->getWinHeight(); };
    lua["engine"]["cHandlerGetKey"] = [](intptr_t handler_lua, Uint32 scancode) { return ((Handler*) handler_lua)->getKey(scancode); };

    // ===================== Entity class lua ============================

    lua["Entity"]["cGetPosition"] = [](intptr_t entity_lua) {
        Vector2D<int> pos = ((Entity*) entity_lua)->getComponent<TransformComponent>().getPosition();
        std::tuple<int, int> res = { pos.x, pos.y };
        return res;
    };
    lua["Entity"]["cGetVelocity"] = [](intptr_t entity_lua) {
        Vector2D<float> vel = ((Entity*) entity_lua)->getComponent<TransformComponent>().getVelocity();
        std::tuple<float, float> res = { vel.x, vel.y };
        return res;
    };
    lua["Entity"]["cSetPosition"] = [](intptr_t entity_lua, int x, int y) {((Entity*) entity_lua)->getComponent<TransformComponent>().setPosition(Vector2D<int>(x, y));};
}

void Game::update() {
    // Handler some keys debug
    #pragma GCC diagnostic warning "-Woverflow"
    #pragma GCC diagnostic error "-Woverflow"
    #pragma GCC diagnostic ignored "-Woverflow"

    if(handler->getKey(SDLK_ESCAPE))
        handler->closeGame();
    if(handler->getKey(SDLK_F2))
        sManager->previousState();
    if(handler->getKey(SDLK_F3))
        sManager->nextState();
    if(handler->getKey(SDLK_F5))
        sManager->restart();
    if(handler->getKey(SDLK_F7))
        sManager->getEntityManager()->destroyAllEntities();
    
    sManager->update();
}

void Game::render() {
    handler->getGraphic()->setRenderColor(0x00, 0x00, 0x00);
    handler->getGraphic()->renderClear();

    // render all game here
    sManager->render();

    // render the text of the current state and number of entities
    handler->getGraphic()->renderText(10, 10, handler->getWinWidth() / 4, 100, string("State: ") + to_string(sManager->getCurrentState()), handler->getGraphic()->freeRoyalty);
    handler->getGraphic()->renderText(10, 10 + 100, handler->getWinWidth() / 4, 100, string("#entities: ") + to_string(sManager->getEntityManager()->getNumberEntities()), handler->getGraphic()->freeRoyalty);


    handler->getGraphic()->renderPresent();
}