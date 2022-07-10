
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
    const float Ant::SMELL_RANGE = 10;
    const float Ant::PICK_RANGE = 5;
    const float Ant::TRAIL_STRENGTH = 10;

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
        }

        if (dispenseTrail != nullptr)
            dispenseTrail->addTrailPoint(x, y, TRAIL_STRENGTH);

        float trailDir = -2;

        if (targetTrail != nullptr)
            trailDir = followTrail(targetTrail);

        if (trailDir < -1)
        {
            setDirection(direction + (randFloat() - 0.5) * TURNINESS);
        }
        else
        {
            // printf("following trail: %f", trailDir);
            setDirection(trailDir);
            // still a little random
            setDirection(direction + (randFloat() - 0.5) * TURNINESS);
        }

        float deltaTime = elapsedMs / 1000.0;

        float dx = deltaTime * SPEED * cos(direction);
        float dy = deltaTime * SPEED * sin(direction);

        x = rangeMod(x + dx, 0, screenWidth);
        y = rangeMod(y + dy, 0, screenHeight);
    }

    float Ant::followTrail(Trail *trail)
    {
        float totalX = 0;
        float totalY = 0;
        float totalWeight = 0;
        bool foundPoints = false;

        int numNeighbors;
        auto neighbors = trail->getNeighborhood(x, y, numNeighbors);

        for (int i = 0; i < numNeighbors; i++)
        {
            for (auto it = neighbors[i]->begin(); it != neighbors[i]->end(); it++)
            {
                if ((*it)->getLifetime() > 0 && pointInCircle((*it)->getX(), (*it)->getY(), x, y, SMELL_RANGE))
                {
                    foundPoints = true;

                    float dirToPoint = rangeMod(atan2((*it)->getY() - y, (*it)->getX() - x), 0, 2 * M_PI);
                    // float weight = (*it)->getLifetime() / (1 + sqDistance(x, y, (*it)->getX(), (*it)->getY()));
                    float weight = (*it)->getLifetime();
                
                    totalX += cos(dirToPoint) * weight;
                    totalY += sin(dirToPoint) * weight;
                    totalWeight += weight;
                }
            }
        }

        delete[] neighbors;

        if (foundPoints)
        {
            // float ret = -atan2(totalY / totalWeight, totalX / totalWeight);
            // printf("RETURNING %f\n", ret);
            return rangeMod(-atan2(totalY / totalWeight, totalX / totalWeight), 0, 2 * M_PI);
        }
        else
        {
            return -2;
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