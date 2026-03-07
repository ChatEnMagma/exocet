#pragma once


#include <string>
#include <map>
#include <memory>

#include "tool/playSong.hpp"

#include "ecs/components.hpp"

#include "background.hpp"
#include "tile.hpp"

namespace exocet {
    class State {
        protected:
            Handler* handler;

            EntityManager* eManager;
            EntityManager* uiManager;
            Background* background;
            TileManager* tileManager;

            sol::function initLua;
            sol::function updateLua;
            sol::function renderLua;

            std::string tag;
            std::map<std::string, std::unique_ptr<PlaySong>> songs;

            int w, h;
            std::vector<std::size_t> tiles;

            void renderTiles();
        public:
            State(Handler* handler) noexcept;
            State(Handler* handler, std::string tag, sol::function initLua, sol::function updateLua, sol::function renderLua) noexcept;
            ~State() noexcept { songs.clear(); }

            void init() { if(initLua != sol::nil) initLua(); }
            void update();
            void render();

            void settupTiles(int width, int height, std::vector<std::size_t> tiles);

            Tile* getTile(const EngineVector2D& position) const noexcept {
                auto pos = position.convert<int>();

                if(pos.x < 0 || pos.y < 0 || pos.x > w || pos.y > h) return tileManager->getDefaultTile();
                return tileManager->getTile(tiles[(w * pos.y) + pos.x]);
            }
            inline bool getTileFlags(const EngineVector2D& position, int flags) const noexcept { return getTile(position)->isFlags(flags); }
            inline EntityManager* getEntityManager() noexcept { return eManager; }
            inline EntityManager* getUIManager() noexcept { return uiManager; }
            inline std::string getTag() const noexcept { return tag; }

            PlaySong* getSong(const std::string& key, const std::string& path = "") {
                auto it = songs.find(key);

                if(it == songs.end() && path.empty())
                    throw std::runtime_error("you must initiate the path when you want to load a new song...");
                if(it == songs.end())
                    songs[key] = std::move(std::make_unique<PlaySong>(path));

                return songs[key].get();
            }

            inline void setEntityManager(EntityManager* entityManager) noexcept { eManager = entityManager; }
            inline void setUIManager(EntityManager* uiManager) noexcept { this->uiManager = uiManager; }
            inline void setBackground(Background* background) noexcept { this->background = background; }
            inline void setTileManager(TileManager* tileManager) noexcept { this->tileManager = tileManager; }
    };

    class StateManager {
        private:
            Handler* handler;

            std::vector<std::unique_ptr<State>> states;

            std::unique_ptr<EntityManager> eManager;
            std::unique_ptr<EntityManager> uiManager;

            std::unique_ptr<TileManager> tileManager;

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
                state->setTileManager(getTileManager());

                states.emplace_back(std::move(state));
            }

            void initStates();
            
            inline void restart() { setState(current); }
            inline void nextState() { if(current < states.size() - 1) setState(current + 1); }
            inline void previousState() { if(current > 0) setState(current - 1); }
            
            // All getters and setters
            
            inline State* getState() noexcept { return states[current].get(); }
            inline std::size_t getCurrentState() noexcept { return current; }

            inline EntityManager* getEntityManager() noexcept { return eManager.get(); }
            inline EntityManager* getUIManager() noexcept { return uiManager.get(); }
            
            inline Background* getBackground() noexcept { return background.get(); }
            inline TileManager* getTileManager() noexcept { return tileManager.get(); }
            
            void setState(std::size_t state);
    };
}