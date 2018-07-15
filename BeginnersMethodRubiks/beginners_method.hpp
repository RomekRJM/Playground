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
#include "cube_logging.hpp"
#include "method_steps.hpp"

using namespace std;

class BeginnersMethod {
public:
    BeginnersMethod() {};
    string solve(string cubeAsAString);
    
private:
    MethodSteps methodSteps;
    map<State, CubeAlgorithm*> ALGORITHM;
    void resetInternalState();
    string yellowCrossSubroutine(State state, Cube& cube);
    string cubeAlgorithmSubroutine(State state, CubeAlgorithm* algorithm, Cube& cube);
};

#endif /* BEGINNERS_METHOD_HPP */

