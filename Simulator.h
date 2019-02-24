#ifndef _SIMULATOR_H
#define _SIMULATOR_H

using namespace std;

class Simulator {
    public:
    static const float FPS_CAP;
    static const float PI;
    
    static int start();
    
    private:
    enum class State {
        uninitialized, running, exiting
    };
    
    static State state;
};

#endif
