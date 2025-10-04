#pragma once

#include "ecs/components.hpp"

namespace exocet {
    class State {
        protected:
            Handler* handler;

            EntityManager* eManager;
            std::string tag;

        public:
            State(std::string tag = "noname_state") { 
                this->tag = tag; 
            }

            void init() {}
            void update() { eManager->update(); eManager->refresh(); }
            void render() { eManager->render(); }

            void loadState();

            inline EntityManager* getEntityManager() { return eManager; }
            inline std::string getTag() const { return tag; }
            inline void setEntityManager(EntityManager* entityManager) { eManager = entityManager; }
            inline void setHandler(Handler* handler) { this->handler = handler; }
    };

    class StateManager {
        private:
            Handler* handler;

            std::vector<std::unique_ptr<State>> states;
            EntityManager eManager;

            /**
             * \brief The index of the current state
             */
            std::size_t current;
        public:
            inline void update() { getState()->update(); }
            inline void render() { getState()->render(); }

            inline void addState(State* state) {
                state->setEntityManager(getEntityManager());
                state->setHandler(handler);

                std::unique_ptr<State> uPtr { state };
                states.emplace_back(std::move(uPtr));
            }

            void initStates();
            
            inline void restart() { setState(current); }
            inline void nextState() { if(current < states.size() - 1) setState(current + 1); }
            inline void previousState() { if(current > 0) setState(current - 1); }

            inline std::size_t getCurrentState() { return current; }
            inline EntityManager* getEntityManager() { return &eManager; }
            inline State* getState() { return states[current].get(); }
            
            inline void setHandler(Handler* handler) { eManager.setHandler(handler); this->handler = handler; } 
            void setState(std::size_t state);
    };
}