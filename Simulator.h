#ifndef _SIMULATOR_H
#define _SIMULATOR_H

#include <cmath>

using namespace std;

class Simulator {
    public:
    static const float FPS_CAP;
    static const float PI;
    
    private:
    enum class State {
        uninitialized, running
    };
    
    static State state;
};

#endif
