#pragma once

#include <memory>
#include <vector>

#include "constantes.hpp"
#include "gfx/texture.hpp"

namespace exocet {
    class Sprite {
        private:
            Texture* texture;

            int nCol, nRow, w, h;
            std::size_t nFrames;

            inline int getSheetX(std::size_t i) { return (i % nCol) * w; }
            inline int getSheetY(std::size_t i) { return (i / nCol) * h; }
        public:
            Sprite(Handler* handler, const std::string& path);
            Sprite(Handler* handler, const std::string& path, int nCol, int nRow, int width, int height, std::size_t nFrames);
            ~Sprite() = default;

            void render(const IntVector2D& position, int width, int height, std::size_t i = 0) {
                texture->render(position, width, height, getSheetX(i), getSheetY(i), w, h);
            }
            void renderAnchor(const IntVector2D& position, int width, int height, std::size_t i = 0) {
                texture->renderAnchor(position, width, height, getSheetX(i), getSheetY(i), w, h);
            }

            void renderAngle(const IntVector2D& position, double angle, int width, int height, std::size_t i = 0) {
                texture->renderAngle(position, angle, width, height, getSheetX(i), getSheetY(i), w, h);
            }
            void renderAnchorAngle(const IntVector2D& position, double angle, int width, int height, std::size_t i = 0) {
                texture->renderAnchorAngle (position, angle, width, height, getSheetX(i), getSheetY(i), w, h);
            }

            inline int getHeight() { return h; }
            inline int getWidth() { return w; }

            inline std::size_t size() const { return nFrames; }
    };
}