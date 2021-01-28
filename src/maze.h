#ifndef _MAZE_GEN_H
#define _MAZE_GEN_H

#include "globals.h"

#include <SDL2/SDL.h>
#include <utility>
#include <vector>
#include <map>

struct Maze
{
    SDL_Surface* s;
    SDL_Texture* t;
};

// Boarders around the grid squares are 3 pixel width or height and the squares are 8*8
enum DIRECTIONS {LEFT, RIGHT, UP, DOWN};

void createGrid(SDL_Surface* s);
void createCells(std::map<std::pair<int, int>, bool>& grid);
void getNeighbour(int d, int& x, int& y, SDL_Surface* s);
std::vector<int> checkNeighbours(const int x, const int y, std::map<std::pair<int, int>, bool>& cells);
void dfsMazeGen(SDL_Surface* s, int x, int y, std::map<std::pair<int, int>, bool>& visited);
Maze createMaze();

void destroyMaze(Maze m);

#endif