#ifndef TRAILPOINT_H
#define TRAILPOINT_H

#include <SDL.h>
#include "Trail.h"
#include "Screen.h"

namespace ants
{
    class Trail;

    class TrailPoint
    {
    private:
        Trail *owner;
        float x, y;
        float lifetime, maxLifetime;

    public:
        TrailPoint(float x, float y, Trail *owner, float lifetime) : x(x), y(y), owner(owner), lifetime(lifetime), maxLifetime(lifetime) {}
        ~TrailPoint();

        bool update(Uint32 elapsedMs);
        bool render(Screen &screen);

        float getX() { return x; }
        float getY() { return y; }
        float getLifetime() { return lifetime; }
        float getMaxLifetime() { return maxLifetime; }
    };
}

#endif