#include "beginners_method.hpp"
#include "cube_generator.hpp"

string BeginnersMethod::solve(string s) {
    Cube cube = CubeGenerator::fromString(s);
    string result = "";
    
    for(pair<State, CubeAlgorithm*> p : ALGORITHM) {
        State state = p.first;
        CubeAlgorithm* algorithm = p.second;
        
        if(state == State::YELLOW_ARC) {
            result += yellowArcSubroutine(cube);
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
        s = algorithm->perform(cube);
    }
    
    return s;
}

string BeginnersMethod::yellowArcSubroutine(Cube& cube) {
    string s = "";
    
    if(methodSteps.isYellowDotDone(cube)) {
        if(methodSteps.isYellowArcDone(cube)) {
            s += YellowArc().perform(cube);
        } else if(methodSteps.isYellowLineDone(cube)) {
            s += YellowLine().perform(cube);
        } else {
            s += YellowDot().perform(cube);
            s += YellowArc().perform(cube);
        }
    }
    
    return s;
}