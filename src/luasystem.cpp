#include "luasystem.hpp"
#include "handler.hpp"

#include "state/tileBuilder.hpp"

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
    initUsertypeSprite();
    initUsertypeBackground();
    initUsertypeSong();
    initUsertypeTileBuilder();

    initUsertypeEntity();
    initUsertypeComponents();

    cout << "Success to initiate all usertypes" << endl;

    initEngine();

    cout << "Success to initiate all specific methods" << endl;

    preloadPackages(DIR_SCRIPT, "module");

    cout << "Success to initiate all modules' package" << endl;
}

void LuaSystem::initRectClass() noexcept {
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

void LuaSystem::initUsertypeLuaVector2D() {
    lua.new_usertype<EngineVector2D>(USERTYPE_LUAVECTOR2D,
        sol::meta_function::construct, 
        sol::factories(
            [](sol::object) noexcept { return make_shared<EngineVector2D>(0.f, 0.f); },
            [](sol::object, const lua_Number& x, const lua_Number& y) noexcept { return make_shared<EngineVector2D>(x, y); }
        ),

        sol::meta_function::addition, &EngineVector2D::operator+,
        sol::meta_function::subtraction, &EngineVector2D::operator-,
        sol::meta_function::multiplication, &EngineVector2D::operator*,
        
        "getAngle", &EngineVector2D::getAngle,
        "x", &EngineVector2D::x,
        "y", &EngineVector2D::y
    );
}

void LuaSystem::initUsertypePolygon() {
    lua.new_usertype<Polygon>(USERTYPE_POLYGON,
        sol::meta_function::construct,
        sol::factories(
            [](sol::object) noexcept { return make_shared<Polygon>(); },
            [](sol::object, sol::table vertices) noexcept { return make_shared<Polygon>(vertices); }
        ),
        sol::meta_function::index, &Polygon::getVertex
    );
}

void LuaSystem::initUsertypeBackground() {
    lua.new_usertype<Background>(USERTYPE_BACKGROUND,
        "append", sol::factories(
            [](Background& self, Sprite* sprite) { self.append(sprite); },
            &Background::append
        ),

        "getPosition", [](Background& self) noexcept { return self.getPosition().convert<lua_Number>(); },
        "getWidth", &Background::getWidth,
        "getHeight", &Background::getHeight,
        
        "setPosition", &Background::setPosition,
        "setSize", &Background::setSize,
        "setLoop", &Background::setLoop
    );
}

void LuaSystem::initUsertypeTileBuilder() {
    lua.new_usertype<TileBuilder>(USERTYPE_TILE_BUILDER,
        sol::meta_function::construct, [this](sol::object, int w, int h) { return make_shared<TileBuilder>(this->handler, w, h); },
        "addLine", [](TileBuilder& self, sol::variadic_args args) {
            vector<size_t> tiles;

            for(auto v: args)
                tiles.emplace_back(v.as<size_t>());

            return self.addLine(tiles);
        },
        "settupTiles", &TileBuilder::settupTiles
    );
}

void LuaSystem::initUsertypeSprite() {
    lua.new_usertype<Sprite>(USERTYPE_SPRITE,
        "render", sol::factories(
            [](Sprite& sprite, const EngineVector2D& pos, int w, int h) noexcept { sprite.render(pos, w, h); },
            &Sprite::render
        ),
        "renderAnchor", sol::factories(
            [](Sprite& sprite, const EngineVector2D& pos, int w, int h) noexcept { sprite.renderAnchor(pos, w, h); },
            &Sprite::renderAnchor
        ),
        "renderAngle", sol::factories(
            [](Sprite& sprite, const EngineVector2D& pos, double a, int w, int h) noexcept { sprite.renderAngle(pos, a, w, h); },
            &Sprite::renderAngle
        ),
        "renderAnchorAngle", sol::factories(
            [](Sprite& sprite, const EngineVector2D& pos, double a, int w, int h) noexcept { sprite.renderAnchorAngle(pos, a, w, h); },
            &Sprite::renderAnchorAngle
        ),

        "getWidth", &Sprite::getWidth,
        "getHeight", &Sprite::getHeight
    );
}

void LuaSystem::initUsertypeSong() {
    lua.new_usertype<PlaySong>(USERTYPE_SONG,
        "play", sol::factories(
            [](PlaySong& self) noexcept { self.play(); },
            &PlaySong::play
        ),
        "getVolume", &PlaySong::getVolume,
        "setVolume", &PlaySong::setVolume,
        "isPlaying", &PlaySong::isPlaying,
        "isLoop", &PlaySong::isLoop
    );
}

void LuaSystem::initUsertypeEntity() {
    lua.new_usertype<Entity>(USERTYPE_ENTITY,
        sol::meta_function::construct, sol::factories(
            [](sol::object, sol::this_main_state s) noexcept {
                sol::state_view mLua(s.lua_state());

                return new Entity((Handler*) mLua["engine"]["_handler"].get<intptr_t>(), "missigno");
            },
            [](sol::object, const string& tag, sol::this_main_state s) noexcept {
                sol::state_view mLua(s.lua_state());

                return new Entity((Handler*) mLua["engine"]["_handler"].get<intptr_t>(), tag);
            }
        ),
        "components", &Entity::componentsLua,
        "data", &Entity::data,
        "destroy", &Entity::destroy,
        "componentSize", &Entity::componentSize
    );
}

void LuaSystem::initUsertypeComponents() {
    lua.new_usertype<AnchorComponent>(USERTYPE_ANCHOR_COMPONENT,
        sol::meta_function::construct, sol::factories(
            [](sol::object, Entity& e, sol::table rect) { 
                auto& c = e.addComponent<AnchorComponent>();
                
                e.componentsLua[USERTYPE_ANCHOR_COMPONENT] = &c;

                c.getHitbox()->setRect(
                    rect["x"].get<int>(),
                    rect["y"].get<int>(),
                    rect["w"].get<int>(),
                    rect["h"].get<int>()
                );

                return &c;
            },
            [](sol::object, Entity& e, sol::table rect, const EngineVector2D& position) {
                auto& c = e.addComponent<AnchorComponent>();

                e.componentsLua[USERTYPE_ANCHOR_COMPONENT] = &c;
                
                c.getHitbox()->setRect(
                    rect["x"].get<int>(),
                    rect["y"].get<int>(),
                    rect["w"].get<int>(),
                    rect["h"].get<int>()
                );
                c.setPosition(position);

                return &c;
            }
        ),

        "isCollide", [](AnchorComponent& self, Entity* e) {
            if(!e->hasComponent<HitboxComponent>()) { cout << "Warning: the entity: `" << e->getTag() << "` must have hitboxComponent" << endl; return false; }
            return self.getHitbox()->isCollide(e->getComponent<HitboxComponent>());
        },

        "getPosition", [](AnchorComponent& self) noexcept { return self.getPosition().convert<lua_Number>(); }
    );

    lua.new_usertype<InputComponent>(USERTYPE_INPUT_COMPONENT,
        sol::meta_function::construct, [](sol::object, Entity& e) {
            auto& c = e.addComponent<InputComponent>();

            e.componentsLua[USERTYPE_INPUT_COMPONENT] = &c;

            return &c;
        }
    );

    lua.new_usertype<PhysicComponent>(USERTYPE_PHYSIC_COMPONENT,
        sol::meta_function::construct, sol::factories(
            [](sol::object, Entity& e, sol::table rect) { 
                auto& c = e.addComponent<PhysicComponent>();
                
                e.componentsLua[USERTYPE_PHYSIC_COMPONENT] = &c;

                c.getHitbox()->setRect(
                    rect["x"].get<int>(),
                    rect["y"].get<int>(),
                    rect["w"].get<int>(),
                    rect["h"].get<int>()
                );

                return &c;
            },
            [](sol::object, Entity& e, sol::table rect, const EngineVector2D& position) {
                auto& c = e.addComponent<PhysicComponent>();

                e.componentsLua[USERTYPE_PHYSIC_COMPONENT] = &c;
                
                c.getHitbox()->setRect(
                    rect["x"].get<int>(),
                    rect["y"].get<int>(),
                    rect["w"].get<int>(),
                    rect["h"].get<int>()
                );
                c.setPosition(position);

                return &c;
            }
        ),

        "isCollide", [](AnchorComponent& self, Entity* e) {
            if(!e->hasComponent<HitboxComponent>()) { cout << "Warning: the entity: `" << e->getTag() << "` must have hitboxComponent" << endl; return false; }
            return self.getHitbox()->isCollide(e->getComponent<HitboxComponent>());
        },

        "getAcceleration", &PhysicComponent::getAccelation,
        "getMasse", &PhysicComponent::getMasse,
        "getPosition", &PhysicComponent::getPosition,
        "getVelocity", &PhysicComponent::getVelocity,
        "getFriction", &PhysicComponent::getFriction,
        "getSpeed", &PhysicComponent::getSpeed,
        "getMaxSpeed", &PhysicComponent::getMaxSpeed,

        "setAcceleration", &PhysicComponent::getAccelation,
        "setMasse", &PhysicComponent::setMasse,
        "setPosition", &PhysicComponent::setPosition,
        "setVelocity", &PhysicComponent::setVelocity,
        "setFriction", &PhysicComponent::setFriction,
        "setSpeed", &PhysicComponent::setSpeed,
        "setMaxSpeed", &PhysicComponent::setMaxSpeed
    );

    lua.new_usertype<SpriteComponent>(USERTYPE_SPRITE_COMPONENT,
        sol::meta_function::construct, sol::factories(
            [](sol::object, Entity& e, Sprite* sprite) {
                auto& c = e.addComponent<SpriteComponent>();

                e.componentsLua[USERTYPE_SPRITE_COMPONENT] = c;
                
                c.setSprite(sprite);

                return &c;
            },
            [](sol::object, Entity& e, Sprite* sprite, int fps) {
                auto& c = e.addComponent<SpriteComponent>();

                e.componentsLua[USERTYPE_SPRITE_COMPONENT] = c;
                
                c.setSprite(sprite);
                c.setFPS(fps);

                return &c;
            }
        ),
        "fitSizeWithHitbox", &SpriteComponent::fitSizeWithHitbox,
        "setFPS", &SpriteComponent::setFPS
    );

    lua.new_usertype<ScriptComponent>(USERTYPE_SCRIPT_COMPONENT,
        sol::meta_function::construct, sol::factories(
            [](sol::object, Entity& e, sol::object init, sol::object update, sol::object render) {
                auto& c = e.addComponent<ScriptComponent>(init, update, render);

                e.componentsLua[USERTYPE_SCRIPT_COMPONENT] = c;

                return &c;
            },
            [](sol::object, Entity& e, sol::object update) {
                auto& c = e.addComponent<ScriptComponent>(sol::nil, update, sol::nil);

                e.componentsLua[USERTYPE_SCRIPT_COMPONENT] = c;

                return &c;
            }
        )
    );
}

void LuaSystem::preloadPackages(const std::string pathDir, const std::string name) {
    sol::optional<sol::error> res = lua.safe_script_file(pathDir + name + ".lua");

    if(res)
        throw runtime_error(res->what());

    // Check if the module field exists in the config
    if(lua[name] == sol::nil)
        throw invalid_argument("You must have `" + name + "`...");
        

    // Load all modules homemade
    lua[name].get<sol::table>().for_each([&](sol::object, sol::object const& value) {
        string file = pathDir + value.as<string>() + ".lua";

        if(lua["config"]["logOpenLuaFiles"].get_or<bool>(0))
            cout << "open the file: " << file << endl;

        sol::optional<sol::error> maybeErr = lua.safe_script_file(file);

        if(maybeErr)
            throw runtime_error("File: " + file + " has an err:" + maybeErr->what());
    });
}

void LuaSystem::initEngine() noexcept {
    lua.script(R"(engine = {mainEntities={}})");
    // set the handler pointeur in engine.lua lib
    lua["engine"]["_handler"] = (intptr_t) handler;

    #define hLua self.get<intptr_t>("_handler")

    lua["engine"]["addTile"] = [](sol::table self, Sprite* sprite, int flags) {
        ((Handler*) hLua)->getGame()->getStateManager()->getTileManager()->addTile(sprite, bitset<SIZE_BIT_TILE_FLAG>(flags));
    };

    // ============ ALL SUBSYS METHODS ====
    lua["engine"]["getWinHeight"] = [](sol::table self) noexcept { return ((Handler*) hLua)->getWinHeight(); };
    lua["engine"]["getWinWidth"] = [](sol::table self) noexcept { return ((Handler*) hLua)->getWinWidth(); };
    lua["engine"]["closeGame"] = [](sol::table self) noexcept { ((Handler*) hLua)->closeGame(); };
    lua["engine"]["isResizing"] = [](sol::table self) noexcept { return ((Handler*) hLua)->getSubsystem()->isResizing(); };
    
    lua["engine"]["getKey"] = [](sol::table self, Uint16 scancode) noexcept { return ((Handler*) hLua)->getKey(scancode); };
    lua["engine"]["getJustKey"] = [](sol::table self, Uint16 scancode) noexcept { return ((Handler*) hLua)->getJustKey(scancode); };
    lua["engine"]["getKeyCode"] = [](sol::table self) noexcept { return ((Handler*) hLua)->getSubsystem()->getKeyListener()->getKeyCode(); };
    lua["engine"]["getAnyKey"] = [](sol::table self) noexcept { return ((Handler*) hLua)->getAnyKey(); };
    lua["engine"]["getJustAnyKey"] = [](sol::table self) noexcept { return ((Handler*) hLua)->getJustAnyKey(); };

    lua["engine"]["getButton"] = [](sol::table self, Uint16 scancode) noexcept { return ((Handler*) hLua)->getButton(scancode); };
    lua["engine"]["getJustButton"] = [](sol::table self, Uint16 scancode) noexcept { return ((Handler*) hLua)->getJustButton(scancode); };
    lua["engine"]["getButtonCode"] = [](sol::table self) noexcept { return ((Handler*) hLua)->getSubsystem()->getMouseListener()->getButtonCode(); };
    lua["engine"]["getMousePosition"] = [](sol::table self) noexcept {
        auto vec = ((Handler*) hLua)->getMousePosition();
        return make_shared<EngineVector2D>(vec.x, vec.y);
    };

    lua["engine"]["mute"] = [](sol::table self) noexcept { ((Handler*) hLua)->getSubsystem()->mute(); };
    lua["engine"]["unmute"] = [](sol::table self) noexcept { ((Handler*) hLua)->getSubsystem()->unmute(); };
    lua["engine"]["isMuting"] = [](sol::table self) noexcept { return ((Handler*) hLua)->getSubsystem()->isMuting(); };
    lua["engine"]["getSong"] = sol::factories(
        [](sol::table self, const string& key) { return ((Handler*) hLua)->getState()->getSong(key); },
        [](sol::table self, const string& key, const string& path) { return ((Handler*) hLua)->getState()->getSong(key, "res/" + path); }
    );

    // ======== ALL STATES METHODS =====
    lua["engine"]["setState"] = [](sol::table self, size_t state) { ((Handler*) hLua)->getGame()->getStateManager()->setState(state); };
    lua["engine"]["getState"] = [](sol::table self) { return ((Handler*) hLua)->getGame()->getStateManager()->getState(); };
    lua["engine"]["getCurrentState"] = [](sol::table self) noexcept { ((Handler*) hLua)->getGame()->getStateManager()->getCurrentState(); };
    lua["engine"]["restart"] = [](sol::table self) { ((Handler*) hLua)->getGame()->getStateManager()->restart(); };
    lua["engine"]["nextState"] = [](sol::table self) { ((Handler*) hLua)->getGame()->getStateManager()->nextState(); };
    lua["engine"]["previousState"] = [](sol::table self) { ((Handler*) hLua)->getGame()->getStateManager()->previousState(); };
    lua["engine"]["restart"] = [](sol::table self) { ((Handler*) hLua)->getGame()->getStateManager()->restart(); };

    lua["engine"]["setSizeTile"] = [](int size) noexcept { Tile::size = size; };

    // ========= ALL GFX METHODS
    lua["engine"]["setColor"] = sol::factories(
        [](sol::table self, int r, int g, int b) noexcept { ((Handler*) hLua)->getGraphic()->setColor(r, g, b); },
        [](sol::table self, int r, int g, int b, int a) noexcept { ((Handler*) hLua)->getGraphic()->setColor(r, g, b, a); }
    );
    lua["engine"]["renderRect"] = [](sol::table self, const EngineVector2D& position, int w, int h) noexcept { ((Handler*) hLua)->getGraphic()->renderRect(position, w, h); };
    lua["engine"]["renderFillRect"] = [](sol::table self, const EngineVector2D& position, int w, int h) noexcept { ((Handler*) hLua)->getGraphic()->renderFillRect(position, w, h); };
    lua["engine"]["renderAnchorRect"] = [](sol::table self, const EngineVector2D& position, int w, int h) noexcept { ((Handler*) hLua)->getGraphic()->renderAnchorRect(position, w, h); };
    lua["engine"]["renderAnchorFillRect"] = [](sol::table self, const EngineVector2D& position, int w, int h) noexcept { ((Handler*) hLua)->getGraphic()->renderAnchorFillRect(position, w, h); };
    lua["engine"]["centerOnEntity"] = [](sol::table self, Entity* entity) noexcept { ((Handler*) hLua)->getGraphic()->centerOnEntity(entity); };
    lua["engine"]["getCameraPosition"] = [](sol::table self) noexcept {  return ((Handler*) hLua)->getGraphic()->getCamera()->getPosition(); };
    lua["engine"]["renderText"] = [](sol::table self, const EngineVector2D& position, int width, int height, string text) {
        ((Handler*) hLua)->getGraphic()->renderText(
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            width,
            height,
            text,
            ((Handler*) hLua)->getGraphic()->getFont("res/FreeRoyalty.ttf", 20)
        );
    };
    lua["engine"]["renderPolygon"] = [](sol::table self, const EngineVector2D& position, const Polygon& polygon) noexcept {
        ((Handler*) hLua)->getGraphic()->renderPolygon(position, polygon);
    };
    
    
    lua["engine"]["getSprite"] = sol::factories(
        [](sol::table self, const string& key) { return ((Handler*) hLua)->getGraphic()->getSprite(key); },
        [](sol::table self, const string& key, const string& path) { return ((Handler*) hLua)->getGraphic()->getSprite(key, path); },
        [](sol::table self, const string& key, const string& path, int xPos, int yPos, int width, int height) { return ((Handler*) hLua)->getGraphic()->loadSpriteSheet(key, path, xPos, yPos, width, height); },
        [](sol::table self, const string& key, const string& path, int nCol, int nRow, int wsrc, int hsrc, size_t nbFrames) { return ((Handler*) hLua)->getGraphic()->getSprite(key, path, nCol, nRow, wsrc, hsrc, nbFrames); }
    );
    lua["engine"]["getBackground"] = [](sol::table self) noexcept { return ((Handler*) hLua)->getGame()->getStateManager()->getBackground(); };
    lua["engine"]["addEntity"] = [](sol::table self, Entity* e) noexcept { (((Handler*) hLua)->getEntityManager()->addEntity(e)); };
}
