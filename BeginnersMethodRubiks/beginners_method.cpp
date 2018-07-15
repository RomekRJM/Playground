#include "beginners_method.hpp"
#include "cube_generator.hpp"
#include "cube_logging.hpp"

void BeginnersMethod::resetInternalState() {
    methodSteps = MethodSteps();

    //Order for ALGORITHM: 
    //DASY, WHITE_CROSS, FIRST_LAYER_CORNERS, SECOND_LAYER_EDGES, 
    //YELLOW_DOT, YELLOW_LINE, YELLOW_ARC,
    //YELLOW_CROSS, POSITION_LAST_LAYER_CORNERS, PERMUTE_LAST_LAYER_CORNERS,
    //SOLVED
    ALGORITHM.insert(pair<State, CubeAlgorithm*>
        {State::DASY, new Dasy()});
    ALGORITHM.insert(pair<State, CubeAlgorithm*>
        {State::WHITE_CROSS, new WhiteCross()});
    ALGORITHM.insert(pair<State, CubeAlgorithm*>
        {State::FIRST_LAYER_CORNERS, new FirstLayerCorners()});
    ALGORITHM.insert(pair<State, CubeAlgorithm*>
        {State::SECOND_LAYER_EDGES, new SecondLayerEdges()});
    ALGORITHM.insert(pair<State, CubeAlgorithm*>
        {State::YELLOW_CROSS, nullptr});
    ALGORITHM.insert(pair<State, CubeAlgorithm*>
        {State::POSITION_LAST_LAYER_CORNERS, new PositionLastLayerCorners()});
    ALGORITHM.insert(pair<State, CubeAlgorithm*>
        {State::PERMUTE_LAST_LAYER_CORNERS, new PermuteLastLayerCorners()});
    ALGORITHM.insert(pair<State, CubeAlgorithm*>
        {State::POSITION_LAST_LAYER_EDGES, new PositionLastLayerEdges()});
}

string BeginnersMethod::solve(string s) {
    resetInternalState();
    
    Cube cube = CubeGenerator::fromString(s);
    string result = "";
    
    for(pair<State, CubeAlgorithm*> p : ALGORITHM) {
        State state = p.first;
        CubeAlgorithm* algorithm = p.second;
        
        if(state == State::YELLOW_CROSS) {
            result += yellowCrossSubroutine(state, cube);
        } else {
            result += cubeAlgorithmSubroutine(state, algorithm, cube);
        }
    }
    
    return result.substr(0, result.size() - 1);
}

string BeginnersMethod::cubeAlgorithmSubroutine(State state, 
        CubeAlgorithm* algorithm, Cube& cube) {
    string s;
    
    while(!methodSteps.isStateDone(cube, state)) {
        debug << "Next try on state: " << state;
        s = algorithm->perform(cube);
        debug << s << " done?: " << methodSteps.isStateDone(cube, state);
        debug << cube.asString();
    }
    
    return s;
}

string BeginnersMethod::yellowCrossSubroutine(State state, Cube& cube) {
    string s = "";
    debug << "Checking which yellow cross subroutine is appropriate.";
    
    if(methodSteps.isYellowCrossDone(cube)) {
        debug << "Nothing to do as yellow cross already done.";
    } else if(methodSteps.isYellowDotDone(cube)) {
        if(methodSteps.isYellowArcDone(cube)) {
            debug << "Yellow arc is next";
            s += YellowArc().perform(cube);
        } else if(methodSteps.isYellowLineDone(cube)) {
            debug << "Yellow Line is next";
            s += YellowLine().perform(cube);
        } else {
            debug << "Yellow dot is next";
            s += YellowDot().perform(cube);
            s += YellowArc().perform(cube);
        }
    } 
    
    debug << s << " done?: " << methodSteps.isStateDone(cube, state);
    debug << cube.asString();
    
    return s;
}