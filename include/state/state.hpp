#pragma once


#include <string>
#include <map>
#include <memory>

#include "ecs/components.hpp"
#include "background.hpp"
#include "tool/playSong.hpp"

namespace exocet {
    class State {
        protected:
            Handler* handler;

            EntityManager* eManager;
            EntityManager* uiManager;
            Background* background;

            sol::function initLua;
            sol::function updateLua;
            sol::function renderLua;

            std::string tag;
            std::map<std::string, std::unique_ptr<PlaySong>> songs;
        public:
            State(Handler* handler) noexcept { 
                this->handler = handler;
                
                this->tag = "no_name"; 

                this->initLua = sol::nil;
                this->updateLua = sol::nil;
                this->renderLua = sol::nil;
            }

            State(Handler* handler, std::string tag, sol::function initLua, sol::function updateLua, sol::function renderLua) noexcept { 
                this->handler = handler;
                
                this->tag = tag; 

                this->initLua = initLua;
                this->updateLua = updateLua;
                this->renderLua = renderLua;
            }
            ~State() noexcept { songs.clear(); }

            void init() { if(initLua != sol::nil) initLua(); }
            void update() { 
                if(updateLua != sol::nil) updateLua();
                
                background->update(); 
                eManager->update(); 
                eManager->refresh(); 
                uiManager->update(); 
                uiManager->refresh(); 
            }
            void render() {
                if(renderLua != sol::nil) renderLua();

                background->render(); 
                eManager->render(); 
                uiManager->render(); 
            }

            inline EntityManager* getEntityManager() noexcept { return eManager; }
            inline EntityManager* getUIManager() noexcept { return uiManager; }
            inline std::string getTag() const noexcept { return tag; }
            inline void setEntityManager(EntityManager* entityManager) noexcept { eManager = entityManager; }
            inline void setUIManager(EntityManager* uiManager) noexcept { this->uiManager = uiManager; }
            inline void setBackground(Background* background) noexcept { this->background = background; }
            PlaySong* getSong(const std::string& key, const std::string& path = "") {
                auto it = songs.find(key);

                if(it == songs.end() && path.empty())
                    throw std::runtime_error("you must initiate the path when you want to load a new song...");
                if(it == songs.end())
                    songs[key] = std::move(std::make_unique<PlaySong>(path));

                return songs[key].get();
            }
    };

    class StateManager {
        private:
            Handler* handler;

            std::vector<std::unique_ptr<State>> states;
            std::unique_ptr<EntityManager> eManager;
            std::unique_ptr<EntityManager> uiManager;
            std::unique_ptr<Background> background;

            /**
             * \brief The index of the current state
             */
            std::size_t current;
        public:
            StateManager(Handler* handler) noexcept;
            ~StateManager() noexcept = default;

            inline void update() { getState()->update(); }
            inline void render() { getState()->render(); }

            inline void addState(std::unique_ptr<State> state) noexcept {
                state->setEntityManager(getEntityManager());
                state->setUIManager(getUIManager());
                state->setBackground(getBackground());

                states.emplace_back(std::move(state));
            }

            void initStates();
            
            inline void restart() { setState(current); }
            inline void nextState() { if(current < states.size() - 1) setState(current + 1); }
            inline void previousState() { if(current > 0) setState(current - 1); }

            inline std::size_t getCurrentState() noexcept { return current; }
            inline EntityManager* getEntityManager() noexcept { return eManager.get(); }
            inline EntityManager* getUIManager() noexcept { return uiManager.get(); }
            inline Background* getBackground() noexcept { return background.get(); }
            inline State* getState() noexcept { return states[current].get(); }
            
            void setState(std::size_t state);
    };
}