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
        static std::list<Food *> foods;
        static Food *addFood(float x, float y);
        static void deleteAll();
        static void deleteFood(std::list<Food *>::iterator it);

    private:
        float x, y;

    public:
        bool render(Screen& screen)
        {
            screen.setPixel((int) round(x), (int) round(y), 0x00FF0055);
        }
    };
}

#endif