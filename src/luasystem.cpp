#include "luasystem.hpp"
#include "handler.hpp"

#define SOL_ALL_SAFETIES_ON 1

#define lua (*this)

using namespace exocet;
using namespace std;

LuaSystem::LuaSystem(Handler* handler) {
    this->handler = handler;

    // Load main lib and package
    lua.open_libraries(sol::lib::base, sol::lib::package, sol::lib::io, sol::lib::string, sol::lib::os, sol::lib::math);

    initRectClass();

    initUsertypeLuaVector2D();
    initUsertypePolygon();

    cout << "Success to initiate all usertypes" << endl;
    
    preloadPackages((string) DIR_SCRIPT + "lib/", "lib");

    cout << "Success to initiate all libs' package" << endl;

    initEngine();
    initEntity();

    cout << "Success to initiate all specific methods" << endl;

    preloadPackages(DIR_SCRIPT, "module");

    cout << "Success to initiate all modules' package" << endl;
}

void LuaSystem::initUsertypeLuaVector2D() {
    lua.new_usertype<LuaVector2D>(USERTYPE_LUAVECTOR2D,
        sol::meta_function::construct, 
        sol::factories(
            [](sol::object) {
                return make_shared<LuaVector2D>(0.f, 0.f);
            },

            [](sol::object, const lua_Number& x, const lua_Number& y) {
                return make_shared<LuaVector2D>(x, y);
            }
        ),

        sol::meta_function::addition, &LuaVector2D::operator+,
        sol::meta_function::subtraction, &LuaVector2D::operator-,
        sol::meta_function::multiplication, &LuaVector2D::operator*,
        
        "getAngle", &LuaVector2D::getAngle,
        "x", &LuaVector2D::x,
        "y", &LuaVector2D::y
    );
}

void LuaSystem::initRectClass() {
    lua.script(R"a(Rect = {x = 0,y = 0,w = 0,h = 0}
Rect.__index = Rect
function Rect:new(x, y, w, h)
    local r = {}
    setmetatable(r, Rect)
    if (w == nil) and (h == nil) then
        w = x;h = y;x = 0;y = 0;
    end
    r.x = x;r.y = y;r.w = w;r.h = h;
    return r
end
function Rect:__tostring()return "(x: " .. self.x .." ; y: " .. self.y .. " ; w: " .. self.w .." ; h: " .. self.h ..")"end)a");
}

void LuaSystem::initUsertypePolygon() {
    lua.new_usertype<Polygon>(USERTYPE_POLYGON,
        sol::meta_function::construct,
        sol::factories(
            [](sol::object) {
                return make_shared<Polygon>();
            },
            [](sol::object, sol::table vertices) {
                return make_shared<Polygon>(vertices);
            }
        ),
        sol::meta_function::index, &Polygon::getVertex
    );
}

void LuaSystem::preloadPackages(const std::string pathDir, const std::string name) {
    sol::optional<sol::error> res = lua.safe_script_file(pathDir + name + ".lua");

    if(res) {
        cerr << res->what() << endl;
        handler->closeGame();
    }

    // Check if the module field exists in the config
    if(lua[name] == sol::nil) {
        cerr << "You must have `" << name << "`..." << endl;
        handler->closeGame();
    }

    // Load all modules homemade
    lua[name].get<sol::table>().for_each([&](sol::object const& key, sol::object const& value) {
        sol::optional<sol::error> maybeErr = lua.safe_script_file(pathDir + value.as<string>() + ".lua");

        if(maybeErr) {
            cerr << "File: " << pathDir << value.as<string>() + ".lua has an err:" << endl << maybeErr->what() << endl;
            handler->closeGame();
        }
    });
}

