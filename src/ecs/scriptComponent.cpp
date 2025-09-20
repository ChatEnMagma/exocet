#include "ecs/scriptComponent.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

ScriptComponent::ScriptComponent(string pathlua, size_t indexEntity, size_t indexCompoent) {
    this->indexEntity = indexEntity;
    this->indexCompoent = indexCompoent;
    this->pathlua = pathlua;
}

void ScriptComponent::refresh() {
    sol::state& lua = *handler->getLua();   // get lua with all libs
    lua.script_file(pathlua);               // load the lua file with entity got this script

    // set the entity pointer to lua file
    sol::table entity_lua = lua["state"]["entities"][indexEntity]["entity"];
    entity_lua["setEntity"](entity_lua, (intptr_t) entity);

    // set lua table for easy access functions
    this->componentScriptLua = lua["state"]["entities"][indexEntity]["components"][indexCompoent];
}

void ScriptComponent::init() {
    refresh();

    if(componentScriptLua["init"] != sol::nil)
        componentScriptLua["init"]();
}

void ScriptComponent::update() {
    if(componentScriptLua["update"] != sol::nil)
        componentScriptLua["update"]();
}

void ScriptComponent::render() {
    if(componentScriptLua["render"] != sol::nil)
        componentScriptLua["render"]();
}