#include <string>

#include "engine.hpp"
#include "handler.hpp"

using namespace std;
using namespace exocet;

void Engine::init(int w, int h, std::string title, bool fullscreen) {
    try {
        (subsys = make_unique<Subsystem>())->init(w, h, title);
    } catch(const bad_alloc& e) {
        cerr << "Error to initiate the subsystem..." << endl;
        exit(EXIT_FAILURE);
    }

    if(fullscreen)
        subsys->setFullscreen();

    game = make_unique<Game>(subsys.get());
}

void Engine::run() {
    cout << "Start the game..." << endl;

    Uint64 frameStart, frameTime;
    Uint64 frameLast = SDL_GetTicks64();

    double deltaTime;

    // main loop
    while(subsys->isRunning()) {
        frameStart = SDL_GetTicks64();

        deltaTime = (frameStart - frameLast) / 1000000.0f;

        subsys->handleEvents();
        game->update(deltaTime);
        game->render();

        frameLast = frameStart;

        // set up the delay, they game is limite by FPS
        frameTime = SDL_GetTicks64() - frameStart;
        if(FRAME_DELAY > frameTime) SDL_Delay(FRAME_DELAY - frameTime);
    }
}

int main(int argc, char** argv) {
    bool fullscreen = false;

    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "--fullscreen") == 0)
            fullscreen = true;
    }

    Engine engin;

    engin.init(WIN_MIN_WIDTH, WIN_MIN_HEIGHT, "Exocet", fullscreen);
    engin.run();

    return EXIT_SUCCESS;
}
