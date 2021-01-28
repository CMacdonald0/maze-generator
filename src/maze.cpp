#include "maze.h"
#include "globals.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <stdlib.h>
#include <time.h>

const int g_CellCenterSize = 14;
const int g_wallThickness = 3;
const int g_CenterAndWall = g_CellCenterSize + g_wallThickness;

// Create grid of squares
void createGrid(SDL_Surface* s)
{
    std::vector<SDL_Rect> walls;
    // Columns
    for (int x = 0, y = 0; x <= WH; x+=17)
    {
        SDL_Rect r = {x, y, 3, WH};
        walls.push_back(r);
    }
    // Rows
    for (int x = 0, y = 0; y <= WH; y+=17)
    {
        SDL_Rect r = {x, y, WH, 3};
        walls.push_back(r);
    }
    // add Entrance and exit
    std::vector<SDL_Rect> doors;
    doors.push_back(SDL_Rect{3, 0, 14, 3});
    doors.push_back(SDL_Rect{WH - 17, WH - 3, 17, 3});
    SDL_FillRects(s, walls.data(), walls.size(), SDL_MapRGB(s->format, 255, 255, 255));
    SDL_FillRects(s, doors.data(), doors.size(), SDL_MapRGB(s->format, 0, 0, 0));
}

// Create map for all grid squares, each is represented by an x, y coordinate that is its top left corner,
void createCells(std::map<std::pair<int, int>, bool>& grid)
{
    for (int x = 3, y = 3; x <= WH; x+=17)
    {
        for (;y <= WH; y+=17)
        {
            grid[std::make_pair(x, y)] = false;
        }
        y = 3;
    }
}

// Get the neighbour of the direction and coordinates passed in
void getNeighbour(int d, int& x, int& y, SDL_Surface* s)
{
    if (d == LEFT)
    {
        x -= 17;
        SDL_Rect temp = {x, y, 17, 14};
        SDL_FillRect(s, &temp, SDL_MapRGB(s->format, 0, 0, 0));
    }
    else if (d == RIGHT)
    {
        SDL_Rect temp = {x, y, 17, 14};
        SDL_FillRect(s, &temp, SDL_MapRGB(s->format, 0, 0, 0));
        x += 17;
    }
    else if (d == UP)
    {
        y -= 17;
        SDL_Rect temp = {x, y, 14, 17};
        SDL_FillRect(s, &temp, SDL_MapRGB(s->format, 0, 0, 0));
    }
    // Move down
    else
    {
        SDL_Rect temp = {x, y, 14, 17};
        SDL_FillRect(s, &temp, SDL_MapRGB(s->format, 0, 0, 0));
        y += 17;
    }
}

// Check neighbours of a cell if they have been visited, add all unvisited cells to a vector
std::vector<int> checkNeighbours(const int x, const int y, std::map<std::pair<int, int>, bool>& cells)
{
    std::vector<int> n;
    if (cells.find(std::make_pair(x - 17, y)) != cells.end() && cells[std::make_pair(x - 17, y)] == false)
        n.push_back(LEFT);
    if (cells.find(std::make_pair(x + 17, y)) != cells.end() && cells[std::make_pair(x + 17, y)] == false)
        n.push_back(RIGHT);
    if (cells.find(std::make_pair(x, y - 17)) != cells.end() && cells[std::make_pair(x, y - 17)] == false)
        n.push_back(UP);
    if (cells.find(std::make_pair(x, y + 17)) != cells.end() && cells[std::make_pair(x, y + 17)] == false)
        n.push_back(DOWN);

    return n;
}

void dfsMazeGen(SDL_Surface* s, int x, int y, std::map<std::pair<int, int>, bool>& visited)
{
    // Mark the current cell as visited 
    visited[std::make_pair(x, y)] = true;

    std::vector<int> n = checkNeighbours(x, y, visited);
    // While the cell has at least one unvisited neighbour continue, a dead end is formed when a cell has no unvisited neighbours
    while (!n.empty())
    {
        // Go to a random neighbour
        int dir = rand() % n.size();
        getNeighbour(n.at(dir), x, y, s);
        dfsMazeGen(s, x, y, visited);
        n = checkNeighbours(x, y, visited);
    }
}

Maze createMaze()
{
    // Initialize random seed
    srand(time(nullptr));

    SDL_Surface* s = SDL_CreateRGBSurfaceWithFormat(0, WH, WH, 24, SDL_PIXELFORMAT_RGB24);
    if (s == nullptr)
    {
        std::cerr << "Failed to create surface: " << SDL_GetError() << std::endl;
        return {nullptr, nullptr};
    }
    createGrid(s);
    std::map<std::pair<int, int>, bool> cells;
    createCells(cells);

    dfsMazeGen(s, 428, 207, cells);
    SDL_Texture* t = SDL_CreateTextureFromSurface(g_Renderer, s);
    if (t == nullptr)
    {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        return {nullptr, nullptr};
    }

    return {s, t};

}

void destroyMaze(Maze m)
{
    if (m.t != nullptr)
    {
        SDL_DestroyTexture(m.t);
    }
    if (m.s != nullptr)
    {
        SDL_FreeSurface(m.s);
    }
}
