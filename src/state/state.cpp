#include "state/state.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

void StateManager::initStates() {
    sol::state_view lua(handler->getLua()->lua_state());

    // Check if the config file from lua have states field
    if(lua["config"]["states"] == sol::nil) {
        cerr << "You must have `states` field in the config..." << endl;
        handler->closeGame();
    }

    // For each all states
    lua["config"]["states"].get<sol::table>().for_each([&](sol::object const& key, sol::object const& value) {
        // Make a new state with the tag from config
        sol::optional<sol::error> maybeErr = lua.safe_script_file(DIR_SCRIPT_STATES + value.as<string>() + ".lua");

        if(maybeErr) {
            cerr << maybeErr->what() << endl;
            handler->closeGame();
        }

        State* state = new State(
            value.as<string>(), 
            lua[value.as<string>()]["init"].get<sol::function>(),
            lua[value.as<string>()]["update"].get<sol::function>(),
            lua[value.as<string>()]["render"].get<sol::function>()
        );
        addState(state);
    });
}

void StateManager::setState(std::size_t state) { 
    eManager.destroyAllEntities();
    uiManager.destroyAllEntities();
    background.refresh();

    handler->getGraphic()->getCamera()->setPosition(Vector2D<int>());

    current = state;

    getState()->init();

    cout << "Finish initiate the state" << endl;
}