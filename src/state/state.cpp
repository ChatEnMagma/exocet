#include "state/state.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

void State::loadState() {
    sol::state& lua = *handler->getLua();

    if(lua[getTag()]["background"] != sol::nil) {

        lua[getTag()]["background"]["textures"].get<sol::table>().for_each([&](sol::object const& key, sol::object const& value) {
            background->append(
                value.as<sol::table>()["zindex"].get<size_t>(),
                handler->getGraphic()->getSprite("res/" + value.as<sol::table>()["path"].get<string>())
            );
            
            // Set the position of the backgrounds
            background->setPosition(value.as<sol::table>()["postion"].get_or<LuaVector2D>(*(new LuaVector2D(0, 0))).convert<int>());
        });

        background->setSize(
            lua[getTag()]["background"].get<sol::table>()["size"]["w"].get<int>(),
            lua[getTag()]["background"].get<sol::table>()["size"]["h"].get<int>()
        );

        if(lua[getTag()]["background"]["loop"] != sol::nil) {
            background->setLoop(true);
        }
    }

    // For each all entities from lua
    if(lua[getTag()]["entities"] != sol::nil) {
        lua[getTag()]["entities"].get<sol::table>().for_each([&](sol::object const& keyEntity, sol::object const& valueEntity) {
            eManager->addEntityFromLua(valueEntity.as<sol::table>());
        });
    }
    if(lua[getTag()]["uis"] != sol::nil) {
        lua[getTag()]["uis"].get<sol::table>().for_each([&](sol::object const& keyEntity, sol::object const& valueEntity) {
            uiManager->addEntityFromLua(valueEntity.as<sol::table>());
        });
    }
}

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
    getState()->loadState();

    cout << "Finish initiate the state" << endl;
}