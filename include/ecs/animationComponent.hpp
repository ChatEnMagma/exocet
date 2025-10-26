#pragma once

#include "gfx/texture.hpp"
#include "ecs/transformComponent.hpp"

namespace exocet {
    class AnimationComponent: public Component {
        private:
            std::vector<Texture*> tex;
            std::size_t frame;
            Uint32 fps;

            TransformComponent* transform;
            int w, h;

            inline void cleanTextures() { for(Texture* t: tex) t->clean(); tex.clear(); }
        public:
            ~AnimationComponent() { cleanTextures(); }

            void init() override;
            void update() override;
            void render() override;

            void fitSizeWithHitbox();

            inline std::size_t getFrame() const { return tex.size(); }
            inline std::size_t getCurrentFrame() const { return frame; }
            inline Uint32 getFPS() const { return fps; }
            
            inline void setSize(int width, int height) { w = width; h = height; }
            inline void setFPS(const Uint32 fps) { this->fps = fps; }
            inline void setTextures(std::vector<Texture*> textures) { cleanTextures(); tex = textures; }
    };
}