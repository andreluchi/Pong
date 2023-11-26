#include "Game.h"

Game::Game(const char* name, int width, int height)
    : screen_width(width), screen_height(height)
{
    isRunning = true;

    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(name, 0, 0, width, height, 0);
    renderer = SDL_CreateRenderer(window, 0, 0);
    lastFPSUpdate = 0;
    frameStartTimestamp = 0;
    frameEndTimestamp = 0;
    frameCountPerSecond = 0;
    FPS = 0.0;

    int maxFPS = 60;
    frameDuration = (1.0f / maxFPS) * 1000.0f;
}

Game::~Game()
{
    
}

void Game::setup()
{
    
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            setRunning(false);
        };
    }
}

void Game::update()
{
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

bool Game::running()
{
    return isRunning;
}

void Game::setRunning(bool value)
{
    isRunning = value;
}

void Game::frameStart()
{
    frameStartTimestamp = SDL_GetTicks();

    if (frameEndTimestamp)
    {
        deltaTime = (frameStartTimestamp - frameEndTimestamp) / 1000.0f;
    }
    else
    {
        deltaTime = 0.0f;
    }
}

void Game::frameEnd()
{
    frameEndTimestamp = SDL_GetTicks();

    float actualFrameDuration = frameEndTimestamp - frameStartTimestamp;
    if (actualFrameDuration < frameDuration)
    {
        SDL_Delay(static_cast<Uint32>(frameDuration - actualFrameDuration));
    }
    frameCountPerSecond++;
    Uint32 currentTime = SDL_GetTicks();
    Uint32 timeElapsed = currentTime - lastFPSUpdate;

    if (timeElapsed >= 1000)
    {
        FPS = static_cast<double>(frameCountPerSecond) / (timeElapsed / 1000.0);
        lastFPSUpdate = currentTime;
        frameCountPerSecond = 0;
    }
}
