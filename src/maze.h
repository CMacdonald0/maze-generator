#ifndef _MAZE_GEN_H
#define _MAZE_GEN_H

#include "globals.h"

#include <SDL2/SDL.h>
#include <utility>
#include <vector>
#include <map>

// Boarders around the grid squares are 3 pixel width or height and the squares are 8*8

enum DIRECTIONS {LEFT, RIGHT, UP, DOWN};

void createGrid(SDL_Surface* s);
void createCells(std::map<std::pair<int, int>, bool>& grid);
SDL_Texture* createMaze();
void destroyMaze(SDL_Texture* m);



#endif