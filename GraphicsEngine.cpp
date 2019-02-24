#include "GraphicsEngine.h"
#include <cmath>

using namespace std;
using namespace sf;

const float GraphicsEngine::PI = acos(-1.0f);
vector<Vector3f> GraphicsEngine::_bodyPoints(12);
vector<ScreenPoint> GraphicsEngine::_bodyScreenPoints(12);

ScreenPoint GraphicsEngine::graphicsTransform(const Vector2u& screenSize, const Vector3f& camRotation, Vector3f point) {
    Vector3f point2;
    point2.x = point.x * cos(camRotation.y) + point.z * sin(camRotation.y);
    point2.z = -point.x * sin(camRotation.y) + point.z * cos(camRotation.y);
    
    point.z = point2.z * cos(camRotation.x) + point.y * sin(camRotation.x);
    point2.y = -point2.z * sin(camRotation.x) + point.y * cos(camRotation.x);
    
    point.y = point2.y * cos(camRotation.z) + point2.x * sin(camRotation.z);
    point.x = -point2.y * sin(camRotation.z) + point2.x * cos(camRotation.z);
    
    float aspectRatio = static_cast<float>(screenSize.x) / screenSize.y;
    if (aspectRatio < 1.0f) {
        point.x /= aspectRatio;
    } else {
        point.y *= aspectRatio;
    }
    
    if (point.z >= 0.0) {
        return ScreenPoint(0.0, 0.0, false);
    }
    point.z *= tan(90.0f * PI / 360.0f);
    point.x = (point.x / -point.z + 1.0f) * screenSize.x / 2.0f;
    point.y = (point.y / point.z + 1.0f) * screenSize.y / 2.0f;
    
    return ScreenPoint(point.x, point.y, true);
}

