#pragma once

#include <iostream>
#include <string>
#include "constantes.hpp"

namespace exocet {
    class PlaySong {
        private:
            Mix_Chunk* chunk;
            bool loop;
        public:
            PlaySong(const std::string path, bool loop = false) {
                chunk = Mix_LoadWAV(path.c_str());
                if(chunk == NULL) {
                    std::cerr << "Error to load song from " << path << ": " << Mix_GetError() << std::endl;
                    return;
                }
                this->loop = loop;
            }
            ~PlaySong() { clean(); }
            inline void play() {
                Mix_PlayChannel(-1, chunk, loop);
            }
            inline bool isLoop() const { return loop; }
            inline void clean() { Mix_FreeChunk(chunk); }
    };
}