#include "state/state.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

StateManager::StateManager(Handler* handler) noexcept {
    this->handler = handler;

    eManager = make_unique<EntityManager>(handler);
    uiManager = make_unique<EntityManager>(handler);
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

    handler->getGraphic()->getCamera()->setPosition(IntVector2D());

    current = state;

    getState()->init();

    cout << "Finish initiate the state" << endl;
}