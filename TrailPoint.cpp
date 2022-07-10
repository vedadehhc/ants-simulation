#include <cmath>

#include "TrailPoint.h"
#include "Trail.h"

namespace ants
{    
    TrailPoint::~TrailPoint()
    {
        owner = NULL;
    }

    bool TrailPoint::update(Uint32 elapsedMs)
    {
        lifetime -= elapsedMs / 1000.0;
        return lifetime > 0;
    }

    bool TrailPoint::render(Screen &screen)
    {
        int brightness = round(0xFF * lifetime / maxLifetime);
        screen.addToPixel(x, y, (owner->getColor() & 0xFFFFFF00) + (brightness & 0xFF));
    }
}