void LuaSystem::initEngine() {
    lua.script(R"(engine = {mainEntities={}})");
    // set the handler pointeur in engine.lua lib
    lua["engine"]["_handler"] = (intptr_t) handler;

    #define hLua self.get<intptr_t>("_handler")

    // ============ ALL SUBSYS METHODS ====
    lua["engine"]["getWinHeight"] = [](sol::table self) { return ((Handler*) hLua)->getWinHeight(); };
    lua["engine"]["getWinWidth"] = [](sol::table self) { return ((Handler*) hLua)->getWinWidth(); };
    lua["engine"]["closeGame"] = [](sol::table self) { ((Handler*) hLua)->closeGame(); };
    lua["engine"]["isResizing"] = [](sol::table self) { return ((Handler*) hLua)->getSubsystem()->isResizing(); };
    
    lua["engine"]["getKey"] = [](sol::table self, Uint16 scancode) { return ((Handler*) hLua)->getKey(scancode); };
    lua["engine"]["getJustKey"] = [](sol::table self, Uint16 scancode) { return ((Handler*) hLua)->getJustKey(scancode); };
    lua["engine"]["getKeyCode"] = [](sol::table self) { return ((Handler*) hLua)->getSubsystem()->getKeyListener()->getKeyCode(); };
    lua["engine"]["getAnyKey"] = [](sol::table self) { return ((Handler*) hLua)->getAnyKey(); };
    lua["engine"]["getJustAnyKey"] = [](sol::table self) { return ((Handler*) hLua)->getJustAnyKey(); };

    lua["engine"]["getButton"] = [](sol::table self, Uint16 scancode) { return ((Handler*) hLua)->getButton(scancode); };
    lua["engine"]["getJustButton"] = [](sol::table self, Uint16 scancode) { return ((Handler*) hLua)->getJustButton(scancode); };
    lua["engine"]["getButtonCode"] = [](sol::table self) { return ((Handler*) hLua)->getSubsystem()->getMouseListener()->getButtonCode(); };
    lua["engine"]["getMousePosition"] = [](sol::table self) {
        auto vec = ((Handler*) hLua)->getMousePosition();
        return make_shared<LuaVector2D>(vec.x, vec.y);
    };

    lua["engine"]["mute"] = [](sol::table self) { ((Handler*) hLua)->getSubsystem()->mute(); };
    lua["engine"]["unmute"] = [](sol::table self) { ((Handler*) hLua)->getSubsystem()->unmute(); };
    lua["engine"]["isMuting"] = [](sol::table self) { return ((Handler*) hLua)->getSubsystem()->isMuting(); };
    lua["engine"]["getVolume"] = [](sol::table self, const string path) { return ((Handler*) hLua)->getState()->getSong("res/" + path)->getVolume(); };
    lua["engine"]["setVolume"] = [](sol::table self, const string path, int volume) {
        Handler* handler = (Handler*) hLua;
        if(!handler->getSubsystem()->isMuting())
            handler->getState()->getSong("res/" + path)->setVolume(volume); 
    };
    lua["engine"]["playSong"] = [](sol::table self, const string path, sol::object ticksObject) {
        Handler* handler = (Handler*) hLua;
        int ticks = (ticksObject == sol::nil)? -1: ticksObject.as<int>();
        
        if(!handler->getSubsystem()->isMuting()) 
            handler->getState()->getSong("res/" + path)->play(ticks); 
    };
    lua["engine"]["isPlayingSong"] = [](sol::table self, const string path) { return ((Handler*) hLua)->getState()->getSong("res/" + path)->isPlaying(); };
    lua["engine"]["setSong"] = [](sol::table self, const string path) { ((Handler*) hLua)->getState()->setSong("res/" + path); };

    // ======== ALL STATES METHODS =====
    lua["engine"]["setState"] = [](sol::table self, size_t state) { ((Handler*) hLua)->getGame()->getStateManager()->setState(state); };
    lua["engine"]["getCurrentState"] = [](sol::table self) { ((Handler*) hLua)->getGame()->getStateManager()->getCurrentState(); };
    lua["engine"]["restart"] = [](sol::table self) { ((Handler*) hLua)->getGame()->getStateManager()->restart(); };
    lua["engine"]["nextState"] = [](sol::table self) { ((Handler*) hLua)->getGame()->getStateManager()->nextState(); };
    lua["engine"]["previousState"] = [](sol::table self) { ((Handler*) hLua)->getGame()->getStateManager()->previousState(); };
    lua["engine"]["restart"] = [](sol::table self) { ((Handler*) hLua)->getGame()->getStateManager()->restart(); };

    // ========= ALL GFX METHODS
    lua["engine"]["setColor"] = [](sol::table self, int r, int g, int b, int a) {
        ((Handler*) hLua)->getGraphic()->setColor(r, g, b, a);
    };
    lua["engine"]["renderRect"] = [](sol::table self, LuaVector2D position, int w, int h) {
        ((Handler*) hLua)->getGraphic()->renderRect(position.convert<int>(), w, h);
    };
    lua["engine"]["renderFillRect"] = [](sol::table self, LuaVector2D position, int w, int h) {
        ((Handler*) hLua)->getGraphic()->renderFillRect(position.convert<int>(), w, h);
    };
    lua["engine"]["renderAnchorRect"] = [](sol::table self, LuaVector2D position, int w, int h) {
        ((Handler*) hLua)->getGraphic()->renderAnchorRect(position.convert<int>(), w, h);
    };
    lua["engine"]["renderAnchorFillRect"] = [](sol::table self, LuaVector2D position, int w, int h) {
        ((Handler*) hLua)->getGraphic()->renderAnchorFillRect(position.convert<int>(), w, h);
    };
    lua["engine"]["centerOnEntity"] = [](sol::table self, sol::table entity) {
        ((Handler*) hLua)->getGraphic()->centerOnEntity(((Entity*) entity.get<intptr_t>("_ptr")));
    };
    lua["engine"]["getCameraPosition"] = [](sol::table self) { 
        auto vec = ((Handler*) hLua)->getGraphic()->getCamera()->getPosition();
        return make_shared<LuaVector2D>(static_cast<lua_Number>(vec.x), static_cast<lua_Number>(vec.y));
    };
    lua["engine"]["renderText"] = [](sol::table self, LuaVector2D position, int width, int height, string text) {
        ((Handler*) hLua)->getGraphic()->renderText(
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            width,
            height,
            text,
            ((Handler*) hLua)->getGraphic()->freeRoyalty
        );
    };
    lua["engine"]["renderPolygon"] = [](sol::table self, LuaVector2D position, sol::table polygon) {
        ((Handler*) hLua)->getGraphic()->renderPolygon(position.convert<int>(), Polygon(polygon.get<sol::table>("polygon")));
    };
    lua["engine"]["getBackgroundPosition"] = [](sol::table self) {
        auto vec = ((Handler*) hLua)->getGame()->getStateManager()->getBackground()->getPosition(); 
        return make_shared<LuaVector2D>(static_cast<lua_Number>(vec.x), static_cast<lua_Number>(vec.y));
    };
    lua["engine"]["setBackgroundPosition"] = [](sol::table self, LuaVector2D position) {
        ((Handler*) hLua)->getGame()->getStateManager()->getBackground()->setPosition(position.convert<int>()); 
    };
    lua["engine"]["setBackgroundSize"] = [](sol::table self, int w, int h) { ((Handler*) hLua)->getGame()->getStateManager()->getBackground()->setSize(w, h); };
    lua["engine"]["addEntity"] = [](sol::table self, sol::table entity_lua) { (((Handler*) hLua)->getEntityManager()->addEntityFromLua(entity_lua)); };
}

