
#include "Ant.h"
#include "ants.h"

namespace ants
{
    const Uint32 Ant::COLOR = 0xFF000080;
    const float Ant::SIZE = 2, Ant::SPEED = 50, Ant::TURNINESS = 0.5;

    void Ant::move(Uint32 elapsedMs, float screenWidth, float screenHeight)
    {
        float deltaTime = elapsedMs / 1000.0;

        direction += (randFloat() - 0.5) * TURNINESS;

        float dx = deltaTime * SPEED * cos(direction);
        float dy = deltaTime * SPEED * sin(direction);

        x = rangeMod(x + dx, 0, screenWidth);
        y = rangeMod(y + dy, 0, screenHeight);
    }

    // Renders the ant to the screen.
    // Returns true if the ant is visible on the screen.
    // TODO: update render to display partial wrapping
    bool Ant::render(Screen &screen)
    {
        return screen.drawFillSquare((int)floor(x - SIZE), (int)floor(y - SIZE), (int)ceil(x + SIZE), (int)ceil(y + SIZE), COLOR);
    }
}