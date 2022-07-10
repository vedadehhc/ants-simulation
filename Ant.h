#ifndef ANT_H
#define ANT_H

#include <algorithm>
#include <cmath>

#include "Screen.h"
#include "ants.h"
#include "Trail.h"

namespace ants
{
    class Ant
    {
    public:
        const static float HEAD_SIZE, BODY_SIZE, SPEED, TURNINESS, HOME_RADIUS, RANGE, TRAIL_STRENGTH;
        const static Uint32 COLOR;

    private:
        float x, y;
        float homeX, homeY;
        float direction;
        bool carryingFood;

        Trail *exploreTrail;
        Trail *returnTrail;

    public:
        void setDirection(float newDir)
        {
            direction = fmod(newDir, 2 * M_PI);
        }

    public:
        Ant() : x(0), y(0) {}
        Ant(float x, float y, Trail *exploreTrail, Trail *returnTrail) : x(x), y(y), exploreTrail(exploreTrail), returnTrail(returnTrail)
        {
            homeX = x;
            homeY = y;
            direction = randFloat() * 2 * M_PI;
            carryingFood = false;
        }

        void move(Uint32 elapsedMs, float screenWidth, float screenHeight);

        // Renders the ant to the screen.
        // Returns true if the ant is visible on the screen.
        // TODO: update render to display partial wrapping
        bool render(Screen &screen);
    };
}

#endif