#pragma once

#include <iostream>
#include <string>

#include "constantes.hpp"
#include "tool/vectors.hpp"

namespace exocet {
    class Texture {
        private:
            Handler* handler;

            SDL_Texture* tex = NULL;

            int w, h;

            void openTexture(const std::string& path);
        public:
            Texture(Handler* handler, const std::string& path);
            ~Texture() { SDL_DestroyTexture(tex); }

            /**
             * \brief Render the texture
             */
            void render(const IntVector2D& position, int wdest, int hdest, int xsrc, int ysrc, int wsrc, int hsrc);
            void renderAnchor(const IntVector2D& position, int wdest, int hdest, int xsrc, int ysrc, int wsrc, int hsrc);
            void renderAnchorAngle(const IntVector2D& position, double angle, int wdest, int hdest, int xsrc, int ysrc, int wsrc, int hsrc);
            void renderAngle(const IntVector2D&, double angle, int wdest, int hdest, int xsrc, int ysrc, int wsrc, int hsrc);

            inline int getHeight() const { return h; }
            inline int getWidth() const { return w; }
    };
}