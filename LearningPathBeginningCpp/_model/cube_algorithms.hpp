/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cube_algorithms.hpp
 * Author: roman.subik
 *
 * Created on 18 February 2018, 14:20
 */

#ifndef CUBE_ALGORITHMS_HPP
#define CUBE_ALGORITHMS_HPP

#include <string>
#include "cube.hpp"

using namespace std;

class CubeAlgorithm {
public:
    CubeAlgorithm(string _steps) : steps(_steps) {initRotations(); initSteps();};
    void perform(Cube & cube);
    
    // rotation string representations
    static const string ROTATE_FRONT_CLOCKWISE;
    static const string ROTATE_UP_CLOCKWISE;
    static const string ROTATE_BACK_CLOCKWISE;
    static const string ROTATE_DOWN_CLOCKWISE;
    static const string ROTATE_RIGHT_CLOCKWISE;
    static const string ROTATE_LEFT_CLOCKWISE;
    static const string ROTATE_FRONT_COUNTER_CLOCKWISE;
    static const string ROTATE_UP_COUNTER_CLOCKWISE;
    static const string ROTATE_BACK_COUNTER_CLOCKWISE;
    static const string ROTATE_DOWN_COUNTER_CLOCKWISE;
    static const string ROTATE_RIGHT_COUNTER_CLOCKWISE;
    static const string ROTATE_LEFT_COUNTER_CLOCKWISE;
    
    // flip string representations
    static const string FLIP_Y_CLOCKWISE_90;
    static const string FLIP_Y_COUNTER_CLOCKWISE_90;
    static const string FLIP_X_CLOCKWISE_90;
    static const string FLIP_X_COUNTER_CLOCKWISE_90;
    static const string FLIP_Z_CLOCKWISE_90;
    static const string FLIP_Z_COUNTER_CLOCKWISE_90;
    static const string FLIP_UPSIDE_DOWN;
    
private:
    string steps;
    map<string, Rotation> rotations;
    map<string, Flip> flips;
    
    void initRotations();
    void initSteps();
};

#endif /* CUBE_ALGORITHMS_HPP */

