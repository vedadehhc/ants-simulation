#ifndef ANTS_H
#define ANTS_H

#include <cmath>

namespace ants
{
    float randFloat()
    {
        return ((float) rand()) / ((float) RAND_MAX);
    }

    float sqDistance(float x1, float y1, float x2, float y2)
    {
        return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    }

    bool pointInCircle(float px, float py, float cx, float cy, float radius)
    {
        return sqDistance(px, py, cx, cy) <= radius * radius;
    }

    float clamp(float val, float min, float max)
    {
        float size = max - min;
        val = fmod(val - min, size);
        if (val < 0) val += size;

        return val + min;
    }
}

#endif