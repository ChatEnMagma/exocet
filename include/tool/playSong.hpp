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
            static Uint8 volume[MIX_CHANNELS];

            PlaySong(const std::string path, int loop = 1) {
                if((chunk = Mix_LoadWAV(path.c_str())) == NULL)
                    throw std::runtime_error("Error to load song from " + path + ": " + std::string(Mix_GetError()));

                this->channelPlay = -1;
                this->loop = loop;

                std::cout << "Success open the song from: " << path << std::endl;
            }
            ~PlaySong() noexcept { Mix_FreeChunk(chunk); }

            void play(int ticks = -1) noexcept {
                channelPlay = Mix_PlayChannelTimed(-1, chunk, loop, ticks);
                PlaySong::volume[channelPlay] = chunk->volume;
            }

            inline bool isPlaying() const noexcept { return (channelPlay == -1)? false: ((bool) Mix_Playing(channelPlay)); }
            inline bool isLoop() const noexcept { return loop; }
            inline void pause() noexcept { Mix_Pause(channelPlay); }
            inline void resume() noexcept { Mix_Resume(channelPlay); }
            inline void setVolume(Uint8 volume) noexcept { if(channelPlay >= 0) { Mix_Volume(channelPlay, volume); PlaySong::volume[channelPlay] = volume; } }
            inline Uint8 getVolume() const noexcept { return (channelPlay != 1)? 0: PlaySong::volume[channelPlay]; }
    };
}