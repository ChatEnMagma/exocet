#pragma once

#include "ecs/components.hpp"
#include "background.hpp"

namespace exocet {
    class State {
        protected:
            Handler* handler;

            EntityManager* eManager;
            EntityManager* uiManager;
            Background* background;

            sol::function initLua;

            std::string tag;

        public:
            State(std::string tag = "noname_state", sol::function initLua = sol::nil) { 
                this->tag = tag; 

                this->initLua = initLua;
            }

            void init() { if(initLua != sol::nil) initLua(); }
            void update() { background->update(); eManager->update(); eManager->refresh(); uiManager->update(); uiManager->refresh(); }
            void render() { background->render(); eManager->render(); uiManager->render(); }

            void loadState();

            inline EntityManager* getEntityManager() { return eManager; }
            inline EntityManager* getUIManager() { return uiManager; }
            inline std::string getTag() const { return tag; }
            inline void setEntityManager(EntityManager* entityManager) { eManager = entityManager; }
            inline void setUIManager(EntityManager* uiManager) { this->uiManager = uiManager; }
            inline void setBackground(Background* background) { this->background = background; }
            inline void setHandler(Handler* handler) { this->handler = handler; }
    };

    class StateManager {
        private:
            Handler* handler;

            std::vector<std::unique_ptr<State>> states;
            EntityManager eManager;
            EntityManager uiManager;
            Background background;

            State* loadingState;

            /**
             * \brief The index of the current state
             */
            std::size_t current;
        public:
            inline void update() { getState()->update(); }
            inline void render() { getState()->render(); }

            inline void addState(State* state) {
                state->setEntityManager(getEntityManager());
                state->setUIManager(getUIManager());
                state->setBackground(getBackground());
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
            inline EntityManager* getUIManager() { return &uiManager; }
            inline Background* getBackground() { return &background; }
            inline State* getState() { return states[current].get(); }
            
            inline void setHandler(Handler* handler) { 
                eManager.setHandler(handler);
                uiManager.setHandler(handler);
                background.setHandler(handler);
                
                this->handler = handler; 
            } 
            void setState(std::size_t state);
    };
}