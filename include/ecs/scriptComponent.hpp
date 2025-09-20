#pragma once

#include "ecs/ecs.hpp"

namespace exocet {
    class ScriptComponent: public Component {
        private:
            sol::table componentScriptLua;

            std::string pathlua;
            std::size_t indexEntity;
            std::size_t indexCompoent;
        public:
            /**
             * \param pathlua the path of lua file
             * \param indexEntity the index of entity in the state file lua
             * \param indexCompoent the index of component i.e scriptComponent of entity
             */
            ScriptComponent(std::string pathlua, std::size_t indexEntity, std::size_t indexCompoent);

            void init() override;

            void update() override;
            void render() override;

            /**
             * \brief reload the lua file
             */
            void refresh();

            inline void setPathLua(const std::string pathlua) { this->pathlua = pathlua; }
            inline std::string getPathLua() const { return pathlua; }
    };
}