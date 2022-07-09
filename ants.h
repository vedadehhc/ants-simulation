#ifndef ANTS_H
#define ANTS_H

namespace ants
{
    float sqDistance(float x1, float y1, float x2, float y2)
    {
        return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    }

    bool pointInCircle(float px, float py, float cx, float cy, float radius)
    {
        return sqDistance(px, py, cx, cy) <= radius * radius;
    }
}

#endif