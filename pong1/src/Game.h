#pragma once
#include <SDL2/SDL.h>
#include <string>

class Game
{
public:
    Game(const char* name, int width, int height); 
    virtual ~Game(); 

    virtual void setup();
    virtual void handleEvents();
    virtual void update();
    virtual void render();
    bool running();
    void setRunning(bool value);

    void frameStart();
    void frameEnd();

protected:
    int width;
    int height;

    SDL_Window* window;
    SDL_Renderer* renderer;

    int screen_width;
    int screen_height;

    double FPS;
    int frameCountPerSecond;
    Uint32 frameStartTimestamp;
    Uint32 frameEndTimestamp;
    Uint32 lastFPSUpdate;
    float frameDuration;
    float deltaTime; 

    bool isRunning;
};
