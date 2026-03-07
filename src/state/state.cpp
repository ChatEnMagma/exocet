#include "state/state.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

int Tile::size = DEFAULT_TILE_SIZE;

State::State(Handler* handler) noexcept {
    this->handler = handler;
                
    this->tag = "no_name"; 

    this->initLua = sol::nil;
    this->updateLua = sol::nil;
    this->renderLua = sol::nil;

    w = 0;
    h = 0;
}

State::State(Handler* handler, std::string tag, sol::function initLua, sol::function updateLua, sol::function renderLua) noexcept { 
    this->handler = handler;
                
    this->tag = tag; 

    this->initLua = initLua;
    this->updateLua = updateLua;
    this->renderLua = renderLua;

    w = 0;
    h = 0;
}

void State::update() {
    if(updateLua != sol::nil) updateLua();
                
    background->update(); 
    eManager->update(); 
    eManager->refresh(); 
    uiManager->update(); 
    uiManager->refresh(); 
}

void State::render() {
    if(renderLua != sol::nil) renderLua();

    background->render(); 
    renderTiles();

    eManager->render(); 
    uiManager->render(); 
}

void State::renderTiles() {
    auto posCam = handler->getGraphic()->getCamera();
    
    EngineVector2D posTile;

    for(int y = 0; y < h; y++) {
        for(int x = 0; x < w; x++) {
            posTile.setPoints(x, y);

            getTile(posTile)->render(posTile);
        }
    }
}

void State::settupTiles(int w, int h, vector<size_t> tiles) {
    this->w = w;
    this->h = h;
    this->tiles = tiles;
}

StateManager::StateManager(Handler* handler) noexcept {
    this->handler = handler;

    eManager = make_unique<EntityManager>(handler);
    uiManager = make_unique<EntityManager>(handler);

    tileManager = make_unique<TileManager>(handler);

    background = make_unique<Background>(handler);
}

void StateManager::initStates() {
    sol::state_view lua(handler->getLua()->lua_state());

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
        addState(move(state));
    });
}

void StateManager::setState(std::size_t state) { 
    eManager->destroyAllEntities();
    uiManager->destroyAllEntities();
    background->refresh();

    handler->getGraphic()->getCamera()->setPosition(EngineVector2D::vectorZeros());

    current = state;

    getState()->init();

    cout << "Finish initiate the state" << endl;
}