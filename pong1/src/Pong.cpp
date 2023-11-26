#include "Pong.h"
#include "Game.h"
#include "print.h"

Pong::Pong(const char* name, int width, int height)
    : Game(name, width, height)
{
    isGameOver = false;
    gameOverRect = { width / 2 - 100, height / 2 - 25, 200,  100 };
    lastFPSUpdate = 0;
    frameStartTimestamp = 0;
    frameEndTimestamp = 0;
    frameCountPerSecond = 0;
    FPS = 0.0;

    int maxFPS = 60;
    frameDuration = 1000.0f / maxFPS;

}

Pong::~Pong()
{
    
}

void Pong::setup()
{
    ball.x = (screen_width / 2 );
    ball.y = (screen_height / 2 );
    ball.w = 15;
    ball.h = 15;
    paddle1.x = 20;
    paddle1.y = (screen_height / 2) - 50;
    paddle1.w = 20;
    paddle1.h = 100;

    paddle2.x = screen_width - 20;
    paddle2.y = (screen_height / 2) - 50;
    paddle2.w = 20;
    paddle2.h = 100;
    ball_speed_x = 2;
    ball_speed_y = 2;
    ball_speed_multiplier = 2;
}

void Pong::update()
{
    if (!isGameOver)
    {
        ball.x += ball_speed_x;
        ball.y += ball_speed_y;

    }
    if (ball.y + ball.h >= screen_height || ball.y <= 0)
    {
        ball_speed_y *= -1.1;
    }

    if (ball.y + ball.h >= paddle1.y && ball.x + ball.w >= paddle1.x && ball.x <= paddle1.x + paddle1.w)
    {
        ball_speed_x *= -1.1;
    }
    else if (ball.y <= paddle2.y + paddle2.h && ball.x + ball.w >= paddle2.x && ball.x <= paddle2.x + paddle2.w)
    {
        ball_speed_x *= -1.1;
    }

    else if ((ball.x + ball.w < 0 || ball.x > screen_width) && !isGameOver)
    {
        isGameOver = true;
        if (ball.x + ball.w < 0)
        {
            print("Player 2 Wins (Derecha)");
        }
        else
        {
            print("Player 1 Wins (Izquierda)");
        }
        setRunning(false);
        SDL_Quit();
    }
}

void Pong::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 2, 55, 25);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &ball);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &paddle1);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &paddle2);
    SDL_RenderPresent(renderer);
}

void Pong::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            setRunning(false);
        }
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_w:
                paddle1.y -= 30;
                break;
            case SDLK_s:
                paddle1.y += 30;
                break;
            case SDLK_UP:
                paddle2.y -= 30;
                break;
            case SDLK_DOWN:
                paddle2.y += 30;
                break;
            }
        }
        
    }
    if (ball.y + ball.h >= paddle1.y && ball.x + ball.w >= paddle1.x && ball.x <= paddle1.x + paddle1.w)
    {
        ball_speed_y *= -1;
    }

    if (ball.y <= paddle2.y + paddle2.h && ball.x + ball.w >= paddle2.x && ball.x <= paddle2.x + paddle2.w)
    {
        ball_speed_y *= -1;
    }

}

void Pong::frameStart()
{
    frameStartTimestamp = SDL_GetTicks();

    if(frameEndTimestamp)
    {
        deltaTime = (frameStartTimestamp - frameEndTimestamp) / 1000.0f;
    }
    else
    {
        deltaTime = 0.0f;
    }
}

void Pong::frameEnd()
{
    // Get the current time at the end of the frame
    frameEndTimestamp = SDL_GetTicks();

    // Calculate the actual duration of this frame
    float actualFrameDuration = frameEndTimestamp - frameStartTimestamp;

    // Delay to achieve the target frame rate
    if (actualFrameDuration < frameDuration)
    {
        // Calculate the remaining time to sleep
        Uint32 remainingTime = static_cast<Uint32>(frameDuration - actualFrameDuration);
        
        // Sleep the remaining time to cap the FPS
        SDL_Delay(remainingTime);
    }

    // FPS calculation
    frameCountPerSecond++;
    Uint32 currentTime = SDL_GetTicks();
    Uint32 timeElapsed = currentTime - lastFPSUpdate;

    if (timeElapsed >= 1000)
    {
        FPS = static_cast<double>(frameCountPerSecond) / (timeElapsed / 1000.0);
        lastFPSUpdate = currentTime;
        frameCountPerSecond = 0;

        print("FPS: " + std::to_string(FPS));
    }
}