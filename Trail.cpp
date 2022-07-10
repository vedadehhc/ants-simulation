#include <SDL.h>
#include <cmath>
#include <algorithm>

#include "Trail.h"
#include "TrailPoint.h"
#include "Screen.h"
#include "ants.h"

namespace ants
{

    Trail::Trail(Uint32 color, Screen &screen, int gridSize) : color(color), gridSize(gridSize), torus(0, 0, screen.getWidth(), screen.getHeight())
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

    bool Trail::pointInGrid(float x, float y)
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

    std::list<TrailPoint *> **Trail::getNeighborhood(float x, float y, float radius, int &numNeighbors)
    {
        if (!pointInGrid(x, y))
        {
            return nullptr;
        }

        int l = (int)floor((x - radius) / gridSize);
        int r = (int)ceil((x + radius) / gridSize);

        int t = (int)floor((y - radius) / gridSize);
        int b = (int)ceil((y + radius) / gridSize);

        numNeighbors = (r - l + 1) * (b - t + 1);
        if (numNeighbors == 0)
        {
            return nullptr;
        }

        std::list<TrailPoint *> **neighbors = new std::list<TrailPoint *> *[numNeighbors];

        int ind = 0;
        for (int i = l; i <= r; i++)
        {
            for (int j = t; j <= b; j++)
            {
                neighbors[ind] = (points + uMod(j, gridHeight) * gridWidth + uMod(i, gridWidth));
                ind++;
            }
        }

        return neighbors;
    }

    float Trail::getStrength(float x, float y, float radius)
    {
        int numNeighbors;
        std::list<TrailPoint *> **neighbors = getNeighborhood(x, y, radius, numNeighbors);

        if (neighbors == nullptr || numNeighbors == 0)
        {
            return 0;
        }

        float total = 0;
        for (int i = 0; i < numNeighbors; i++)
        {
            for (auto it = neighbors[i]->begin(); it != neighbors[i]->end(); it++)
            {
                if (pointInCircleTorus((*it)->getX(), (*it)->getY(), x, y, radius, torus))
                {
                    total += (*it)->getLifetime() / (*it)->getMaxLifetime();
                }
            }
        }

        delete[] neighbors;
        
        return total;
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