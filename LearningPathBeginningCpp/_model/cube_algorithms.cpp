/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CubeAlgorithms.cpp
 * Author: roman.subik
 * 
 * Created on 18 February 2018, 14:21
 */

#include "cube_algorithms.hpp"

// rotation string representations
const string CubeAlgorithm::ROTATE_FRONT_CLOCKWISE = "F";
const string CubeAlgorithm::ROTATE_UP_CLOCKWISE = "U";
const string CubeAlgorithm::ROTATE_BACK_CLOCKWISE = "B";
const string CubeAlgorithm::ROTATE_DOWN_CLOCKWISE = "D";
const string CubeAlgorithm::ROTATE_RIGHT_CLOCKWISE = "R";
const string CubeAlgorithm::ROTATE_LEFT_CLOCKWISE = "L";
const string CubeAlgorithm::ROTATE_FRONT_COUNTER_CLOCKWISE = "F'";
const string CubeAlgorithm::ROTATE_UP_COUNTER_CLOCKWISE = "U'";
const string CubeAlgorithm::ROTATE_BACK_COUNTER_CLOCKWISE = "B'";
const string CubeAlgorithm::ROTATE_DOWN_COUNTER_CLOCKWISE = "D'";
const string CubeAlgorithm::ROTATE_RIGHT_COUNTER_CLOCKWISE = "R'";
const string CubeAlgorithm::ROTATE_LEFT_COUNTER_CLOCKWISE = "L'";

// flip string representations
const string CubeAlgorithm::FLIP_Y_CLOCKWISE_90 = "y";
const string CubeAlgorithm::FLIP_Y_COUNTER_CLOCKWISE_90 = "y'";
const string CubeAlgorithm::FLIP_X_CLOCKWISE_90 = "x";
const string CubeAlgorithm::FLIP_X_COUNTER_CLOCKWISE_90 = "x'";
const string CubeAlgorithm::FLIP_Z_CLOCKWISE_90 = "z";
const string CubeAlgorithm::FLIP_Z_COUNTER_CLOCKWISE_90 = "z'";
const string CubeAlgorithm::FLIP_UPSIDE_DOWN = "z2";

void CubeAlgorithm::initRotations() {
    rotations.insert(pair<string, Rotation>(ROTATE_FRONT_CLOCKWISE, FRONT_CLOCKWISE));
    rotations.insert(pair<string, Rotation>(ROTATE_UP_CLOCKWISE, UP_CLOCKWISE));
    rotations.insert(pair<string, Rotation>(ROTATE_BACK_CLOCKWISE, BACK_CLOCKWISE));
    rotations.insert(pair<string, Rotation>(ROTATE_DOWN_CLOCKWISE, DOWN_CLOCKWISE));
    rotations.insert(pair<string, Rotation>(ROTATE_RIGHT_CLOCKWISE, RIGHT_CLOCKWISE));
    rotations.insert(pair<string, Rotation>(ROTATE_LEFT_CLOCKWISE, LEFT_CLOCKWISE));
    rotations.insert(pair<string, Rotation>(ROTATE_FRONT_COUNTER_CLOCKWISE, FRONT_COUNTER_CLOCKWISE));
    rotations.insert(pair<string, Rotation>(ROTATE_UP_COUNTER_CLOCKWISE, UP_COUNTER_CLOCKWISE));
    rotations.insert(pair<string, Rotation>(ROTATE_BACK_COUNTER_CLOCKWISE, BACK_COUNTER_CLOCKWISE));
    rotations.insert(pair<string, Rotation>(ROTATE_DOWN_COUNTER_CLOCKWISE, DOWN_COUNTER_CLOCKWISE));
    rotations.insert(pair<string, Rotation>(ROTATE_RIGHT_COUNTER_CLOCKWISE, RIGHT_COUNTER_CLOCKWISE));
    rotations.insert(pair<string, Rotation>(ROTATE_LEFT_COUNTER_CLOCKWISE, LEFT_COUNTER_CLOCKWISE));
}

void CubeAlgorithm::initSteps() {
    flips.insert(pair<string, Flip>(FLIP_Y_CLOCKWISE_90, Y_CLOCKWISE_90));
    flips.insert(pair<string, Flip>(FLIP_Y_COUNTER_CLOCKWISE_90, Y_COUNTER_CLOCKWISE_90));
    flips.insert(pair<string, Flip>(FLIP_X_CLOCKWISE_90, X_CLOCKWISE_90));
    flips.insert(pair<string, Flip>(FLIP_X_COUNTER_CLOCKWISE_90, X_COUNTER_CLOCKWISE_90));
    flips.insert(pair<string, Flip>(FLIP_Z_COUNTER_CLOCKWISE_90, Z_COUNTER_CLOCKWISE_90));
    flips.insert(pair<string, Flip>(FLIP_Z_COUNTER_CLOCKWISE_90, Z_COUNTER_CLOCKWISE_90));
    flips.insert(pair<string, Flip>(FLIP_UPSIDE_DOWN, UPSIDE_DOWN));
}
