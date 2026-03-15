#include "state/background.hpp"
#include "handler.hpp"

using namespace exocet;
using namespace std;

void Background::update() noexcept {

}

void Background::render() noexcept {
    for(auto s : sprites) {
        if(!loop)
            s->render(position, w, h);
        else {
            s->render(position, w, h);

            if(handler.getGraphic().getCamera().getPosition().x <= position.x) {
                s->render(position - EngineVector2D(w, 0), w, h);
            }
            if(handler.getGraphic().getCamera().getPosition().x + handler.getWinWidth() >= position.x) {
                s->render(position + EngineVector2D(w, 0), w, h);
            }

            if(position.x <= -w)
                position.x = 0;
        }
    }
}

void Background::refresh() {
    sprites.clear();
    setSize(0, 0);
}