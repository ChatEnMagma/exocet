#pragma once

#include "state/state.hpp"

namespace exocet {
    class DebugState: public State {
        void init() override;

        void update() override;
        void render() override;
    };
}