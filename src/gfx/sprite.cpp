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
    if(nCol <= 0 || nRow <= 0 || w <= 0 || h <= 0 || nFrames == 0)
        throw invalid_argument("Bad format source sprite");

    this->texture = handler->getGraphic()->getTexture(path);

    this->nCol = nCol;
    this->nRow = nRow;
    this->h = h;
    this->w = w;

    this->nFrames = nFrames;
}