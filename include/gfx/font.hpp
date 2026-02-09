#pragma once

#include <iostream>
#include <string>

#include <constantes.hpp>

namespace exocet {
    class Font {
        private:
            TTF_Font* font;
            int fontSize;
        public:
            Font(const std::string& path, int fontSize) {
                this->fontSize = fontSize;

                if((font = TTF_OpenFont(path.c_str(), fontSize)) == NULL)
                    std::cerr << "Failed to load the font from `" << path << "`: " << TTF_GetError() << std::endl;
                else
                    std::cout << "Success to load the font from " << path << "`..." << std::endl;
            }
            ~Font() { TTF_CloseFont(font); }
            
            int getFontSize() const { return fontSize; }
            TTF_Font* get() { return font; }
    };
}