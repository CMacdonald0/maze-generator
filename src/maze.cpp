#include "maze.h"
#include "globals.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <stdlib.h>
#include <time.h>



// Create grid of squares
void createGrid(SDL_Surface* s)
{
    std::vector<SDL_Rect> walls;
    // std::cout << "Columns: \n";
    for (int x = 0, y = 0; x <= WH; x+=17)
    {
        SDL_Rect r = {x, y, 3, WH};
        walls.push_back(r);
        // std::cout << x << ", ";
    }

    // std::cout << "\nRows: \n";
    for (int x = 0, y = 0; y <= WH; y+=17)
    {
        SDL_Rect r = {x, y, WH, 3};
        walls.push_back(r);
        // std::cout << y << ", ";
    }
    SDL_FillRects(s, walls.data(), walls.size(), SDL_MapRGB(s->format, 255, 255, 255));
}

SDL_Texture* createMaze()
{
    // Initialize random seed
    srand(time(nullptr));

    SDL_Surface* s = SDL_CreateRGBSurfaceWithFormat(0, WH, WH, 24, SDL_PIXELFORMAT_RGB24);
    if (s == nullptr)
    {
        std::cerr << "Failed to create surface: " << SDL_GetError() << std::endl;
        return nullptr;
    }
    createGrid(s);

    SDL_Texture* maze = SDL_CreateTextureFromSurface(g_Renderer, s);
    if (maze == nullptr)
    {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_FreeSurface(s);
    return maze;
}

void destroyMaze(SDL_Texture* m)
{
    if (m != nullptr)
    {
        SDL_DestroyTexture(m);
    }
}

