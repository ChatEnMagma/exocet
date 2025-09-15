#pragma once

#include <array>
#include <algorithm>
#include <bitset>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "constantes.hpp"

namespace exocet {
    class Entity;
    class Component;
    class EntityManager;

    using ComponentID = std::size_t;
    using Group = std::size_t;

    constexpr ComponentID maxComponents = 32UL;
    constexpr Group maxGroup = 32UL;

    using ComponentBitset = std::bitset<maxComponents>;
    using GroupBitset = std::bitset<maxGroup>;

    using ComponentArray = std::array<Component*, maxComponents>;

    enum groupLabels: Group {
        GROUP_COLLIDER
    };

    inline ComponentID getNewComponentTypeID() {
        static ComponentID lastID = 0UL;
        return lastID++;
    }

    template <typename T> inline ComponentID getComponentTypeID() noexcept {
        static_assert(std::is_base_of<Component, T>::value, "");
        static ComponentID typeID = getNewComponentTypeID();
        return typeID;
    }

    class Component {
        protected:
            Handler* handler;
            Entity* entity;
        public:
            virtual void init() {}
            virtual void update() {}
            virtual void render() {}

            inline Entity* getEntity() { return entity; }
            inline void setEntity(Entity* entity) { this->entity = entity; }
            inline void setHandler(Handler* handler) { this->handler = handler; }
    };

    class Entity {
        private:
            Handler* handler;

            bool active;

            std::string tag;

            std::vector<std::unique_ptr<Component>> components;
            ComponentArray componentArray;

            ComponentBitset componentBitset;
            GroupBitset groupBitset;
        public:
            Entity(Handler* handler, std::string tag);

            inline void update() { for(auto& c: components) c->update(); }
            inline void render() { for(auto& c: components) c->render(); }

            /**
             * \brief It kills or destroys the entity
             */
            inline void destroy() { active = false; }
            /**
             * \return true if the entity is active or alive else false
             */
            inline bool isActive() { return active; }

            inline std::string getTag() { return tag; }

            /**
             * \brief Check if the entity is well in the group
             * \return true if the entity is in the group else false
             */
            inline bool hasGroup(Group group) const { return groupBitset[group]; }
            inline void delGroup(Group group) { groupBitset[group] = false; }
            void addGroup(Group group);

            /**
             * \brief Check if the entity has well this component
             * \return true if the entity has this component else false
             */
            template <typename T> 
            inline bool hasComponent() const { return componentBitset[getComponentTypeID<T>()]; }

            template <typename T> 
            T& getComponent() const {
                auto ptr(componentArray[getComponentTypeID<T>()]);
                return *static_cast<T*>(ptr);
            }
            /**
             * \brief Add a component to entity
             * \param args all arguments need for the component
             * \return the component add to entity
             */
            template <typename T, typename... Targs> 
            T& addComponent(Targs&&... args) {
                T* c(new T(std::forward<Targs>(args)...));

                c->setEntity(this);
                c->setHandler(handler);

                std::unique_ptr<Component> uPtr { c };
                components.emplace_back(move(uPtr));

                componentArray[getComponentTypeID<T>()] = c;
                componentBitset[getComponentTypeID<T>()] = true;

                c->init();
                return *c;
            }
    };

    class EntityManager {
        private:
            Handler* handler;

            std::vector<std::unique_ptr<Entity>> entities;
            std::array<std::vector<Entity*>, maxGroup> groupedEntities;
        public:
            inline void update() { for(auto& e: entities) e->update(); this->refresh(); }
            inline void render() { for(auto& e: entities) e->render(); }

            void refresh();

            Entity& addEntity(std::string tag);

            inline void destroyAllEntities() { entities = std::vector<std::unique_ptr<Entity>>(); }

            inline void addToGroup(Entity* entity, Group group) { groupedEntities[group].emplace_back(entity); entity->addGroup(group); }
            inline std::vector<Entity*> getGroup(Group group) { return groupedEntities[group]; }

            inline void setHandler(Handler* handler) { this->handler = handler; }
            inline Handler* getHandler() { return handler; }
    };
}