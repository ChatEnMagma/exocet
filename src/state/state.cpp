#include "state/state.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

void State::loadState() {
    sol::state& lua = *handler->getLua();

    lua.script_file(DIR_SCRIPT_STATES + getTag() + ".lua");

    // For each all entities from lua
    lua["state"]["entities"].get<sol::table>().for_each([&](sol::object const& keyEntity, sol::object const& valueEntity) {
        eManager->addEntityFromLua(valueEntity.as<sol::table>());
    });
}

void StateManager::initStates() {
    sol::state& lua = *handler->getLua();

    // Check if the config file from lua have states field
    if(lua["config"]["states"] == sol::nil) {
        cerr << "You must have `states` field in the config..." << endl;
        handler->closeGame();
    }

    // For each all states
    lua["config"]["states"].get<sol::table>().for_each([&](sol::object const& key, sol::object const& value) {
        // Make a new state with the tag from config
        State* state = new State(value.as<string>());
        addState(state);
    });
}

void StateManager::setState(std::size_t state) { 
    eManager.destroyAllEntities();

    current = state;
    getState()->loadState();
}