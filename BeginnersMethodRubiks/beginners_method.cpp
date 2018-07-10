#include "beginners_method.hpp"
#include "cube_generator.hpp"
#include "unistd.h"

BeginnersMethod::BeginnersMethod() {
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
        usleep(100000);
        cout << "Next try on state: " << state << endl;
        s = algorithm->perform(cube);
        cout << s << " done?: " << methodSteps.isStateDone(cube, state) << endl;
        cube.printCube();
    }
    
    return s;
}

string BeginnersMethod::yellowCrossSubroutine(State state, Cube& cube) {
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
    
    cout << s << " done?: " << methodSteps.isStateDone(cube, state) << endl;
    cube.printCube();
    
    return s;
}