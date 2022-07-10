
#include "Ant.h"
#include "ants.h"

namespace ants
{
    const float Ant::SIZE = 2, Ant::SPEED = 50, Ant::TURNINESS = 0.5;

    void Ant::move(Uint32 elapsedMs, float screenWidth, float screenHeight)
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
    bool Ant::render(Screen &screen)
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
}