#ifndef _GRAPHICSENGINE_H
#define _GRAPHICSENGINE_H

#include "Body.h"
#include <list>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

struct ScreenPoint {
    float x, y, z;
    bool visible;
    
    ScreenPoint() : x(0), y(0), z(0), visible(false) {}
    ScreenPoint(float x, float y, float z, bool visible) : x(x), y(y), z(z), visible(visible) {}
};

class GraphicsEngine {
    public:
    static const float PI;
    
    ScreenPoint graphicsTransform(const Vector2u& screenSize, const Vector3f& camRotation, Vector3f point);
    void redraw(RenderWindow& window, const Vector3f& camPosition, const Vector3f& camRotation, const list<Body>& bodies);
    void drawTriangle(RenderWindow& window, const Vector3f& camPosition, const Color& color, const Vector3f& a, const Vector3f& b, const Vector3f& c, const ScreenPoint& aS, const ScreenPoint& bS, const ScreenPoint& cS);
    
    private:
    static vector<Vector3f> _bodyPoints;
    static vector<ScreenPoint> _bodyScreenPoints;
};

#endif
