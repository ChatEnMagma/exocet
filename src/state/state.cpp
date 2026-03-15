#include "state/state.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

int Tile::size = DEFAULT_TILE_SIZE;

State::State(Handler& handler): handler(handler) {
    this->tag = "no_name"; 

    this->initLua = sol::nil;
    this->updateLua = sol::nil;
    this->renderLua = sol::nil;

    w = 0;
    h = 0;
}

State::State(Handler& handler, std::string tag, sol::function initLua, sol::function updateLua, sol::function renderLua): handler(handler) { 
    this->tag = tag; 

    this->initLua = move(initLua);
    this->updateLua = move(updateLua);
    this->renderLua = move(renderLua);

    w = 0;
    h = 0;
}

void State::update() {
    if(updateLua.valid()) updateLua();

    auto& sManager = handler.getGame().getStateManager();

    sManager.getBackground().update();
    sManager.getEntityManager().update();
    sManager.getEntityManager().refresh();
    sManager.getUIManager().update();
    sManager.getUIManager().refresh();
}

void State::render() {
    if(renderLua.valid()) renderLua();

    auto& sManager = handler.getGame().getStateManager();

    sManager.getBackground().render();
    renderTiles();

    sManager.getEntityManager().render(); 
    sManager.getUIManager().render(); 
}

void State::renderTiles() {
    auto posCam = handler.getGraphic().getCamera();
    
    EngineVector2D posTile;

    for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
            posTile.setPoints(x, y);

            getTile(posTile).render(posTile);
        }
    }
}

void State::settupTiles(int w, int h, vector<size_t> tiles) {
    this->w = w;
    this->h = h;
    this->tiles = tiles;
}

Tile& State::getTile(const EngineVector2D& position) const noexcept {
    auto pos = position.convert<int>();

    if(pos.x < 0 || pos.y < 0 || pos.x >= w || pos.y >= h) return handler.getGame().getStateManager().getTileManager().getDefaultTile();

    return handler.getGame().getStateManager().getTileManager().getTile(tiles[(pos.y * w) + pos.x]);
}

StateManager::StateManager(Handler& handler): handler(handler) {
    eManager = make_unique<EntityManager>(handler);
    uiManager = make_unique<EntityManager>(handler);

    tileManager = make_unique<TileManager>();

    background = make_unique<Background>(handler);

    current = 0;
}

void StateManager::initStates() {
    sol::state_view lua(handler.getLua().lua_state());

    // Check if the config file from lua have states field
    if(lua["config"]["states"] == sol::nil)
        throw invalid_argument("You must have `states` field in the config...");

    // For each all states
    lua["config"]["states"].get<sol::table>().for_each([&](sol::object, sol::object const& value) {
        // Make a new state with the tag from config
        sol::optional<sol::error> maybeErr = lua.safe_script_file(DIR_SCRIPT_STATES + value.as<string>() + ".lua");

        if(maybeErr) throw runtime_error(maybeErr->what());

        auto state = make_unique<State>(
            handler,
            value.as<string>(), 
            lua[value.as<string>()]["init"].get<sol::function>(),
            lua[value.as<string>()]["update"].get<sol::function>(),
            lua[value.as<string>()]["render"].get<sol::function>()
        );
        states.emplace_back(move(state));
    });
}

void StateManager::setState(std::size_t state) { 
    eManager->destroyAllEntities();
    uiManager->destroyAllEntities();
    background->refresh();

    handler.getGraphic().getCamera().setPosition(EngineVector2D::vectorZeros());

    current = state;

    getState().init();

    cout << "Finish initiate the state" << endl;
}