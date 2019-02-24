#ifndef _BODY_H
#define _BODY_H

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Body {
    public:
    float x, y, z, t, period;
    float eccentricity, mass, semiMinor, semiMajor, radius;
    Color color;
    
    Body(float t, float eccentricity, float mass, float semiMajor, float radius, const Color& color);
};

#endif
