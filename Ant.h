#ifndef ANT_H
#define ANT_H

#include <algorithm>
#include <cmath>

#include "Screen.h"
#include "ants.h"

namespace ants
{
    class Ant
    {
    public:
        const static float SIZE, SPEED, TURNINESS;
        const static Uint32 COLOR = 0xFF0000FF;

    private:
        float x, y;
        float homeX, homeY;
        float direction;

    public:
        void setDirection(float newDir)
        {
            direction = fmod(newDir, 2 * M_PI);
        }

    public:
        Ant() : x(0), y(0) {}
        Ant(float x, float y) : x(x), y(y)
        {
            homeX = x;
            homeY = y;
            direction = randFloat() * 2 * M_PI;
        }

        void move(Uint32 elapsedMs, float screenWidth, float screenHeight);

        // Renders the ant to the screen.
        // Returns true if the ant is visible on the screen.
        // TODO: update render to display partial wrapping
        bool render(Screen &screen);
    };
}

#endif