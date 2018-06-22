/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   beginners_method.hpp
 * Author: roman.subik
 *
 * Created on 05 May 2018, 10:38
 */

#ifndef BEGINNERS_METHOD_HPP
#define BEGINNERS_METHOD_HPP

#include <iostream>

#include "cube_algorithms.hpp"
#include "method_steps.hpp"

using namespace std;

//DASY, WHITE_CROSS, FIRST_LAYER_CORNERS, SECOND_LAYER_EDGES, 
//    YELLOW_DOT, YELLOW_LINE, YELLOW_ARC,
//    YELLOW_CROSS, POSITION_LAST_LAYER_CORNERS, PERMUTE_LAST_LAYER_CORNERS,
//    SOLVED

const map<State, CubeAlgorithm*> ALGORITHM = {
    {State::DASY, new Dasy()},
    {State::WHITE_CROSS, new WhiteCross()},
    {State::FIRST_LAYER_CORNERS, new FirstLayerCorners()},
    {State::SECOND_LAYER_EDGES, new SecondLayerEdges()},
    {State::YELLOW_CROSS, nullptr},
    {State::POSITION_LAST_LAYER_CORNERS, new PositionLastLayerCorners()},
    {State::PERMUTE_LAST_LAYER_CORNERS, new PermuteLastLayerCorners()},
    {State::POSITION_LAST_LAYER_EDGES, new PositionLastLayerEdges()}
};

class BeginnersMethod {
public:
    BeginnersMethod() { methodSteps = MethodSteps(); };
    string solve(string cubeAsAString);
    
private:
    MethodSteps methodSteps;
    string yellowCrossSubroutine(State state, Cube& cube);
    string cubeAlgorithmSubroutine(State state, CubeAlgorithm* algorithm, Cube& cube);
};

#endif /* BEGINNERS_METHOD_HPP */

