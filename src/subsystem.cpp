#include "subsystem.hpp"

using namespace std;
using namespace exocet;

bool Subsystem::init(int w, int h, string title) {
    // init the SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cerr << "Fail to initiate SDL: " << SDL_GetError() << endl;
        return false;
    }
    // init the TTF
    if(TTF_Init() != 0) {
        cerr << "Fail to initiate TTF: " << TTF_GetError() << endl;
        return false;
    }
    // set the window size
    this->w = max(WIN_MIN_WIDTH, w);
    this->h = max(WIN_MIN_HEIGHT, h);
    // set the title window
    this->title = title;

    win = SDL_CreateWindow(
        this->title.c_str(), 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        this->w, 
        this->h, 
        0
    );

    if(win == NULL) {
        cerr << "Fail to initiate the window: " << SDL_GetError() << endl;
        return false; 
    }

    // create the renderer
    gfx = new Graphic(SDL_CreateRenderer(
        win, 
        -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE
    ));

    if(gfx->getRenderer() == NULL) {
        cerr << "Fail to initiate the renderer: " << SDL_GetError() << endl;
        return false;
    }

    running = true;

    cout << "Success to ititiate the subsystem" << endl;

    return true;
}

void Subsystem::handleEvents() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if(e.type == SDL_QUIT)
            close();
        // Keylistener methods
        if(e.type == SDL_KEYDOWN)
            keys.interactKey(e.key.keysym.sym, true);
        if(e.type == SDL_KEYUP)
            keys.interactKey(e.key.keysym.sym, false);

        // MouseListener methods
        mouse.move(e.motion.x, e.motion.y);

        if(e.type == SDL_MOUSEBUTTONDOWN)
            mouse.interact(e.button.button, true);
        if(e.type == SDL_MOUSEBUTTONUP)
            mouse.interact(e.button.button, false);
    }

    keys.update();
    mouse.update();
}

void Subsystem::clean() {
    gfx->clean();

    // All SDL clean
    SDL_DestroyWindow(win);
    SDL_Quit();
    TTF_Quit();

    cout << "The subsystem is well clean, bye..." << endl;
}