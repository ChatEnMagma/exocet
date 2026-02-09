#include "gfx/sprite.hpp"
#include "handler.hpp"

using namespace std;
using namespace exocet;

Sprite::Sprite(Handler* handler, const string& path) {
    this->texture = handler->getGraphic()->getTexture(path);

    this->nCol = 1;
    this->nRow = 1;
    this->h = this->texture->getHeight();
    this->w = this->texture->getWidth();

    this->nFrames = 1;
}

Sprite::Sprite(Handler* handler, const string& path, int nCol, int nRow, int w, int h, size_t nFrames) {
    this->texture = handler->getGraphic()->getTexture(path);

    this->nCol = nCol;
    this->nRow = nRow;
    this->h = h;
    this->w = w;

    this->nFrames = nFrames;
}