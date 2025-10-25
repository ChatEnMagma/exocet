#pragma once

#include "ecs/ecs.hpp"

namespace exocet {
    class ScriptComponent: public Component {
        private:
            sol::function initLua;
            sol::function updateLua;
            sol::function renderLua;
        public:
            /**
             * \param component The component settings from lua file
             */
            ScriptComponent(sol::table component) {
                initLua =   component.get<sol::function>("init");
                updateLua = component.get<sol::function>("update");
                renderLua = component.get<sol::function>("render");
            }

            void init() override {   if(initLua != sol::nil)     initLua(); }
            void update() override { if(updateLua != sol::nil) { updateLua(); } }
            void render() override { if(renderLua != sol::nil) renderLua(); }
    };
}