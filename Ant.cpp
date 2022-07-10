
#include "Ant.h"
#include "ants.h"
#include "Food.h"

namespace ants
{
    const Uint32 Ant::COLOR = 0xFF000080;
    const float Ant::HEAD_SIZE = 2;
    const float Ant::BODY_SIZE = 3;
    const float Ant::SPEED = 50;
    const float Ant::TURNINESS = 0.5;
    const float Ant::HOME_RADIUS = 20;
    const float Ant::RANGE = 5;
    const float Ant::TRAIL_STRENGTH = 10;

    void Ant::move(Uint32 elapsedMs, float screenWidth, float screenHeight)
    {
        float deltaTime = elapsedMs / 1000.0;

        float dx = deltaTime * SPEED * cos(direction);
        float dy = deltaTime * SPEED * sin(direction);

        x = rangeMod(x + dx, 0, screenWidth);
        y = rangeMod(y + dy, 0, screenHeight);

        if (!carryingFood)
        {
            exploreTrail->addTrailPoint(x, y, TRAIL_STRENGTH);
            direction += (randFloat() - 0.5) * TURNINESS;

            // go thru all foods
            for (std::list<Food *>::iterator it = Food::foods.begin(); it != Food::foods.end(); it++)
            {
                if (pointInCircle((*it)->getX(), (*it)->getY(), x, y, RANGE))
                {
                    carryingFood = true;
                    Food::deleteFood(it);
                    break;
                }
            }
        }
        else
        {
            returnTrail->addTrailPoint(x, y, TRAIL_STRENGTH);
            // TODO: change this behavior
            direction = atan2(homeY - y, homeX - x);

            // drop off food
            if (pointInCircle(x, y, homeX, homeY, HOME_RADIUS))
            {
                carryingFood = false;
            }
        }
    }

    // Renders the ant to the screen.
    // Returns true if the ant is visible on the screen.
    // TODO: update render to display partial wrapping
    bool Ant::render(Screen &screen)
    {
        // return screen.drawFillSquare((int)floor(x - SIZE), (int)floor(y - SIZE), (int)ceil(x + SIZE), (int)ceil(y + SIZE), COLOR);
        bool result = false;
        result |= screen.drawFillCircle(x, y, BODY_SIZE, COLOR);
        result |= screen.drawFillCircle(x + (HEAD_SIZE + BODY_SIZE) * cos(direction), y + (HEAD_SIZE + BODY_SIZE) * sin(direction), HEAD_SIZE, COLOR);
        return result;
    }
}