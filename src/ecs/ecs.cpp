#include "ecs/ecs.hpp"

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
}

Entity& EntityManager::addEntity(string tag) {
    Entity* e = new Entity(handler, tag);
    unique_ptr<Entity> uPtr { e };

    entities.emplace_back(move(uPtr));

    return *e;
}