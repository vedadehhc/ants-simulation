#ifndef TRAIL_H
#define TRAIL_H

#include <list>

#include "TrailPoint.h"
#include "Screen.h"
#include "ants.h"

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
        Box torus;

    public:
        Trail(Uint32 color, Screen& screen, int gridSize);
        ~Trail();

        Uint32 getColor() { return color; }

        bool pointInGrid(float x, float y);
        int gridIndex(int x, int y);

        TrailPoint *addTrailPoint(float x, float y, float lifetime);
        std::list<TrailPoint *>** getNeighborhood(float x, float y, float radius, int& numNeighbors);
        float getStrength(float x, float y, float radius);

        void update(Uint32 elapsedMs);
        bool render(Screen &screen);
    };
}

#endif