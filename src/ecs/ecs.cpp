#include "ecs/ecs.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

Entity::Entity(Handler* handler, std::string tag) {
    this->handler = handler;

    this->tag = tag;
    this->active = true;

    this->componentsLua = handler->getLua()->create_table();
    this->data = handler->getLua()->create_table();
}

void Entity::addGroup(Group group) {
    groupBitset[group] = true;
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
    for_each(entitiedAdd.begin(), entitiedAdd.end(), [this](Entity* e) {
        entities.emplace_back(move(unique_ptr<Entity> { e }));
    });
    
    entitiedAdd.clear();
}

Entity& EntityManager::addEmptyEntity(string tag) {
    Entity* e = new Entity(handler, tag);
    // Add into entities tmp
    entitiedAdd.emplace_back(e);

    return *e;
}

void EntityManager::addEntity(Entity* e) { entitiedAdd.emplace_back(e); }
