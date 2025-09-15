#include "state/debugState.hpp"

#include "handler.hpp"

using namespace std;
using namespace exocet;

void DebugState::init() {
    auto& player = eManager->addEntity("player");
    auto& player_player = player.addComponent<PlayerComponent>();
    player_player.setPointsPosition(10, 100);

    auto& wall = eManager->addEntity("wall");
    auto& wall_physic = wall.addComponent<PhysicComponent>();
    wall_physic.setPointsPosition(64, 400);
    wall.getComponent<HitboxComponent>().setSize(handler->getWinWidth(), 64);
    wall_physic.setMasse(500.f);

    auto& ball = eManager->addEntity("ball");
    auto& ball_physic = ball.addComponent<PhysicComponent>();
    ball_physic.setPointsPosition(100, 100);
    ball.getComponent<HitboxComponent>().setColor(0x00, 0xff, 0xff);
    ball_physic.setMasse(1.f);

    auto& wall2 = eManager->addEntity("wall2");
    auto& wall2_physic = wall2.addComponent<PhysicComponent>();
    wall2_physic.setPointsPosition(-64, 0);
    wall2.getComponent<HitboxComponent>().setSize(64, handler->getWinHeight());
    wall2_physic.setMasse(500.f);
}

void DebugState::update() {
    eManager->update();
}

void DebugState::render() {
    eManager->render();
}