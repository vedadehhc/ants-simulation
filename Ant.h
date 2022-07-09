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
        const static float ANT_SIZE, ANT_SPEED;

    private:
        float x, y;
        float direction;

    public:
        void setDirection(float newDir)
        {
            direction = fmod(newDir, 2 * M_PI);
        }

    public:
        Ant() : x(0), y(0)
        {
            direction = (((float)rand()) / RAND_MAX) * 2 * M_PI;
        }
        Ant(float x, float y) : x(x), y(y)
        {
            direction = (((float)rand()) / RAND_MAX) * 2 * M_PI;
        }

        void move(Uint32 elapsedMs, float screenWidth, float screenHeight)
        {
            float deltaTime = elapsedMs / 1000.0;

            float dx = deltaTime * ANT_SPEED * cos(direction);
            float dy = deltaTime * ANT_SPEED * sin(direction);

            x = clamp(x + dx, 0, screenWidth);
            y = clamp(y + dy, 0, screenHeight);
        }

        // Renders the ant to the screen.
        // Returns true if the ant is visible on the screen.
        bool render(Screen &screen)
        {
            int startX = std::max((int)floor(x - ANT_SIZE), 0);
            int endX = std::min((int)ceil(x + ANT_SIZE), screen.getWidth() - 1);

            int startY = std::max((int)floor(y - ANT_SIZE), 0);
            int endY = std::min((int)ceil(y + ANT_SIZE), screen.getHeight() - 1);
            
            if (startX >= screen.getWidth() || endX < 0 || startY >= screen.getHeight() || endY < 0)
            {
                return false;
            }

            // Try rendering on screen
            bool result = false;
            for (int i = startX; i <= endX; i++)
            {
                for (int j = startY; j <= endY; j++)
                {
                    // if (pointInCircle(i + 0.5, j + 0.5, x, y, ANT_SIZE))
                    result |= screen.setPixel(i, j, 0xFF0000FF);
                }
            }
            return result;
        }
    };

    const float Ant::ANT_SIZE = 2, Ant::ANT_SPEED = 50;
}

#endif