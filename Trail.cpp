#include <SDL.h>
#include <cmath>
#include <algorithm>

#include "Trail.h"
#include "TrailPoint.h"
#include "Screen.h"

namespace ants
{

    Trail::Trail(Uint32 color, Screen &screen, int gridSize) : color(color), gridSize(gridSize)
    {
        gridWidth = screen.getWidth() / gridSize;
        if (gridWidth * gridSize < screen.getWidth())
        {
            gridWidth++;
        }

        gridHeight = screen.getHeight() / gridSize;
        if (gridWidth * gridSize < screen.getHeight())
        {
            gridHeight++;
        }

        points = new std::list<TrailPoint *>[gridWidth * gridHeight];
    }

    Trail::~Trail()
    {
        for (int i = 0; i < gridWidth * gridHeight; i++)
        {
            auto it = points[i].begin();
            while (points[i].size() > 0)
            {
                delete (*it);
                it = points[i].erase(it);
            }

            delete &points[i];
        }

        delete[] points;
    }

    bool Trail::pointInGrid(int x, int y)
    {
        return x >= 0 && x < gridSize * gridWidth && y >= 0 && y < gridSize * gridHeight;
    }

    int Trail::gridIndex(int x, int y)
    {
        return (y / gridSize) * gridWidth + (x / gridSize);
    }

    TrailPoint *Trail::addTrailPoint(float x, float y, float lifetime)
    {
        if (!pointInGrid(x, y))
        {
            return nullptr;
        }

        TrailPoint *tp = new TrailPoint(x, y, this, lifetime);

        points[gridIndex(x, y)].push_back(tp);

        return tp;
    }

    std::list<TrailPoint *> **Trail::getNeighborhood(int x, int y, int& numNeighbors)
    {
        if (!pointInGrid(x, y))
        {
            return nullptr;
        }

        int l = std::max(x / gridSize - 1, 0);
        int r = std::min(x / gridSize + 1, gridWidth - 1);

        int t = std::max(y / gridSize - 1, 0);
        int b = std::min(y / gridSize + 1, gridHeight - 1);

        numNeighbors = (r - l + 1) * (b - t + 1);
        std::list<TrailPoint *> **neighbors = new std::list<TrailPoint *> *[numNeighbors];

        int ind = 0;
        for (int i = l; i <= r; i++)
        {
            for (int j = t; j <= b; j++)
            {
                neighbors[ind] = (points + j * gridWidth + i);
                ind++;
            }
        }

        return neighbors;
    }

    void Trail::update(Uint32 elapsedMs)
    {
        for (int i = 0; i < gridWidth * gridHeight; i++)
        {
            for (auto it = points[i].begin(); it != points[i].end();)
            {
                if (!(*it)->update(elapsedMs))
                {
                    delete (*it);
                    it = points[i].erase(it);
                }
                else
                {
                    it++;
                }
            }
        }
    }

    bool Trail::render(Screen &screen)
    {
        for (int i = 0; i < gridWidth * gridHeight; i++)
        {
            for (auto it = points[i].begin(); it != points[i].end(); it++)
            {
                (*it)->render(screen);
            }
        }
    }
}