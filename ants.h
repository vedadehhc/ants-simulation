#ifndef ANTS_H
#define ANTS_H

#include <cmath>

namespace ants
{
    float randFloat();
    float sqDistance(float x1, float y1, float x2, float y2);
    bool pointInCircle(float px, float py, float cx, float cy, float radius);

    float rangeMod(float val, float min, float max);

    void colorComponentsInt(Uint32 color, int& r, int& g, int& b, int& a);

    // https://en.wikipedia.org/wiki/Alpha_compositing
    Uint32 colorOver(Uint32 c1, Uint32 c2);
}

#endif