#include <SDL.h>
#include <cmath>
#include <stdio.h>

#include "ants.h"

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

    float rangeMod(float val, float min, float max)
    {
        float size = max - min;
        val = fmod(val - min, size);
        if (val < 0) val += size;

        return val + min;
    }

    void colorComponentsInt(Uint32 color, int& r, int& g, int& b, int& a)
    {
        r = color >> 24;
        g = (color >> 16) & 0xFF;
        b = (color >> 8) & 0xFF;
        a = color & 0xFF;
    }

    // https://en.wikipedia.org/wiki/Alpha_compositing
    // c1 over c2
    Uint32 colorOver(Uint32 c1, Uint32 c2)
    {
        int r1, g1, b1, a1;
        colorComponentsInt(c1, r1, g1, b1, a1);

        int r2, g2, b2, a2;
        colorComponentsInt(c2, r2, g2, b2, a2);

        // new alpha is a2 * (1 - a1)
        // but we have to adjust formula to use 256 alpha values instead of [0, 1]
        int c2Intensity = (a2 * (0xFF ^ a1)) >> 8;

        int a3 = (a1 + c2Intensity) & 0xFF;
        Uint8 r3 = ((r1 * a1 + r2 * c2Intensity) / a3) & 0xFF;
        Uint8 g3 = ((g1 * a1 + g2 * c2Intensity) / a3) & 0xFF;
        Uint8 b3 = ((b1 * a1 + b2 * c2Intensity) / a3) & 0xFF;

        Uint32 c3 = (r3 << 24) + (g3 << 16) + (b3 << 8) + a3;
        return c3;
    }
}
