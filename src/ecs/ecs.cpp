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
                component["position"]["x"].get<int>(), 
                component["position"]["y"].get<int>()
            );
        }
        if(component["velocity"] != sol::nil) {
            physic.setPointsVelocity(
                component["velocity"]["x"].get<float>(), 
                component["velocity"]["y"].get<float>()
            );
        }
        if(component["hitbox"] != sol::nil) {
            if(component["hitbox"]["vertices"] == sol::nil) {
                physic.getHitbox()->setRect(
                    component["hitbox"]["x"].get<int>(),
                    component["hitbox"]["y"].get<int>(),
                    component["hitbox"]["w"].get<int>(),
                    component["hitbox"]["h"].get<int>()
                );
            } else {
                physic.getHitbox()->setPoly(Polygon(component["hitbox"]["vertices"].get<sol::table>()));
            }
        }

    if(component["masse"] != sol::nil)
        physic.setMasse(component["masse"].get<float>());
    if(component["color"] != sol::nil)
        physic.getHitbox()->setColor(
            component["color"][0].get<Uint8>(),
            component["color"][1].get<Uint8>(),
            component["color"][2].get<Uint8>()
        );
    } else if(tag == "script") {
        addComponent<ScriptComponent>(component);
    } else if(tag == "sprite") {
        SpriteComponent& sprite = addComponent<SpriteComponent>();

        if(component["fps"] != sol::nil) {
            sprite.setFPS(component["fps"].get<size_t>());
        } else cout << "/!\\ Warning from `" << getTag() << "` you should set fps" << endl;

        if(component["size"] != sol::nil && component["nTextures"] != sol::nil && component["path"] != sol::nil) {
            sprite.initFrameFromSheet(
                "res/" + component["path"].get<string>(),
                component["nTextures"].get<int>(),
                component["size"]["x"].get<int>(),
                component["size"]["y"].get<int>(),
                component["size"]["w"].get<int>(),
                component["size"]["h"].get<int>()
            );
        }else if(component["size"] == sol::nil) {
            sprite.initFrameFromSheet("res/" + component["path"].get<string>());
            sprite.fitSizeWithHitbox();
        }

        if(component["angle"] != sol::nil) {
            sprite.setAngle(component["angle"].get<double>());
        }
        
    } else if(tag == "drag") {
        addComponent<DragComponent>();
    } else if(tag == "ui") {
        UIComponent& ui = addComponent<UIComponent>();

        if(component["rect"] != sol::nil) {
            ui.setRect(
                component["rect"]["x"].get<int>(),
                component["rect"]["y"].get<int>(),
                component["rect"]["w"].get<int>(),
                component["rect"]["h"].get<int>()
            );
        }
    } else if(tag == "button") {
        ButtonComponent& button = addComponent<ButtonComponent>();

        if(component["func"] != sol::nil) {
            button.setFunction(component["func"].get<function<void()>>());
        }
        if(component["rect"] != sol::nil) {
            button.setRect(
                component["rect"]["x"].get<int>(),
                component["rect"]["y"].get<int>(),
                component["rect"]["w"].get<int>(),
                component["rect"]["h"].get<int>()
            );
        } else {
            cout << "Warning from `" << getTag() << "` you should initiate the rect of ButtonComponent" << endl;
        }
    } else if(tag == "particle") {
        ParticleComponent& particle = addComponent<ParticleComponent>();

        if(component["time"] != sol::nil)
            particle.setTime(component["time"]);
        if(component["position"] != sol::nil) {
            particle.setPointsPosition(
                component["position"]["x"].get<int>(),
                component["position"]["y"].get<int>()
            );
        }
        if(component["velocity"] != sol::nil) {
            particle.setPointsVelocity(
                component["velocity"]["x"].get<float>(),
                component["velocity"]["y"].get<float>()
            );
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