void GraphicsEngine::redraw(RenderWindow& window, const Vector3f& camPosition, const Vector3f& camRotation, const list<Body>& bodies) {
    for (auto listIter = bodies.begin(); listIter != bodies.end(); ++listIter) {
        float phi = (1.0f + sqrt(5.0f)) / 2.0f;
        for (unsigned int i = 0; i < 4; ++i) {
            Vector3f offset(0.0, -listIter->radius / 2.0, -listIter->radius * phi / 2.0);
            if (i % 2 == 1) {
                offset.z += listIter->radius * phi;
            }
            if (i / 2 % 2 == 1) {
                offset.y += listIter->radius;
            }
            _bodyPoints[i] = Vector3f(listIter->x, listIter->y, listIter->z) + offset;
            _bodyScreenPoints[i] = graphicsTransform(window.getSize(), camRotation, _bodyPoints[i] - camPosition);
        }
        for (unsigned int i = 4; i < 8; ++i) {
            Vector3f offset(-listIter->radius / 2.0, -listIter->radius * phi / 2.0, 0.0);
            if (i % 2 == 1) {
                offset.y += listIter->radius * phi;
            }
            if (i / 2 % 2 == 1) {
                offset.x += listIter->radius;
            }
            _bodyPoints[i] = Vector3f(listIter->x, listIter->y, listIter->z) + offset;
            _bodyScreenPoints[i] = graphicsTransform(window.getSize(), camRotation, _bodyPoints[i] - camPosition);
        }
        for (unsigned int i = 8; i < 12; ++i) {
            Vector3f offset(-listIter->radius * phi / 2.0, 0, -listIter->radius / 2.0);
            if (i % 2 == 1) {
                offset.x += listIter->radius * phi;
            }
            if (i / 2 % 2 == 1) {
                offset.z += listIter->radius;
            }
            _bodyPoints[i] = Vector3f(listIter->x, listIter->y, listIter->z) + offset;
            _bodyScreenPoints[i] = graphicsTransform(window.getSize(), camRotation, _bodyPoints[i] - camPosition);
        }
        drawTriangle(window, camPosition, listIter->color, _bodyPoints[0], _bodyPoints[2], _bodyPoints[8], _bodyScreenPoints[0], _bodyScreenPoints[2], _bodyScreenPoints[8]);
        drawTriangle(window, camPosition, listIter->color, _bodyPoints[0], _bodyPoints[8], _bodyPoints[4], _bodyScreenPoints[0], _bodyScreenPoints[8], _bodyScreenPoints[4]);
        drawTriangle(window, camPosition, listIter->color, _bodyPoints[0], _bodyPoints[4], _bodyPoints[6], _bodyScreenPoints[0], _bodyScreenPoints[4], _bodyScreenPoints[6]);
        drawTriangle(window, camPosition, listIter->color, _bodyPoints[0], _bodyPoints[6], _bodyPoints[9], _bodyScreenPoints[0], _bodyScreenPoints[6], _bodyScreenPoints[9]);
        drawTriangle(window, camPosition, listIter->color, _bodyPoints[0], _bodyPoints[9], _bodyPoints[2], _bodyScreenPoints[0], _bodyScreenPoints[9], _bodyScreenPoints[2]);
        drawTriangle(window, camPosition, listIter->color, _bodyPoints[2], _bodyPoints[9], _bodyPoints[7], _bodyScreenPoints[2], _bodyScreenPoints[9], _bodyScreenPoints[7]);
        drawTriangle(window, camPosition, listIter->color, _bodyPoints[2], _bodyPoints[7], _bodyPoints[5], _bodyScreenPoints[2], _bodyScreenPoints[7], _bodyScreenPoints[5]);
        drawTriangle(window, camPosition, listIter->color, _bodyPoints[2], _bodyPoints[5], _bodyPoints[8], _bodyScreenPoints[2], _bodyScreenPoints[5], _bodyScreenPoints[8]);
        drawTriangle(window, camPosition, listIter->color, _bodyPoints[8], _bodyPoints[5], _bodyPoints[10], _bodyScreenPoints[8], _bodyScreenPoints[5], _bodyScreenPoints[10]);
        drawTriangle(window, camPosition, listIter->color, _bodyPoints[8], _bodyPoints[10], _bodyPoints[4], _bodyScreenPoints[8], _bodyScreenPoints[10], _bodyScreenPoints[4]);
        drawTriangle(window, camPosition, listIter->color, _bodyPoints[4], _bodyPoints[10], _bodyPoints[1], _bodyScreenPoints[4], _bodyScreenPoints[10], _bodyScreenPoints[1]);
        drawTriangle(window, camPosition, listIter->color, _bodyPoints[4], _bodyPoints[1], _bodyPoints[6], _bodyScreenPoints[4], _bodyScreenPoints[1], _bodyScreenPoints[6]);
        drawTriangle(window, camPosition, listIter->color, _bodyPoints[6], _bodyPoints[1], _bodyPoints[11], _bodyScreenPoints[6], _bodyScreenPoints[1], _bodyScreenPoints[11]);
        drawTriangle(window, camPosition, listIter->color, _bodyPoints[6], _bodyPoints[11], _bodyPoints[9], _bodyScreenPoints[6], _bodyScreenPoints[11], _bodyScreenPoints[9]);
        drawTriangle(window, camPosition, listIter->color, _bodyPoints[9], _bodyPoints[11], _bodyPoints[7], _bodyScreenPoints[9], _bodyScreenPoints[11], _bodyScreenPoints[7]);
        drawTriangle(window, camPosition, listIter->color, _bodyPoints[3], _bodyPoints[5], _bodyPoints[7], _bodyScreenPoints[3], _bodyScreenPoints[5], _bodyScreenPoints[7]);
        drawTriangle(window, camPosition, listIter->color, _bodyPoints[3], _bodyPoints[10], _bodyPoints[5], _bodyScreenPoints[3], _bodyScreenPoints[10], _bodyScreenPoints[5]);
        drawTriangle(window, camPosition, listIter->color, _bodyPoints[3], _bodyPoints[1], _bodyPoints[10], _bodyScreenPoints[3], _bodyScreenPoints[1], _bodyScreenPoints[10]);
        drawTriangle(window, camPosition, listIter->color, _bodyPoints[3], _bodyPoints[11], _bodyPoints[1], _bodyScreenPoints[3], _bodyScreenPoints[11], _bodyScreenPoints[1]);
        drawTriangle(window, camPosition, listIter->color, _bodyPoints[3], _bodyPoints[7], _bodyPoints[11], _bodyScreenPoints[3], _bodyScreenPoints[7], _bodyScreenPoints[11]);
    }
}

void GraphicsEngine::drawTriangle(RenderWindow& window, const Vector3f& camPosition, const Color& color, const Vector3f& a, const Vector3f& b, const Vector3f& c, const ScreenPoint& aS, const ScreenPoint& bS, const ScreenPoint& cS) {
    if (!aS.visible || !bS.visible || !cS.visible) {
        return;
    }
    Vector3f v1(b - a), v2(c - a);
    Vector3f normal(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
    Vector3f vectToTriangle(a - camPosition);
    if (vectToTriangle.x * normal.x + vectToTriangle.y * normal.y + vectToTriangle.z * normal.z <= 0.0) {
        return;
    }
    VertexArray triangle(Triangles, 3);
    triangle[0].position = Vector2f(aS.x, aS.y);
    triangle[1].position = Vector2f(bS.x, bS.y);
    triangle[2].position = Vector2f(cS.x, cS.y);
    triangle[0].color = color;
    triangle[1].color = color;
    triangle[2].color = color;
    window.draw(triangle);
}
