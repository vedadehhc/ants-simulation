
#include <list>
#include "Food.h"
#include "Screen.h"

namespace ants
{
    std::list<Food *> Food::foods;

    Food *Food::addFood(float x, float y)
    {
        Food *f = new Food();
        f->x = x;
        f->y = y;

        foods.push_back(f);

        return f;
    }

    void Food::deleteAll()
    {
        std::list<Food *>::iterator it = foods.begin();
        while (foods.size() > 0)
        {
            delete (*it);
            it = foods.erase(it);
        }
    }

    void Food::deleteFood(std::list<Food *>::iterator it)
    {
        Food *f = *it;
        foods.erase(it);
        delete f;
    }

    bool Food::render(Screen &screen)
    {
        screen.setPixel((int)round(x), (int)round(y), 0x88FF8855);
    }
}