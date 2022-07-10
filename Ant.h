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

        void move(Uint32 elapsedMs, float screenWidth, float screenHeight)
        {
            float deltaTime = elapsedMs / 1000.0;

            direction += (randFloat() - 0.5) * TURNINESS;

            float dx = deltaTime * SPEED * cos(direction);
            float dy = deltaTime * SPEED * sin(direction);

            x = clamp(x + dx, 0, screenWidth);
            y = clamp(y + dy, 0, screenHeight);
        }

        // Renders the ant to the screen.
        // Returns true if the ant is visible on the screen.
        // TODO: update render to display partial wrapping
        bool render(Screen &screen)
        {
            int startX = std::max((int)floor(x - SIZE), 0);
            int endX = std::min((int)ceil(x + SIZE), screen.getWidth() - 1);

            int startY = std::max((int)floor(y - SIZE), 0);
            int endY = std::min((int)ceil(y + SIZE), screen.getHeight() - 1);
            
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
                    if (pointInCircle(i + 0.5, j + 0.5, x, y, SIZE))
                        result |= screen.setPixel(i, j, COLOR);
                }
            }
            return result;
        }
    };

    const float Ant::SIZE = 2, Ant::SPEED = 50, Ant::TURNINESS = 0.5;
}

#endif