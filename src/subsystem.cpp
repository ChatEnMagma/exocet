#include "subsystem.hpp"
#include "tool/playSong.hpp"

using namespace std;
using namespace exocet;

Uint8 PlaySong::volume[] = { 0, 0, 0, 0 };

bool Subsystem::init(int w, int h, string title) {
    // init the SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cerr << "Fail to initiate SDL: " << SDL_GetError() << endl;
        return false;
    }
    if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        cerr << "Fail to initiate IMG: " << IMG_GetError() << endl;
        return false;
    }
    // init the TTF
    if(TTF_Init() != 0) {
        cerr << "Fail to initiate TTF: " << TTF_GetError() << endl;
        return false;
    }
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {
        cerr << "Fail to initiate Mixer: " << Mix_GetError() << endl;
        return false;
    }
    if(Mix_AllocateChannels(4) < 0) {
        cerr << "Unable to allocate mixing channels: %s" << Mix_GetError() << endl;
        return false;
    }

    // set the window size
    this->w = max(WIN_MIN_WIDTH, w);
    this->h = max(WIN_MIN_HEIGHT, h);
    // set the title window
    this->title = title;

    this->resizing = false;

    win = SDL_CreateWindow(
        this->title.c_str(), 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        this->w, 
        this->h, 
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );

    if(win == NULL) {
        cerr << "Fail to initiate the window: " << SDL_GetError() << endl;
        return false; 
    }

    SDL_SetWindowMinimumSize(win, WIN_MIN_WIDTH, WIN_MIN_HEIGHT);

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

    icon = IMG_Load("res/icon.ico");
    if(icon == NULL) {
        cerr << "Failed to load icon: " << IMG_GetError() << endl;
    } else {
        SDL_SetWindowIcon(win, icon);
    }

    running = true;

    cout << "Success to ititiate the subsystem" << endl;

    return true;
}

void Subsystem::handleEvents() {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        switch(e.type) {
            case SDL_QUIT:
                close();
            break;
            case SDL_WINDOWEVENT:
                if(e.window.event == SDL_WINDOWEVENT_RESIZED) {
                    w = e.window.data1;
                    h = e.window.data2;

                    resizing = true;
                } else resizing = false;
            break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                keys.interactKey(e.key.keysym.sym, (e.type == SDL_KEYDOWN));
            break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                mouse.interact(e.button.button, (e.type == SDL_MOUSEBUTTONDOWN));
            break;
        }

        // MouseListener methods
        mouse.move(e.motion.x, e.motion.y);
    }

    keys.update();
    mouse.update();
}

void Subsystem::clean() {
    gfx->clean();
    SDL_FreeSurface(icon);

    // All SDL clean
    SDL_DestroyWindow(win);
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();

    cout << "The subsystem is well clean, bye..." << endl;
}