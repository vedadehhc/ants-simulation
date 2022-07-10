
#include "Ant.h"
#include "ants.h"
#include "Food.h"

namespace ants
{
    const Uint32 Ant::COLOR = 0xFF000080;
    const float Ant::HEAD_SIZE = 2;
    const float Ant::BODY_SIZE = 3;
    const float Ant::SPEED = 50;
    const float Ant::SPEED_VARIANCE = 5;
    const float Ant::TURNINESS = 0.3;
    const float Ant::HOME_RADIUS = 20;
    const float Ant::SMELL_RANGE = 5;
    const float Ant::PICK_RANGE = 1;
    const float Ant::TRAIL_STRENGTH = 10;

    Ant::Ant(float x, float y, Trail *exploreTrail, Trail *returnTrail) : x(x), y(y), exploreTrail(exploreTrail), returnTrail(returnTrail)
    {
        homeX = x;
        homeY = y;
        direction = randFloat() * 2 * M_PI;
        carryingFood = false;
        speed = SPEED + (randFloat() - 0.5) * SPEED_VARIANCE;
    }

    void Ant::move(Uint32 elapsedMs, float screenWidth, float screenHeight)
    {
        Trail *dispenseTrail = nullptr;
        Trail *targetTrail = nullptr;

        if (!carryingFood)
        {
            dispenseTrail = exploreTrail;
            targetTrail = returnTrail;

            // go thru all foods
            for (std::list<Food *>::iterator it = Food::foods.begin(); it != Food::foods.end(); it++)
            {
                if (pointInCircle((*it)->getX(), (*it)->getY(), x, y, PICK_RANGE))
                {
                    carryingFood = true;
                    Food::deleteFood(it);
                    break;
                }
                else if (pointInCircle((*it)->getX(), (*it)->getY(), x, y, SMELL_RANGE))
                {
                    targetTrail = nullptr;
                    setDirection(atan2((*it)->getY() - y, (*it)->getX() - x));
                    break;
                }
            }
        }

        // allow target readjustment if found food on same frame
        if (carryingFood)
        {
            dispenseTrail = returnTrail;
            targetTrail = exploreTrail;

            // drop off food
            if (pointInCircle(x, y, homeX, homeY, HOME_RADIUS))
            {
                carryingFood = false;
            }
            else if (pointInCircle(x, y, homeX, homeY, HOME_RADIUS + SMELL_RANGE))
            {
                targetTrail = nullptr;
                setDirection(atan2(homeY - y, homeX - x));
            }
        }

        if (dispenseTrail != nullptr)
            dispenseTrail->addTrailPoint(x, y, TRAIL_STRENGTH);

        if (targetTrail != nullptr)
            setDirection(followTrail(targetTrail));

        setDirection(direction + (randFloat() - 0.5) * TURNINESS);

        float deltaTime = elapsedMs / 1000.0;

        float dx = deltaTime * speed * cos(direction);
        float dy = deltaTime * speed * sin(direction);

        x = rangeMod(x + dx, 0, screenWidth);
        y = rangeMod(y + dy, 0, screenHeight);
    }

    float Ant::followTrail(Trail *trail)
    {
        float FOV = 0.5f;

        float center = trail->getStrength(x + SMELL_RANGE * cos(direction), y + SMELL_RANGE * sin(direction), SMELL_RANGE);
        float left = trail->getStrength(x + SMELL_RANGE * cos(direction + FOV), y + SMELL_RANGE * sin(direction + FOV), SMELL_RANGE);
        float right = trail->getStrength(x + SMELL_RANGE * cos(direction - FOV), y + SMELL_RANGE * sin(direction - FOV), SMELL_RANGE);

        if (center >= left && center >= right)
        {
            return direction;
        }
        else if (left > right)
        {
            return direction + FOV;
        }
        else
        {
            return direction - FOV;
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

        if (carryingFood)
        {
            result |= screen.drawFillCircle(x + (2 * HEAD_SIZE + BODY_SIZE) * cos(direction), y + (2 * HEAD_SIZE + BODY_SIZE) * sin(direction), HEAD_SIZE, Food::COLOR);
        }

        return result;
    }
}