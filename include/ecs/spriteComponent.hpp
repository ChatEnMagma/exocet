#pragma once

#include "transformComponent.hpp"
#include "gfx/texture.hpp"

namespace exocet {
    class SpriteComponent: public Component {
        private:
            TransformComponent* transform;
            Texture* tex;

            int w, h;
        public:
            ~SpriteComponent();
            
            void init() override;
            void render() override;

            inline void setTexture(std::string path) { 
                if(tex != nullptr)
                    tex->clean();

                tex = new Texture(handler, path); 

                setSize(tex->getWidth(), tex->getHeight());
            }

            inline void setSize(int width, int height) { w = width; h = height; }
            void fitSizeWithHitbox();
    };
}