#include "beginners_method.hpp"
#include "cube_generator.hpp"
#include "unistd.h"

string BeginnersMethod::solve(string s) {
    Cube cube = CubeGenerator::fromString(s);
    string result = "";
    
    for(pair<State, CubeAlgorithm*> p : ALGORITHM) {
        State state = p.first;
        CubeAlgorithm* algorithm = p.second;
        
        if(state == State::YELLOW_CROSS) {
            result += yellowCrossSubroutine(cube);
        } else {
            result += cubeAlgorithmSubroutine(state, algorithm, cube);
        }
    }
    
    return result;
}

string BeginnersMethod::cubeAlgorithmSubroutine(State state, 
        CubeAlgorithm* algorithm, Cube& cube) {
    string s;
    
    while(!methodSteps.isStateDone(cube, state)) {
        usleep(100000);
        cout << "Next try on state: " << state << endl;
        s = algorithm->perform(cube);
        cout << s << " done?: " << methodSteps.isStateDone(cube, state) << endl;
        cube.printCube();
    }
    
    return s;
}

string BeginnersMethod::yellowCrossSubroutine(Cube& cube) {
    string s = "";
    cout << "Checking which yellow cross subroutine is appropriate." << endl;
    if(methodSteps.isYellowDotDone(cube)) {
        if(methodSteps.isYellowArcDone(cube)) {
            cout << "Yellow arc is next" << endl;
            s += YellowArc().perform(cube);
        } else if(methodSteps.isYellowLineDone(cube)) {
            cout << "Yellow Line is next" << endl;
            s += YellowLine().perform(cube);
        } else {
            cout << "Yellow dot is next" << endl;
            s += YellowDot().perform(cube);
            s += YellowArc().perform(cube);
        }
    }
    
    return s;
}