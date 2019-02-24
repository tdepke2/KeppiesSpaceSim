#include "Simulator.h"


#include "Body.h"
#include <list>
#include <iostream>

using namespace std;

int main() {
/*
for(int i = 1; i < sortedZ.size(); ++i){
    float target = sortedZ[i];
    int j;
    for(j = i - 1; j >= 0 && sortedZ[j] > target; --j){
        sortedZ[j+ 1] = sortedZ[j];
        }
    sortedZ[j+ 1] = target; 
    }
}
    
    list<Body> bodies(5);
    auto listIter = bodies.begin();
    listIter->zScreen = 3;
    ++listIter;
    listIter->zScreen = 4;
    ++listIter;
    listIter->zScreen = 3;
    ++listIter;
    listIter->zScreen = 5;
    ++listIter;
    listIter->zScreen = 1;
    
    auto outerIter = bodies.begin(), beforeBeginIter = bodies.begin();
    --beforeBeginIter;
    for(++outerIter; outerIter != bodies.end(); ++outerIter) {
        float target = outerIter->zScreen;
        auto innerIter = outerIter;
        for(--innerIter; innerIter != beforeBeginIter && innerIter->zScreen < target; --innerIter) {
            auto tempIter = innerIter;
            ++tempIter;
            tempIter->zScreen = innerIter->zScreen;
        }
        ++innerIter;
        innerIter->zScreen = target;
    }
    
    for(auto outerIter = bodies.begin(); outerIter != bodies.end(); ++outerIter) {
        cout << outerIter->zScreen << endl;
    }*/
    
    return Simulator::start();
}
