#include "ecs/ecs.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

Entity::Entity(Handler* handler, std::string tag) {
    this->handler = handler;

    this->tag = tag;

    active = true;
}

void Entity::addGroup(Group group) {
    groupBitset[group] = true;
    
}

void Entity::addComponentsFromLua(sol::state* lua, sol::table component) {
    string tag = component.get<string>("tag");

    if(tag == "physic") {
        auto& physic = addComponent<PhysicComponent>();
        if(component["position"] != sol::nil) {
            physic.setPointsPosition(
                component["position"]["x"], 
                component["position"]["y"]
            );
        }
        if(component["velocity"] != sol::nil) {
            physic.setPointsVelocity(
                component["velocity"]["x"], 
                component["velocity"]["y"]
            );
        }
        if(component["hitbox"] != sol::nil) {
            physic.getHitbox()->setHitbox(
                component["hitbox"]["x"], 
                component["hitbox"]["y"], 
                component["hitbox"]["w"], 
                component["hitbox"]["h"]
            );
        }
    if(component["masse"] != sol::nil)
        physic.setMasse(component["masse"]);
    if(component["color"] != sol::nil)
        physic.getHitbox()->setColor(component["color"][0], component["color"][1], component["color"][2]);
    } else if(tag == "script") {
        addComponent<ScriptComponent>(component);
    } else if(tag == "sprite") {
        SpriteComponent& sprite = addComponent<SpriteComponent>();

        sprite.setTexture("res/" + component["path"].get<string>());

        if(component["size"] != sol::nil) {
            sprite.setSize(component["size"]["w"], component["size"]["h"]);
        }
        if(component["fitSizeWithHitbox"] != sol::nil) {
            sprite.fitSizeWithHitbox();
        }
    }else if(tag == "drag") {
        addComponent<DragComponent>();
    } else if(tag == "ui") {
        UIComponent& ui = addComponent<UIComponent>();

        if(component["rect"] != sol::nil) {
            ui.setRect(component["rect"]["x"], component["rect"]["y"], component["rect"]["w"], component["rect"]["h"]);
        }
    } else if(tag == "button") {
        ButtonComponent& button = addComponent<ButtonComponent>();

        if(component["func"] != sol::nil) {
            button.setFunction(component["func"].get<function<void()>>());
        }
        if(component["rect"] != sol::nil) {
            button.setRect(component["rect"]["x"], component["rect"]["y"], component["rect"]["w"], component["rect"]["h"]);
        } else {
            cout << "Warning from `" << getTag() << "` you should initiate the rect of ButtonComponent" << endl;
        }
    } else {
        cout << "Warning: unknow component `" << tag << "`" << endl;
    }
}

void EntityManager::refresh() {
    for(Group i = 0u; i < maxGroup; i++) {
         auto& v(groupedEntities[i]);
        v.erase(
            std::remove_if(
                std::begin(v), std::end(v),
                [i](Entity* e) { return !e->isActive() || !e->hasGroup(i); }
            ),
            std::end(v)
        );
    }
    entities.erase(
        std::remove_if(
            std::begin(entities), 
            std::end(entities), 
            [](const std::unique_ptr<Entity> &e) { return !e->isActive(); }
        ),
        std::end(entities)
    );
    // Add all entities from entity tmp will add
    for(Entity* e: entitiedAdd) {
        unique_ptr<Entity> uPtr { e };
        entities.emplace_back(move(uPtr));
    }
    entitiedAdd.clear();
}

Entity& EntityManager::addEntity(string tag) {
    Entity* e = new Entity(handler, tag);
    // Add into entities tmp
    entitiedAdd.emplace_back(e);

    return *e;
}

Entity& EntityManager::addEntityFromLua(sol::table e) {
    sol::state& lua = *handler->getLua();

    // Check if the entity have entity in the field
    if(e["entity"] == sol::nil) {
        cerr << "Error, you are trying add an entity from lua file without entity in the field" << endl;
        handler->closeGame();   // Close the game
        return addEntity("Err");
    }
    
    // Make C-Entity
    Entity& entity = addEntity(e["entity"]["tag"].get<string>());
    // Set the C-pointer into lua entity
    e["entity"]["setEntity"](e["entity"], (intptr_t) &entity);

    // Add all components for C-Entity
    if(e["components"] != sol::nil) {
        e["components"].get<sol::table>().for_each([&](sol::object const& keyComponent, sol::object const& valueComponent) {
            entity.addComponentsFromLua(&lua, valueComponent.as<sol::table>());
        });
    } else {
        cout << "Warning /!\\ for " << entity.getTag() << " you should add components..." << endl;
    }

    return entity;
}