#pragma once

#include <memory>
#include <vector>

#include "constantes.hpp"
#include "gfx/texture.hpp"

namespace exocet {
    class Sprite {
        private:
            Texture* texture;

            int nCol, nRow, x, y, w, h;
            std::size_t nFrames;

            inline int getSheetX(std::size_t i) noexcept { return (i % nCol) * w; }
            inline int getSheetY(std::size_t i) noexcept { return (i / nCol) * h; }
        public:
            Sprite(Texture* texture);
            Sprite(Texture* texture, int nCol, int nRow, int width, int height, std::size_t nFrames);
            Sprite(Texture* texture, int xPos, int yPos, int width, int height);
            ~Sprite() noexcept = default;

            void render(const EngineVector2D& position, int width, int height, std::size_t i = 0) {
                if(i > size()) throw std::runtime_error("overflow");
                texture->render(position, width, height, x + getSheetX(i), y + getSheetY(i), w, h);
            }
            void renderAnchor(const EngineVector2D& position, int width, int height, std::size_t i = 0) {
                if(i > size()) throw std::runtime_error("overflow");
                texture->renderAnchor(position, width, height, x + getSheetX(i), y + getSheetY(i), w, h);
            }

            void renderAngle(const EngineVector2D& position, double angle, int width, int height, std::size_t i = 0) {
                if(i > size()) throw std::runtime_error("overflow");
                texture->renderAngle(position, angle, width, height, x + getSheetX(i), y + getSheetY(i), w, h);
            }
            void renderAnchorAngle(const EngineVector2D& position, double angle, int width, int height, std::size_t i = 0) {
                if(i > size()) throw std::runtime_error("overflow");
                texture->renderAnchorAngle (position, angle, width, height, x + getSheetX(i), y + getSheetY(i), w, h);
            }

            inline int getHeight() noexcept { return h; }
            inline int getWidth() noexcept { return w; }

            inline std::size_t size() const noexcept { return nFrames; }
    };
}