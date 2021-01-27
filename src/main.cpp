// In current thas this is compiled for little endian
#include <iostream>

#include "globals.h"
#include "maze.h"

#include <SDL2/SDL.h>
#include <vector>

SDL_Window* g_Window = nullptr;
SDL_Renderer* g_Renderer = nullptr;

bool init();
void close();

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "Failed to initialize SDL2: " << SDL_GetError() << std::endl;
        return false;
    }
    if (SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1") == SDL_FALSE)
    {
        std::cerr << "Failed to set texture filtering to linear: " << SDL_GetError() << std::endl;
    }

    g_Window = SDL_CreateWindow("Maze-generator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WH, WH, SDL_WINDOW_SHOWN);
    if (g_Window == nullptr)
    {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }
    g_Renderer = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (g_Renderer == nullptr)
    {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void close()
{
    if (g_Renderer != nullptr)
    {
        SDL_DestroyRenderer(g_Renderer);
        g_Renderer = nullptr;
    }
    if (g_Window != nullptr)
    {
        SDL_DestroyWindow(g_Window);
        g_Window = nullptr;
    }

    SDL_Quit();  
}

int main(int argc, char* args[])
{
    if (!init())
    {
        close();
        return 1;
    }

    bool quit = false;
    SDL_Event event;
    SDL_Texture* maze =  createMaze();
    while (!quit)
    {
        // Get input
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    quit = true;
                }
            }
        }
        // Render
        SDL_SetRenderDrawColor(g_Renderer, 0, 0, 0, 255);
        SDL_RenderClear(g_Renderer);
        SDL_RenderCopy(g_Renderer, maze, NULL, NULL);
        SDL_RenderPresent(g_Renderer);
    }
    destroyMaze(maze);
    return 0;
}
