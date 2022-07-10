#ifndef TRAIL_H
#define TRAIL_H

#include <list>

#include "TrailPoint.h"
#include "Screen.h"

namespace ants
{
    class TrailPoint;

    // TODO: optimize using buckets on grid to make search faster
    class Trail
    {
    private:
        int gridWidth, gridHeight, gridSize;
        std::list<TrailPoint *> *points;
        Uint32 color;

    public:
        Trail(Uint32 color, Screen& screen, int gridSize);
        ~Trail();

        Uint32 getColor() { return color; }

        bool pointInGrid(int x, int y);
        int gridIndex(int x, int y);

        TrailPoint *addTrailPoint(float x, float y, float lifetime);
        std::list<TrailPoint *>** getNeighborhood(int x, int y, int& numNeighbors);

        void update(Uint32 elapsedMs);
        bool render(Screen &screen);
    };
}

#endif