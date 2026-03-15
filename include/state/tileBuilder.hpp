#pragma once

#include <string>
#include <vector>

#include "state.hpp"

namespace exocet {
    class TileBuilder {
        private:
            Handler& handler;

            std::vector<std::vector<std::size_t>> lines;
            
            int w, h;
        public:
            TileBuilder(Handler& handler, int width, int height): handler(handler) {
                this->w = width;
                this->h = height;
            }
            ~TileBuilder() = default;

            TileBuilder& addLine(std::vector<std::size_t> line);

            void settupTiles(State& state) {
                std::vector<std::size_t> tiles;

                for(auto line: lines)
                    for(auto index: line)
                        tiles.emplace_back(index);

                state.settupTiles(w, h, tiles);
            }
    };
}