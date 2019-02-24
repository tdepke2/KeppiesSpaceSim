#include "Body.h"
#include "GraphicsEngine.h"
#include "Simulator.h"
#include <cassert>
#include <cmath>
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

const float Simulator::FPS_CAP = 60.0f;
const float Simulator::PI = acos(-1.0f);
Simulator::State Simulator::state = State::uninitialized;

int Simulator::start() {
    RenderWindow window;
    try {
        assert(state == State::uninitialized);
        state = State::running;
        window.create(VideoMode(500, 500), "Keppies Space Sim");
        
        GraphicsEngine graphicsEngine;
        list<Body> bodies;
        Vector3f camPosition(0.0f, 0.0f, 5.0f), camRotation(0.0f, 0.0f, 0.0f);
        Vector2i mousePosition(0, 0);
        View view(FloatRect(Vector2f(0.0f, 0.0f), Vector2f(window.getSize())));
        Clock mainClock, fpsClock;    // The mainClock keeps track of elapsed frame time, fpsClock is used to count frames per second.
        int fpsCounter = 0;
        
        bodies.emplace_back(0, 0, 100, 0.0001, 1, Color::Yellow);
        bodies.emplace_back(0, 0.206, 0.33, 0.3871, 0.1, Color(219, 181,111));
        bodies.emplace_back(0, 0.007, 4.87, 0.72333, 0.1, Color(229, 197, 94));
        bodies.emplace_back(0, 0.017, 5.97, 1, 0.1, Color(63, 126, 226));
        bodies.emplace_back(0, 0.093, 0.642, 1.52366, 0.1, Color(186, 125, 93));
        bodies.emplace_back(0, 0.048, 1898.0, 5.20336, 0.4, Color(186, 165, 139));
        bodies.emplace_back(0, 0.056, 568.0, 9.53707, 0.1, Color(211, 188, 158));
        bodies.emplace_back(0, 0.047, 86.8, 19.1913, 0.1, Color(148, 206, 201));
        bodies.emplace_back(0, 0.009, 102.0, 30.069, 0.1, Color(77, 122, 198));
        bodies.emplace_back(0, 0.248, 0.0146, 39.48, 0.01, Color(219, 210, 199));
        bodies.emplace_back(0, 0.8, 25, 3.5, 0.1, Color::Green);
        
        while (state != State::exiting) {
            window.clear ();
            window.setView(view);
            RectangleShape marker(Vector2f(10.0, 10.0));
            ScreenPoint markerPoint = graphicsEngine.graphicsTransform(window.getSize(), camRotation, Vector3f(1.0, 0.0, 0.0) - camPosition);
            marker.setPosition(Vector2f(markerPoint.x, markerPoint.y));
            marker.setFillColor(Color::Red);
            window.draw(marker);
            markerPoint = graphicsEngine.graphicsTransform(window.getSize(), camRotation, Vector3f(0.0, 1.0, 0.0) - camPosition);
            marker.setPosition(Vector2f(markerPoint.x, markerPoint.y));
            marker.setFillColor(Color::Green);
            window.draw(marker);
            markerPoint = graphicsEngine.graphicsTransform(window.getSize(), camRotation, Vector3f(0.0, 0.0, 1.0) - camPosition);
            marker.setPosition(Vector2f(markerPoint.x, markerPoint.y));
            marker.setFillColor(Color::Blue);
            window.draw(marker);
            graphicsEngine.redraw(window, camPosition, camRotation, bodies);
            window.display();
            
            while (mainClock.getElapsedTime().asSeconds() < 1.0f / FPS_CAP) {}    // Slow down simulation if the current FPS is greater than the FPS cap.
            float deltaTime = mainClock.restart().asSeconds();    // Change in time since the last frame.
            
            if (fpsClock.getElapsedTime().asSeconds() >= 1.0f) {    // Calculate FPS.
                window.setTitle("Keppies Space Sim (FPS: " + to_string(fpsCounter) + ", pos = (" + to_string(camPosition.x) + ", " + to_string(camPosition.y) + ", " + to_string(camPosition.z) + "), rot = (" + to_string(camRotation.x) + ", " + to_string(camRotation.y) + ", " + to_string(camRotation.z) + ") )");
                fpsClock.restart();
                fpsCounter = 0;
            } else {
                ++fpsCounter;
            }
            
            Event event;
            while (window.pollEvent(event)) {    // Process events.
                if (event.type == Event::MouseMoved) {
                    if (Mouse::isButtonPressed (Mouse::Left)) {
                        camRotation.y += (event.mouseMove.x - mousePosition.x) * 0.01f;
                        if (camRotation.y >= PI * 2.0f) {
                            camRotation.y -= PI * 2.0f;
                        } else if (camRotation.y <= -PI * 2.0f) {
                            camRotation.y += PI * 2.0f;
                        }
                        
                        camRotation.x += (event.mouseMove.y - mousePosition.y) * 0.01f;
                        if (camRotation.x > PI / 2.0f) {
                            camRotation.x = PI / 2.0f;
                        } else if (camRotation.x < -PI / 2.0f) {
                            camRotation.x = -PI / 2.0f;
                        }
                    }
                    
                    mousePosition.x = event.mouseMove.x;
                    mousePosition.y = event.mouseMove.y;
                } else if (event.type == Event::Resized) {
                    view.reset(FloatRect(Vector2f(0.0f, 0.0f), Vector2f(window.getSize())));
                } else if (event.type == Event::Closed) {
                    window.close();
                    state = State::exiting;
                }
            }
            
            // Check for keypress.
            float deltaX = 0.0f, deltaZ = 0.0f;
            if (Keyboard::isKeyPressed (Keyboard::W)) {
                deltaZ -= 5.0f * deltaTime;
            }
            if (Keyboard::isKeyPressed (Keyboard::S)) {
                deltaZ += 5.0f * deltaTime;
            }
            if (Keyboard::isKeyPressed (Keyboard::D)) {
                deltaX += 5.0f * deltaTime;
            }
            if (Keyboard::isKeyPressed (Keyboard::A)) {
                deltaX -= 5.0f * deltaTime;
            }
            camPosition.x += deltaX * cos(camRotation.y) - deltaZ * sin(camRotation.y);
            camPosition.z += deltaX * sin(camRotation.y) + deltaZ * cos(camRotation.y);
            
            if (Keyboard::isKeyPressed (Keyboard::Space)) {
                camPosition.y += 5.0f * deltaTime;
            }
            if (Keyboard::isKeyPressed (Keyboard::LShift)) {
                camPosition.y -= 5.0f * deltaTime;
            }
            
            for (auto listIter = bodies.begin(); listIter != bodies.end(); ++listIter) {    // Update solar bodies.
                float v = sqrt(fabs(0.1 * listIter->mass * (2.0 / sqrt(pow(listIter->x, 2.0) + pow(listIter->y, 2.0) + pow(listIter->z, 2.0))) - 1.0 / listIter->semiMajor));
                listIter->t += v * deltaTime;
                if (listIter->t > 2.0f * PI) {
                    listIter->t -= 2.0f * PI;
                }
                float lastX = listIter->x, lastY = listIter->y;
                listIter->x = listIter->semiMajor * cos(listIter->t) - sqrt(pow(listIter->semiMajor, 2) - pow(listIter->semiMinor, 2));
                listIter->y = listIter->semiMinor * sin(listIter->t);
                //cout << "v = " << sqrt(pow(lastX - listIter->x, 2.0) + pow(lastY - listIter->y, 2.0)) << endl;
            }
        }
    } catch(exception& ex) {    // Catch any exceptions here and handle them as a crash.
        window.close();
        cout << "Exception thrown: " << ex.what() << endl;
        cin.get();
        return -1;
    }
    
    return 0;
}
