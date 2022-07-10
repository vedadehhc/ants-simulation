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
        std::list<TrailPoint *> points;
        Uint32 color;

    public:
        Trail(Uint32 color) : color(color) {}
        ~Trail();

        Uint32 getColor() { return color; }

        TrailPoint *addTrailPoint(float x, float y, float lifetime);
        std::list<TrailPoint *>::iterator getBeginIter();
        std::list<TrailPoint *>::iterator getEndIter();
        void deleteAll();

        void update(Uint32 elapsedMs);
        bool render(Screen &screen);
    };
}

#endif