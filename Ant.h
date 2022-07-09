#ifndef ANT_H
#define ANT_H

#include <algorithm>
#include <cmath>

#include "Screen.h"

namespace ants
{
    class Ant
    {
    public:
        const static float ANT_SIZE;

    private:
        float x, y;
        float direction;

    public:
        Ant() : x(0), y(0) {}
        Ant(float x, float y) : x(x), y(y) {}

        void render(Screen &screen)
        {
            int startX = std::max((int)std::floor(x - ANT_SIZE), 0);
            int endX = std::min((int)std::ceil(x + ANT_SIZE), screen.getWidth() - 1);

            int startY = std::max((int)std::floor(y - ANT_SIZE), 0);
            int endY = std::min((int)std::ceil(y + ANT_SIZE), screen.getHeight() - 1);

            for (int i = startX; i <= endX; i++)
            {
                for (int j = startY; j <= endY; j++)
                {
                    screen.setPixel(i, j, 0xFF0000FF);
                }
            }
        }
    };

    const float Ant::ANT_SIZE = 10;
}

#endif