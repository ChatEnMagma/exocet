#include <climits>
#include <cfloat>

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

    // Init all modules and function lua
    initLua();

    // init StateManager
    sManager = new StateManager();
    sManager->setHandler(handler);
    sManager->initStates();

    // set the state, and try to fetch the config file lua
    if(lua["config"]["init_state"] != sol::nil)
        setState((size_t) lua["config"]["init_state"]);
    else setState(0);

    // All debug functions pre-define bu config lua file
    if(lua["config"]["showHitbox"] != sol::nil && (bool) lua["config"]["showHitbox"]) showHitbox();
    if(lua["config"]["showPointerEntities"] != sol::nil && (bool) lua["config"]["showPointerEntities"]) showPointerEntities();
}

void Game::initLua() {
    lua.script_file(DIR_SCRIPT_PACKAGE_MODULES);

    // Check if the module field exists in the config
    if(lua["modules"] == sol::nil) {
        cerr << "You must have `modules`..." << endl;
        handler->closeGame();
    }

    // Load main lib and package
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string, sol::lib::math);
    // Load all modules homemade
    lua["modules"].get<sol::table>().for_each([&](sol::object const& key, sol::object const& value) {
        lua.require_file(
            value.as<sol::table>()[1].get<string>(),                        // Get the name of the module
            DIR_SCRIPT + value.as<sol::table>()[2].get<string>() + ".lua"   // Get the path of lua file
        );
    });
    // set the handle for lua script

    // set the handler pointeur in engine.lua lib
    lua["engine"]["setHandler"]((intptr_t) handler);

    // add handler function into engine.lua lib
    // ====================== engine class lua ===========================

    lua["engine"]["cCenterOnEntity"] = [](intptr_t handler_lua, intptr_t entity_lua) { ((Handler*) handler_lua)->getGraphic()->centerOnEntity(((Entity*) entity_lua)); };
    lua["engine"]["cCloseGame"] = [](intptr_t handler_lua) { ((Handler*) handler_lua)->closeGame(); };
    lua["engine"]["cHandlerGetKey"] = [](intptr_t handler_lua, Uint32 scancode) { return ((Handler*) handler_lua)->getKey(scancode); };
    lua["engine"]["cHandlerGetKeyCode"] = [](intptr_t handler_lua) { return ((Handler*) handler_lua)->getSubsystem()->getKeyListener()->getKeyCode(); };
    lua["engine"]["cHandlerGetWinHeight"] = [](intptr_t handler_lua) { return ((Handler*) handler_lua)->getWinHeight(); };
    lua["engine"]["cHandlerGetWinWidth"] = [](intptr_t handler_lua) { return ((Handler*) handler_lua)->getWinWidth(); };
    lua["engine"]["cGetCameraPosition"] = [](intptr_t handler_lua) { 
        Vector2D<int> pos = ((Handler*) handler_lua)->getGraphic()->getCamera()->getPosition();
        return std::tuple<int, int>(pos.x, pos.y);
    };

    // ===================== Entity class lua ============================
    // ****************** Methods from EntityManager *********************
    lua["engine"]["cAddEntity"] = [](intptr_t handler_lua, sol::table entity_lua) { (((Handler*) handler_lua)->getEntityManager()->addEntityFromLua(entity_lua)); };
    lua["Entity"]["cDestroy"] = [](intptr_t entity_lua) { ((Entity*) entity_lua)->destroy(); };
    // *************** Methods from SpriteComponent **********************
    lua["Entity"]["cSetTexture"] = [](intptr_t entity_lua, string path) {
        Entity* e = ((Entity*) entity_lua);
        if(e->hasComponent<SpriteComponent>()) {
            e->getComponent<SpriteComponent>().setTexture(string("res/") + path);
        } else { cout << "Warning /!\\ function `setTexture` from: " << e->getTag() <<  ": You must inititate the SpriteComponent..." << endl; }
    };
    lua["Entity"]["cFitSizeWithHitbox"] = [](intptr_t entity_lua) {
        Entity* e = ((Entity*) entity_lua);
        if(e->hasComponent<SpriteComponent>()) {
            e->getComponent<SpriteComponent>().fitSizeWithHitbox();
        } else { cout << "Warning /!\\ function `fitSizeWithHitbot` from: " << e->getTag() <<  ": You must inititate the SpriteComponent..." << endl; }
    };
    // **************** Methods from PhysicComponent ********************
    lua["Entity"]["cGetCollideEntities"] = [](intptr_t entity_lua) {
        Entity* entity = ((Entity*) entity_lua);
        
        vector<intptr_t> entities_ptr;

        if(!entity->hasComponent<PhysicComponent>()) {
            cout << "Warning: function `getCollideEntities` from: " << entity->getTag() << ". You must initiate the PhysicComponent" << endl;
            return entities_ptr;
        }

        for(Entity* e: entity->getComponent<PhysicComponent>().getCollideEntities())
            entities_ptr.emplace_back((intptr_t) e);

        return entities_ptr;
    };
    // ****************** Methods from HitboxComponent ********************
    lua["Entity"]["cGetCollideEntity"] = [](intptr_t entity1_lua, intptr_t entity2_lua) {
        Entity* entity1 = ((Entity*) entity1_lua);
        Entity* entity2 = ((Entity*) entity2_lua);
        
        if(!entity1->hasComponent<HitboxComponent>()) {
            cout << "Warning: function `getCollideEntities` from: " << entity1->getTag() << ". You must initiate the HitboxComponent" << endl;
            return false;
        }
        if(!entity2->hasComponent<HitboxComponent>()) {
            cout << "Warning: function `getCollideEntities` from: " << entity2->getTag() << ". You must initiate the HitboxComponent" << endl;
            return false;
        }

        return entity1->getComponent<HitboxComponent>().isCollide(&entity2->getComponent<HitboxComponent>());
    };
    // ***************** Methods from TransfromComponent ******************
    lua["Entity"]["cGetPosition"] = [](intptr_t entity_lua) {
        Entity* e = ((Entity*) entity_lua);
        if(e->hasComponent<TransformComponent>()) {
            Vector2D<int> pos = ((Entity*) entity_lua)->getComponent<TransformComponent>().getPosition();
            std::tuple<int, int> res = { pos.x, pos.y };
            return res;
        } else {
            cout << "Warning /!\\ function `getPosition` from: " << e->getTag() <<  ": You must inititate the TransfromComponent..." << endl;

            std::tuple<int, int> res = { INT32_MIN, INT32_MIN };
            return res;
        }
    };
    lua["Entity"]["cGetVelocity"] = [](intptr_t entity_lua) {
        Entity* e = ((Entity*) entity_lua);
        if(e->hasComponent<TransformComponent>()) {
            Vector2D<float> vel = ((Entity*) entity_lua)->getComponent<TransformComponent>().getVelocity();
            std::tuple<float, float> res = { vel.x, vel.y };
            return res;
        } else {
            cout << "Warning /!\\ function `getVelocity` from: " << e->getTag() <<  ": You must inititate the TransfromComponent..." << endl;

            std::tuple<float, float> res = { FLT_MIN, FLT_MIN };
            return res;
        }
    };
    lua["Entity"]["cSetPosition"] = [](intptr_t entity_lua, int x, int y) {
        Entity* e = ((Entity*) entity_lua);
        if(e->hasComponent<TransformComponent>()) {
            e->getComponent<TransformComponent>().setPointsPosition(x, y);
        } else { cout << "Warning /!\\ function `setPosition` from: " << e->getTag() <<  ": You must inititate the TransfromComponent..." << endl; }
    };
    lua["Entity"]["cSetVelocity"] = [](intptr_t entity_lua, float x, float y) {
        Entity* e = ((Entity*) entity_lua);

        if(e->hasComponent<TransformComponent>()) {
            ((Entity*) entity_lua)->getComponent<TransformComponent>().setPointsVelocity(x, y);
        } else { cout << "Warning /!\\ function `setVelocity` from: " << e->getTag() <<  ": You must inititate the TransfromComponent..." << endl; }
    };
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