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
                    throw std::runtime_error("Failed to load the font from `" + path + "`: " + std::string(TTF_GetError()));
                
                std::cout << "Success to load the font from " << path << "`..." << std::endl;
            }
            ~Font() noexcept { TTF_CloseFont(font); }
            
            int getFontSize() const noexcept { return fontSize; }
            TTF_Font* get() noexcept { return font; }
    };
}