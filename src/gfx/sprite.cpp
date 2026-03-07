#include "gfx/sprite.hpp"
#include "handler.hpp"

using namespace std;
using namespace exocet;

Sprite::Sprite(Handler* handler, const string& path) {
    this->texture = handler->getGraphic()->getTexture(path);

    this->nCol = 1;
    this->nRow = 1;

    this->x = 0;
    this->y = 0;

    this->w = this->texture->getWidth();
    this->h = this->texture->getHeight();

    this->nFrames = 1;
}

Sprite::Sprite(Handler* handler, const string& path, int nCol, int nRow, int w, int h, size_t nFrames) {
    if(nCol <= 0 || nRow <= 0 || w <= 0 || h <= 0 || nFrames == 0)
        throw invalid_argument("Bad format source sprite");

    this->texture = handler->getGraphic()->getTexture(path);

    this->nCol = nCol;
    this->nRow = nRow;

    this->x = 0;
    this->y = 0;

    this->w = w;
    this->h = h;

    this->nFrames = nFrames;
}

Sprite::Sprite(Handler* handler, const std::string& path, int xPos, int yPos, int w, int h) {
    if(yPos < 0 || xPos < 0 || w <= 0 || h <= 0)
        throw invalid_argument("Bad format source sprite");
 
    this->texture = handler->getGraphic()->getTexture(path);

    this->nCol = 1;
    this->nRow = 1;

    this->x = xPos * w;
    this->y = yPos * h;

    this->h = h;
    this->w = w;

    this->nFrames = 1;
}