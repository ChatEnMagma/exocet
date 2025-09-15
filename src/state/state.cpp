#include "state/state.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

void State::loadState() {
    sol::state lua;

    lua.open_libraries(sol::lib::base);
    lua.script_file("script/state/" + tag + ".lua");

    sol::table entities = lua["state"]["entities"];

    for(size_t i = 1; i < entities.size() + 1; i++) {
        sol::table e = entities[i];
        sol::table components = e["components"];

        auto& entity = eManager->addEntity(e["tag"]);


        for(size_t j = 1; j < components.size() + 1; j++) {
            sol::table c = components[j];

            string tag = c.get<string>("tag");

            if(tag == "physic") {
                auto& physic = entity.addComponent<PhysicComponent>();
                physic.setPointsPosition(c["position"]["x"], c["position"]["y"]);
                physic.getHitbox()->setHitbox(c["hitbox"]["x"], c["hitbox"]["y"], c["hitbox"]["w"], c["hitbox"]["h"]);
                if(c["masse"] != sol::nil)
                    physic.setMasse(c["masse"]);
                if(c["color"] != sol::nil)
                    physic.getHitbox()->setColor(c["color"][0], c["color"][1], c["color"][2]);
            }
            if(tag == "player") {
                auto& player = entity.addComponent<PlayerComponent>();
                player.setPointsPosition(c["position"]["x"], c["position"]["y"]);
                player.getPhysic()->getHitbox()->setHitbox(c["hitbox"]["x"], c["hitbox"]["y"], c["hitbox"]["w"], c["hitbox"]["h"]);
                if(c["masse"] != sol::nil)
                    player.getPhysic()->setMasse(c["masse"]);
            }
        }
    }
}

void StateManager::loadState() {
    sol::state lua;

    lua.open_libraries(sol::lib::base);

    lua.script_file("script/state/state.lua");

    sol::table states = lua["states"];

    for(size_t i = 1; i < states.size() + 1; i++) {
        State* state = new State(states.get<string>(i));

        addState(state);
    }
}