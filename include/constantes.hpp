#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <sol/sol.hpp>

namespace exocet { class Handler; }

#define EXOCET_ENGIN_VERSION 1

#define WIN_MIN_WIDTH 780
#define WIN_MIN_HEIGHT 480

#define FPS 60
#define FRAME_DELAY 1000/FPS

#define HITBOX_DEFAULT_SIZE 32
#define PHYSIC_DEFALULT_MASSE 10.f
#define PHYSIC_DEFAULT_SPEED 1.5f
#define PHYSIC_DEFAULT_MAXSPEED 15.f
#define PHYSIC_DEFAULT_FRICTION 0.8f