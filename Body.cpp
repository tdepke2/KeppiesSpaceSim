#include "Body.h"
#include <cmath>
#include <iostream> 
using namespace std;
using namespace sf;

Body::Body(float t, float eccentricity, float mass, float semiMajor, float radius, const Color& color) {
    x = 1.0;
    y = 0.0;
    z = 0.0;
    this->t = t;
    period = sqrt(4*pow(acos(-1), 2)* pow(semiMajor, 3) / mass);
    cout << period << "\n";
    this->eccentricity = eccentricity;
    this->mass = mass;
    semiMajor *= 2.0;
    this->semiMinor = sqrt(pow(semiMajor, 2.0f) * (1.0f - pow(eccentricity, 2.0f)));
    this->semiMajor = semiMajor;
    this->radius = radius;
    this->color = color;
}
