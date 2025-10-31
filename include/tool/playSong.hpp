#pragma once

#include <iostream>
#include <string>
#include "constantes.hpp"

namespace exocet {
    class PlaySong {
        private:
            Mix_Chunk* chunk;
            int loop;
        
            int channelPlay;
        public:
            static Uint8 volume[4];

            PlaySong(const std::string path, int loop = 1) {
                std::cout << path << std::endl;
                chunk = Mix_LoadWAV(path.c_str());
                if(chunk == NULL) {
                    std::cerr << "Error to load song from " << path << ": " << Mix_GetError() << std::endl;
                    return;
                }
                this->channelPlay = -1;
                this->loop = loop;
            }
            ~PlaySong() { clean(); }
            inline void play(int ticks = -1) {
                channelPlay = Mix_PlayChannelTimed(-1, chunk, loop, ticks);
                PlaySong::volume[channelPlay] = chunk->volume;
            }
            inline bool isPlaying() const { return (channelPlay == -1)? false: ((bool) Mix_Playing(channelPlay)); }
            inline bool isLoop() const { return loop; }
            inline void pause() { Mix_Pause(channelPlay); }
            inline void resume() { Mix_Resume(channelPlay); }
            inline void clean() { Mix_FreeChunk(chunk); }
            inline void setVolume(Uint8 volume) { if(channelPlay >= 0) { Mix_Volume(channelPlay, volume); PlaySong::volume[channelPlay] = volume; } }
            inline Uint8 getVolume() const { if(channelPlay != 1) return volume[channelPlay]; return 0; }
    };
}