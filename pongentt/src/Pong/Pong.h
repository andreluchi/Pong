#pragma once
#include "Game/Game.h"


const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 700;

class Pong : public Game {
    public:
        Pong();
        ~Pong();

    private:
        std::unique_ptr<Scene> createGameplayScene();
};