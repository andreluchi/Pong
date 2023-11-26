#include <string>
#include <SDL2/SDL.h>
#include "Pong.h"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return -1;
    }
    Pong pongGame("Pong", 700, 600);
    pongGame.setup();
    while (pongGame.running()) {
        pongGame.frameStart();
        pongGame.handleEvents();
        pongGame.update();
        pongGame.render();
        pongGame.frameEnd();
    }
    SDL_Quit();
    return 0;
}
