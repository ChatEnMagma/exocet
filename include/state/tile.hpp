#pragma once

#include <bitset>
#include <memory>
#include <vector>

#include "tool/vectors.hpp"
#include "gfx/graphic.hpp"

namespace exocet {
    constexpr std::size_t SIZE_BIT_TILE_FLAG = 8;
    constexpr int DEFAULT_TILE_SIZE = 32;

    enum TILE_FALGS {
        SOLID_UP_TILE =     0b000'0001,
        SOLID_DOWN_TILE =   0b000'0010,
        SOLID_LEFT_TILE =   0b000'0100,
        SOLID_RIGHT_TILE =  0b000'1000,
        SOLID_TILE =        0b000'1111,
    };

    class Tile {
        private:
            Sprite* sprite;
            std::bitset<SIZE_BIT_TILE_FLAG> flags;
        public:
            static int size;

            Tile(Sprite* sprite) {
                this->sprite = sprite;
            }
            Tile(Sprite* sprite, std::bitset<SIZE_BIT_TILE_FLAG> flags) {
                this->sprite = sprite;

                this->flags = flags;
            }
            virtual ~Tile() {};

            virtual void render(const EngineVector2D& position) noexcept { sprite->render(position.scalar(Tile::size), size, size); }

            inline bool isSolid() const noexcept { return (flags & std::bitset<SIZE_BIT_TILE_FLAG>(SOLID_TILE)).any(); }
            inline std::vector<bool> isSolidDirection() const noexcept {
                std::vector<bool> dir = { false, false, false, false };
                
                for(int i = 0; i < 4; i++)
                    dir[i] = flags.test(i);

                return dir;
            }
            inline bool isFlags(int flags) const noexcept { return (this->flags & std::bitset<SIZE_BIT_TILE_FLAG>(flags)).any(); }
    };

    class EmptyTile: public Tile {
        public:
            EmptyTile(): Tile(nullptr) {}
            EmptyTile(std::bitset<SIZE_BIT_TILE_FLAG> flags): Tile(nullptr, flags) {}
            ~EmptyTile() = default;

            void render([[maybe_unused]] const EngineVector2D& position) noexcept override {}
    };

    class TileManager {
        private:
            std::size_t defaultTile;
            std::vector<std::shared_ptr<Tile>> tiles;
        public:
            TileManager() {
                defaultTile = 0;

                tiles.emplace_back(std::make_shared<EmptyTile>());
            }

            ~TileManager() { tiles.clear(); }

            void addTile(Sprite* sprite, std::bitset<SIZE_BIT_TILE_FLAG> flags) {
                tiles.emplace_back(std::make_shared<Tile>(sprite, flags));
            }

            inline Tile& getDefaultTile() const noexcept { return *tiles[defaultTile].get(); }
            inline Tile& getTile(std::size_t index) const {
                if(index >= size()) throw std::runtime_error("Unknow tile from " + std::to_string(index));
                return *tiles[index].get();
            }
            inline bool getTileFlags(std::size_t index, int flags) { return getTile(index).isFlags(flags); }

            void setDefaultTile(std::size_t defaultTile) {
                if(defaultTile > size()) throw std::runtime_error("Unkown tile");
                this->defaultTile = defaultTile;
            }

            std::size_t size() const noexcept { return tiles.size(); }
    };
}