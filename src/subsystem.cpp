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
    SDL_PollEvent(&e);

    if(e.type == SDL_QUIT)
        close();
    // Keylistener methods
    if(e.type == SDL_KEYDOWN)
        keys.interactKey(e.key.keysym.sym, true);
    if(e.type == SDL_KEYUP)
        keys.interactKey(e.key.keysym.sym, false);
}

void Subsystem::clean() {
    gfx->clean();

    // All SDL clean
    SDL_DestroyWindow(win);
    SDL_Quit();
    TTF_Quit();

    cout << "The subsystem is well clean, bye..." << endl;
}