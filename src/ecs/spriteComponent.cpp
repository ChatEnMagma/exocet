#include "ecs/spriteComponent.hpp"

#include "handler.hpp"

using namespace exocet;
using namespace std;

void SpriteComponent::init() {
    if(!entity->hasComponent<TransformComponent>())
        transform = &entity->addComponent<TransformComponent>();
    else
        transform = &entity->getComponent<TransformComponent>();

    fps = FPS;
    frame = 0;
    frameStart = SDL_GetTicks();
    
    a = 0;

    setSize(32, 32);
}

void SpriteComponent::update() {
    if(1000/fps < SDL_GetTicks() - frameStart ) {
        if(frame >= getFrame() - 1)
            frame = 0;
        else
            frame++;
        frameStart = SDL_GetTicks();
    }
}

void SpriteComponent::render() {
    if(!tex.empty())
        tex[frame]->renderAngle(transform->getPosition(), w, h, a);
}

void SpriteComponent::fitSizeWithHitbox() {
    if(entity->hasComponent<HitboxComponent>()) {
        HitboxComponent& hitbox = entity->getComponent<HitboxComponent>();
        setSize(hitbox.getWidth(), hitbox.getHeight());
    }
}

void SpriteComponent::initFrameFromSheet(std::string path, int nTextures, int xrow, int ycol, int width, int height) {
    std::vector<Texture*> tex(nTextures);

    if(nTextures > 1) {
        int xpos = 0;
        int ypos = 0;

        for(int i = 0; i < nTextures; i++) {
            tex[i] = new Texture(handler, path, xpos * width, ypos * height, width, height);
            xpos = (xpos + 1) % xrow;
            ypos += int (xpos == 0);
        }
    } else
        tex[0] = new Texture(handler, path);
    setTextures(tex);
}