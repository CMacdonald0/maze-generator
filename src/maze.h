#ifndef _MAZE_GEN_H
#define _MAZE_GEN_H

#include "globals.h"

#include <SDL2/SDL.h>
#include <utility>
#include <vector>
#include <map>

typedef std::map<std::pair<int, int>, std::pair<int, int>> ParentMap;
typedef std::map<std::pair<int, int>, bool>::iterator CellsIter;

const int g_CR = 12;

enum DIRECTIONS {LEFT, RIGHT, UP, DOWN, LAST};

class Maze
{
    private:
        SDL_Surface* m_S;
        SDL_Texture* m_T;
        const int m_StartX;
        const int m_StartY;
        const int m_EndX;
        const int m_EndY;
        std::map<std::pair<int, int>, bool> m_Cells;
        ParentMap m_Parent;
        
        inline std::vector<int> checkNeighbours(const int x, const int y, bool visitedStatus);
        inline void removeWall(int d, int& x, int& y);
        inline void moveToNeighbour(int d, int& x, int& y);
        void drawPath();

    public:
        Maze();
        Maze operator=(const Maze& m);
        ~Maze();
        SDL_Texture* getTexture() const;
        void updateTexture();
        void createGrid();
        void createCells();
        void dfsMazeGen(int x, int y);
        void dfsMazeExplore(int x, int y);
        void explore();
};

#endif