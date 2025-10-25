#include "state/background.hpp"
#include "handler.hpp"

using namespace exocet;
using namespace std;

void Background::update() {

}

void Background::render() {
    for(Texture* t : tex) {
        if(!loop)
            t->render(position, w, h);
        else {
            t->render(position, w, h);

            if(handler->getGraphic()->getCamera()->getPosition().x <= position.x) {
                t->render(position - Vector2D<int>(w, 0), w, h);
            }
            if(handler->getGraphic()->getCamera()->getPosition().x + handler->getWinWidth() >= position.x) {
                t->render(position + Vector2D<int>(w, 0), w, h);
            }

            if(position.x <= -w)
                position.x = 0;
        }
    }
}

void Background::refresh() {
    for(Texture* t : tex)
        t->clean();
    tex.clear();
    setSize(0, 0);
}