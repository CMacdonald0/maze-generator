#ifndef _MAZE_GEN_H
#define _MAZE_GEN_H

#include "globals.h"

#include <SDL2/SDL.h>
#include <utility>
#include <vector>
#include <map>

typedef std::map<std::pair<int, int>, bool>::iterator m_CellsIter;

// Needs to be a odd number as well as a factor of 780
const int g_CR = 12;

enum DIRECTIONS {LEFT, RIGHT, UP, DOWN, LAST};

class Maze
{
    private:
        SDL_Surface* m_S;
        SDL_Texture* m_T;
        std::map<std::pair<int, int>, bool> m_Cells;
        inline std::vector<int> checkNeighbours(const int x, const int y);
        inline void removeWall(int d, int& x, int& y);

    public:
        Maze();
        ~Maze();
        SDL_Texture* getTexture() const;
        void updateTexture();
        void createGrid();
        void createCells();
        void dfsMazeGen(int x, int y);

};

#endif