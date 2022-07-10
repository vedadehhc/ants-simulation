#ifndef FOOD_H
#define FOOD_H

#include <list>
#include <cmath>

#include "Screen.h"

namespace ants
{

    class Food
    {
    public:
        static const Uint32 COLOR;

        static std::list<Food *> foods;
        static Food *addFood(float x, float y);
        static void deleteAll();
        static void deleteFood(std::list<Food *>::iterator it);

    private:
        float x, y;

    public:
        bool render(Screen &screen);
        float getX() { return x; }
        float getY() { return y; }
    };
}

#endif