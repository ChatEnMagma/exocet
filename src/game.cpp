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
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string, sol::lib::os, sol::lib::math);
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

    // ============ ALL SUBSYS METHODS ====
    lua["engine"]["cHandlerGetWinHeight"] = [](intptr_t hLua) { return ((Handler*) hLua)->getWinHeight(); };
    lua["engine"]["cHandlerGetWinWidth"] = [](intptr_t hLua) { return ((Handler*) hLua)->getWinWidth(); };
    lua["engine"]["cCloseGame"] = [](intptr_t hLua) { ((Handler*) hLua)->closeGame(); };
    
    lua["engine"]["cHandlerGetKey"] = [](intptr_t hLua, Uint16 scancode) { return ((Handler*) hLua)->getKey(scancode); };
    lua["engine"]["cHandlerGetJustKey"] = [](intptr_t hLua, Uint16 scancode) { return ((Handler*) hLua)->getJustKey(scancode); };
    lua["engine"]["cHandlerGetKeyCode"] = [](intptr_t hLua) { return ((Handler*) hLua)->getSubsystem()->getKeyListener()->getKeyCode(); };

    lua["engine"]["cHandlerGetButton"] = [](intptr_t hLua, Uint16 scancode) { return ((Handler*) hLua)->getButton(scancode); };
    lua["engine"]["cHandlerGetJustButton"] = [](intptr_t hLua, Uint16 scancode) { return ((Handler*) hLua)->getJustButton(scancode); };
    lua["engine"]["cHandlerGetButtonCode"] = [](intptr_t hLua) { return ((Handler*) hLua)->getSubsystem()->getMouseListener()->getButtonCode(); };
    lua["engine"]["cGetMousePosition"] = [](intptr_t hLua) {
        Vector2D<int> pos = ((Handler*) hLua)->getMousePosition();
        return tuple<int, int>(pos.x, pos.y);
    };
    
    // ======== ALL STATES METHODS =====
    lua["engine"]["cSetState"] = [](intptr_t hLua, size_t state) { ((Handler*) hLua)->getGame()->getStateManager()->setState(state); };
    lua["engine"]["cGetCurrentState"] = [](intptr_t hLua) { ((Handler*) hLua)->getGame()->getStateManager()->getCurrentState(); };
    lua["engine"]["cRestart"] = [](intptr_t hLua) { ((Handler*) hLua)->getGame()->getStateManager()->restart(); };
    lua["engine"]["cNextState"] = [](intptr_t hLua) { ((Handler*) hLua)->getGame()->getStateManager()->nextState(); };
    lua["engine"]["cPreviousState"] = [](intptr_t hLua) { ((Handler*) hLua)->getGame()->getStateManager()->previousState(); };
    lua["engine"]["cRestart"] = [](intptr_t hLua) { ((Handler*) hLua)->getGame()->getStateManager()->restart(); };

    // ========= ALL GFX METHODS
    lua["engine"]["cSetColor"] = [](intptr_t hLua, int r, int g, int b, int a) { ((Handler*) hLua)->getGraphic()->setColor(r, g, b, a); };
    lua["engine"]["cRenderRect"] = [](intptr_t hLua, int x, int y, int w, int h) { ((Handler*) hLua)->getGraphic()->renderRect(Vector2D<int>(x, y), w, h); };
    lua["engine"]["cRenderFillRect"] = [](intptr_t hLua, int x, int y, int w, int h) { ((Handler*) hLua)->getGraphic()->renderFillRect(Vector2D<int>(x, y), w, h); };
    lua["engine"]["cRenderAnchorRect"] = [](intptr_t hLua, int x, int y, int w, int h) { ((Handler*) hLua)->getGraphic()->renderAnchorRect(Vector2D<int>(x, y), w, h); };
    lua["engine"]["cRenderAnchorFillRect"] = [](intptr_t hLua, int x, int y, int w, int h) { ((Handler*) hLua)->getGraphic()->renderAnchorFillRect(Vector2D<int>(x, y), w, h); };
    lua["engine"]["cCenterOnEntity"] = [](intptr_t hLua, intptr_t entity_lua) { ((Handler*) hLua)->getGraphic()->centerOnEntity(((Entity*) entity_lua)); };
    lua["engine"]["cGetCameraPosition"] = [](intptr_t hLua) { 
        Vector2D<int> pos = ((Handler*) hLua)->getGraphic()->getCamera()->getPosition();
        return tuple<int, int>(pos.x, pos.y);
    };
    lua["engine"]["cRenderText"] = [](intptr_t hLua, int xpos, int ypos, int width, int height, string text) {
        ((Handler*) hLua)->getGraphic()->renderText(
            xpos,
            ypos,
            width,
            height,
            text,
            ((Handler*) hLua)->getGraphic()->freeRoyalty
        );
    };
    lua["engine"]["cGetBackgroundPosition"] = [](intptr_t hLua) {
        const Vector2D<int> pos = ((Handler*) hLua)->getGame()->getStateManager()->getBackground()->getPosition();
        return tuple<int, int>(pos.x, pos.y);
    };
    lua["engine"]["cSetBackgroundPosition"] = [](intptr_t hLua, int xpos, int ypos) { ((Handler*) hLua)->getGame()->getStateManager()->getBackground()->setPosition(Vector2D<int>(xpos, ypos)); };

    // ===================== Entity class lua ============================
    // ****************** Methods from EntityManager *********************
    lua["engine"]["cAddEntity"] = [](intptr_t hLua, sol::table entity_lua) { (((Handler*) hLua)->getEntityManager()->addEntityFromLua(entity_lua)); };
    lua["Entity"]["cDestroy"] = [](intptr_t entity_lua) { ((Entity*) entity_lua)->destroy(); };
    lua["Entity"]["cGetRect"] = [](intptr_t entity_lua) {
        Entity* e = (Entity*) entity_lua;

        if(!e->hasComponent<HitboxComponent>() || e->hasComponent<UIComponent>()) {
            cout << "Warning /!\\ function getRect from: " << e->getTag() << ": You must initiate the HitboxComponent or UIComponent" << endl;
            return tuple<int, int, int, int>(0, 0, 0, 0);
        }

        if(e->hasComponent<HitboxComponent>()) {
            HitboxComponent& hitbox = e->getComponent<HitboxComponent>();
            return tuple<int, int, int, int>(hitbox.getLeft(), hitbox.getTop(), hitbox.getWidth(), hitbox.getHeight());
        }

        UIComponent& ui = e->getComponent<UIComponent>();
        return tuple<int, int, int, int>(ui.getPosition().x, ui.getPosition().y, ui.getWidth(), ui.getHeight());
    };
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
        } else if(e->hasComponent<AnimationComponent>()) {
            e->getComponent<AnimationComponent>().fitSizeWithHitbox();
        } else { cout << "Warning /!\\ function `fitSizeWithHitbot` from: " << e->getTag() <<  ": You must inititate the SpriteComponent or AnimationComponent..." << endl; }
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
            cout << "Warning: function `getCollideEntity` from: " << entity1->getTag() << ". You must initiate the HitboxComponent" << endl;
            return false;
        }
        if(!entity2->hasComponent<HitboxComponent>()) {
            cout << "Warning: function `getCollideEntity` from: " << entity2->getTag() << ". You must initiate the HitboxComponent" << endl;
            return false;
        }

        return entity1->getComponent<HitboxComponent>().isCollide(&entity2->getComponent<HitboxComponent>());
    };
    lua["Entity"]["cIsInsideMouse"] = [](intptr_t entity_lua) {
        Entity* entity = ((Entity*) entity_lua);

        if(entity->hasComponent<HitboxComponent>()) {
            return entity->getComponent<HitboxComponent>().isInsideMouse();
        } else {
            cout << "Warning: function `isInsideMouse` from: " << entity->getTag() << ". You must initiate the HitboxComponent" << endl;
            return false;
        }
    };
    // ***************** Methods from TransfromComponent ******************
    lua["Entity"]["cGetPosition"] = [](intptr_t entity_lua) {
        Entity* e = ((Entity*) entity_lua);

        if(e->hasComponent<TransformComponent>()) {
            Vector2D<int> pos = ((Entity*) entity_lua)->getComponent<TransformComponent>().getPosition();
            return tuple<int, int>(pos.x, pos.y);
        } else if(e->hasComponent<UIComponent>()) {
            Vector2D<int> pos = ((Entity*) entity_lua)->getComponent<UIComponent>().getPosition();
            return tuple<int, int>(pos.x, pos.y);
        } else {
            cout << "Warning /!\\ function `getPosition` from: " << e->getTag() <<  ": You must inititate the TransfromComponent or UIComponents..." << endl;

            return tuple<int, int> ( INT32_MIN, INT32_MIN);
        }
    };
    lua["Entity"]["cGetVelocity"] = [](intptr_t entity_lua) {
        Entity* e = ((Entity*) entity_lua);
        if(e->hasComponent<TransformComponent>()) {
            Vector2D<float> vel = ((Entity*) entity_lua)->getComponent<TransformComponent>().getVelocity();
            return tuple<float, float>(vel.x, vel.y);
        } else {
            cout << "Warning /!\\ function `getVelocity` from: " << e->getTag() <<  ": You must inititate the TransfromComponent..." << endl;

            return tuple<float, float>(FLT_MIN, FLT_MIN);
        }
    };
    lua["Entity"]["cSetPosition"] = [](intptr_t entity_lua, int x, int y) {
        Entity* e = ((Entity*) entity_lua);
        if(e->hasComponent<TransformComponent>()) {
            e->getComponent<TransformComponent>().setPointsPosition(x, y);
        } else if(e->hasComponent<UIComponent>()) {
            e->getComponent<UIComponent>().setPointsPosition(x, y);
        } else { cout << "Warning /!\\ function `setPosition` from: " << e->getTag() <<  ": You must inititate the TransfromComponent or UIComponent..." << endl; }
    };
    lua["Entity"]["cSetVelocity"] = [](intptr_t entity_lua, float x, float y) {
        Entity* e = ((Entity*) entity_lua);

        if(e->hasComponent<TransformComponent>()) {
            ((Entity*) entity_lua)->getComponent<TransformComponent>().setPointsVelocity(x, y);
        } else { cout << "Warning /!\\ function `setVelocity` from: " << e->getTag() <<  ": You must inititate the TransfromComponent..." << endl; }
    };
    // ======
    lua["Entity"]["cIsDragging"] = [](intptr_t entity_lua) {
        Entity* e = ((Entity*) entity_lua);

        if(e->hasComponent<DragComponent>())
            return e->getComponent<DragComponent>().isDragging();
        else {
            cout << "Warning /!\\ function `isDragging` from: " << e->getTag() <<  ": You must inititate the DragComponent..." << endl;
            return false;
        }
    };
}

void Game::update() {
    // Handler some keys debug
    #pragma GCC diagnostic warning "-Woverflow"
    #pragma GCC diagnostic error "-Woverflow"
    #pragma GCC diagnostic ignored "-Woverflow"
    
    sManager->update();

    handler->getSubsystem()->setTitle("Exocet state: " + to_string(sManager->getCurrentState()) + " | e: " + to_string(sManager->getEntityManager()->getNumberEntities()));
    if(handler->getJustKey(SDLK_ESCAPE))
        handler->closeGame();
    if(handler->getJustKey(SDLK_F2))
        sManager->previousState();
    if(handler->getJustKey(SDLK_F3))
        sManager->nextState();
    if(handler->getJustKey(SDLK_F5)) {
        sManager->restart();
        cout << handler->getJustKey(SDLK_F5) << endl;
    }
    else if(handler->getJustKey(SDLK_F7))
        sManager->getEntityManager()->destroyAllEntities();
}

void Game::render() {
    handler->getGraphic()->setRenderColor(0x00, 0x00, 0x00);
    handler->getGraphic()->renderClear();

    // render all game here
    sManager->render();

    handler->getGraphic()->renderPresent();
}