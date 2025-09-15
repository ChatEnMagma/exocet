#include "engine.hpp"
#include "handler.hpp"

using namespace std;
using namespace exocet;

bool Engine::init(int w, int h, std::string title) {
    subsys = new Subsystem();
    bool successInit = subsys->init(w, h, title);
    game = new Game(subsys);

    return successInit;
}

void Engine::run() {
    Uint32 frameStart, frameTime;
    // main loop
    while(subsys->isRunning()) {
        frameStart = SDL_GetTicks();

        subsys->handleEvents();
        game->update();
        game->render();

        // set up the delay, they game is limite by FPS
        frameTime = SDL_GetTicks() - frameStart;
        if(FRAME_DELAY > frameTime) SDL_Delay(FRAME_DELAY - frameTime);
    }
}

void Engine::clean() {
    lua_close(game->getLua());
    subsys->clean();
}