void LuaSystem::initEntity() {
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
    lua["Entity"]["cFitSizeWithHitbox"] = [](intptr_t entity_lua) {
        Entity* e = ((Entity*) entity_lua);
        if(e->hasComponent<SpriteComponent>()) {
            e->getComponent<SpriteComponent>().fitSizeWithHitbox();
        } else { cout << "Warning /!\\ function `fitSizeWithHitbot` from: " << e->getTag() <<  ": You must inititate the SpriteComponent..." << endl; }
    };
    lua["Entity"]["cSetTexture"] = [](intptr_t entity_lua, const string path, int x, int y, int w, int h, size_t nbFrames) {
        Entity* e = (Entity*) entity_lua;
        if(e->hasComponent<SpriteComponent>()) {
            e->getComponent<SpriteComponent>().initFrameFromSheet("res/" + path, nbFrames, x, y, w, h);
        } else
            cout << "Warning /!\\ function `setTexture` from: " << e->getTag() <<  ": You must inititate the SpriteComponent..." << endl;
    };
    lua["Entity"]["cSetTextureAngle"] = [](intptr_t entity_lua, const double angle) {
        Entity* e = (Entity*) entity_lua;
        if(e->hasComponent<SpriteComponent>()) {
            e->getComponent<SpriteComponent>().setAngle(angle);
        } else
             cout << "Warning /!\\ function `setTextureAngle` from: " << e->getTag() <<  ": You must inititate the SpriteComponent..." << endl;
    };
    lua["Entity"]["cGetFrameAnimation"] = [](intptr_t entity_lua) {
        Entity* e = (Entity*) entity_lua;
        if(e->hasComponent<SpriteComponent>()) {
            return e->getComponent<SpriteComponent>().getFrame();
        }
        cout << "Warning /!\\ function `getFrameAnimation` from" << e->getTag() << ": You must initiate the SpriteComponent" << endl;
        return  (size_t)0;
    };
    // ***************** Methods from ParticleComponent ****************
    lua["Entity"]["cGetTime"] = [](intptr_t entity_lua) {
        Entity* e = (Entity*) entity_lua;
        if(e->hasComponent<ParticleComponent>()) {
            return e->getComponent<ParticleComponent>().getTime();
        }
        cout << "Warning /!\\ function `getTime` from" << e->getTag() << ": You must initiate the ParticleComponent" << endl;
        return 0;
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
    lua["Entity"]["cIsOutsideScreen"] = [](intptr_t entity_lua) {
        Entity* e = (Entity*) entity_lua;
        if(e->hasComponent<HitboxComponent>())
            return e->getComponent<HitboxComponent>().isOutsideScreen();
        else
            cout << "Warning: function `isOutsideScreen` from" << e->getTag() << ". You must initiate the HitboxComponent" << endl;
        return false;
    };
    lua["Entity"]["cSetRect"] = [](intptr_t entity_lua, int xpos, int ypos, int width, int height) {
        Entity* e = (Entity*) entity_lua;

        if(e->hasComponent<HitboxComponent>()) {
            e->getComponent<HitboxComponent>().setRect(xpos, ypos, width, height);
        } else if(e->hasComponent<UIComponent>()) {
            e->getComponent<UIComponent>().setRect(xpos, ypos, width, height);
        } else
            cout << "Warning: function `setRect` from" << e->getTag() << ". You must initiate the HitboxComponent or UIComponent" << endl;
    };
    lua["Entity"]["cDestroyOutsideScreen"] = [](intptr_t entity_lua) {
        Entity* e = (Entity*) entity_lua;
        if(e->hasComponent<HitboxComponent>())
            e->getComponent<HitboxComponent>().destroyOutsideScreen();
        else
            cout << "Warning: function `destroyOutsideScreen` from" << e << ". You must initiate the HitboxComponent" << endl;
    };
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