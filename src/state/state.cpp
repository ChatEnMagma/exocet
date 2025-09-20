#include "state/state.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

void State::addComponentEntityLua(sol::state* lua, sol::table component, Entity* entity, size_t indexEntity, size_t indexComponent) {
    string tag = component.get<string>("tag");

    if(tag == "physic") {
        auto& physic = entity->addComponent<PhysicComponent>();
        physic.setPointsPosition(
            component["position"]["x"], 
            component["position"]["y"]
        );
        physic.getHitbox()->setHitbox(
            component["hitbox"]["x"], 
            component["hitbox"]["y"], 
            component["hitbox"]["w"], 
            component["hitbox"]["h"]
        );
    if(component["masse"] != sol::nil)
        physic.setMasse(component["masse"]);
    if(component["color"] != sol::nil)
        physic.getHitbox()->setColor(component["color"][0], component["color"][1], component["color"][2]);
    }
    if(tag == "player") {
        auto& player = entity->addComponent<PlayerComponent>();
        if(component["position"] != sol::nil) {
            player.setPointsPosition(
                component["position"]["x"], 
                component["position"]["y"]
            );
        }
        if(component["hitbox"] != sol::nil) {
            player.getPhysic()->getHitbox()->setHitbox(
                component["hitbox"]["x"], 
                component["hitbox"]["y"], 
                component["hitbox"]["w"], 
                component["hitbox"]["h"]
            );
        }
        if(component["masse"] != sol::nil)
            player.getPhysic()->setMasse(component["masse"]);
    }
    if(tag == "script") {
        entity->addComponent<ScriptComponent>(DIR_SCRIPT_STATES + getTag() + ".lua", indexEntity, indexComponent);
    }
}

void State::loadState() {
    sol::state& lua = *handler->getLua();

    lua.script_file(DIR_SCRIPT_STATES + getTag() + ".lua");

    sol::table entities = lua["state"]["entities"];

    entities.for_each([&](sol::object const& keyEntity, sol::object const& valueEntity) {
        sol::table e = valueEntity;
        sol::table components = e["components"];

        auto& entity = eManager->addEntity(e["tag"]);

        components.for_each([&](sol::object const& keyComponent, sol::object const& valueComponent) {
            addComponentEntityLua(&lua, valueComponent.as<sol::table>(), &entity, keyEntity.as<size_t>(), keyComponent.as<size_t>());
        });
    });
}

void StateManager::loadState() {
    sol::state& lua = *handler->getLua();

    lua.script_file(string(DIR_SCRIPT) + "config.lua");
    sol::table states = lua["config"]["states"];

    states.for_each([&](sol::object const& key, sol::object const& value) {
        State* state = new State(value.as<string>());

        addState(state);
    });
}