#include <SDL.h>
#include <cmath>

#include "Trail.h"
#include "TrailPoint.h"
#include "Screen.h"

namespace ants
{

    Trail::~Trail()
    {
        deleteAll();
    }

    TrailPoint *Trail::addTrailPoint(float x, float y, float lifetime)
    {
        TrailPoint *tp = new TrailPoint(x, y, this, lifetime);

        points.push_back(tp);

        return tp;
    }

    std::list<TrailPoint *>::iterator Trail::getBeginIter()
    {
        return points.begin();
    }

    std::list<TrailPoint *>::iterator Trail::getEndIter()
    {
        return points.end();
    }

    void Trail::deleteAll()
    {
        auto it = points.begin();
        while (points.size() > 0)
        {
            delete (*it);
            it = points.erase(it);
        }
    }

    void Trail::update(Uint32 elapsedMs)
    {
        for (auto it = points.begin(); it != points.end();)
        {
            if (!(*it)->update(elapsedMs))
            {
                delete (*it);
                it = points.erase(it);
            }
            else
            {
                it++;
            }
        }
    }

    bool Trail::render(Screen &screen)
    {
        for (auto it = points.begin(); it != points.end(); it++)
        {
            (*it)->render(screen);
        }
    }
}