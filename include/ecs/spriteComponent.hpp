#pragma once

#include "gfx/texture.hpp"
#include "ecs/transformComponent.hpp"

namespace exocet {
    class SpriteComponent: public Component {
        private:
            std::vector<Texture*> tex;
            std::size_t frame;
            Uint32 fps;
            Uint32 frameStart, frameTime;

            TransformComponent* transform;
            double a;
            int w, h;

            inline void cleanTextures() { for(Texture* t: tex) {
                if(t != nullptr)
                    t->clean();
            } tex.clear(); }
        public:
            ~SpriteComponent() { cleanTextures(); }

            void init() override;
            void update() override;
            void render() override;

            void fitSizeWithHitbox();
            void initFrameFromSheet(std::string path, int nTextures = 1, int xrow = 0, int ycol = 0, int width = -1, int height = -1);
            inline std::size_t getFrame() const { return tex.size(); }
            inline std::size_t getCurrentFrame() const { return frame; }
            inline Uint32 getFPS() const { return fps; }

            inline double getAngle() const { return a; }
            inline int getWidth() const { return w; }
            inline int getHeight() const { return h; }
            
            inline void setAngle(const double angle) { a = angle; }
            inline void setSize(int width, int height) { w = width; h = height; }
            inline void setFPS(const Uint32 fps) { this->fps = fps; }
            inline void setTexture(const std::string path, int xpos, int ypos, int width, int height, std::size_t frame) {
                tex[frame]->clean();
                if((width == 0) || (height == 0)) tex[frame] = new Texture(handler, path);
                else tex[frame] = new Texture(handler, path, xpos, ypos, width, height);
            }
            inline void setTextures(std::vector<Texture*> textures) { cleanTextures(); frame = 0; tex = textures; }
    };
}