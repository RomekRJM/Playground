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
#include <iostream>

using namespace std;

bool CubePosition::operator==(CubePosition &other) {
    return (side == other.side) && (row == other.row) && (column == other.column);
}

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

const map<string, Rotation> CubeAlgorithm::rotations = {
    {CubeAlgorithm::ROTATE_FRONT_CLOCKWISE, FRONT_CLOCKWISE},
    {CubeAlgorithm::ROTATE_UP_CLOCKWISE, UP_CLOCKWISE},
    {CubeAlgorithm::ROTATE_BACK_CLOCKWISE, BACK_CLOCKWISE},
    {CubeAlgorithm::ROTATE_DOWN_CLOCKWISE, DOWN_CLOCKWISE},
    {CubeAlgorithm::ROTATE_RIGHT_CLOCKWISE, RIGHT_CLOCKWISE},
    {CubeAlgorithm::ROTATE_LEFT_CLOCKWISE, LEFT_CLOCKWISE},
    {CubeAlgorithm::ROTATE_FRONT_COUNTER_CLOCKWISE, FRONT_COUNTER_CLOCKWISE},
    {CubeAlgorithm::ROTATE_UP_COUNTER_CLOCKWISE, UP_COUNTER_CLOCKWISE},
    {CubeAlgorithm::ROTATE_BACK_COUNTER_CLOCKWISE, BACK_COUNTER_CLOCKWISE},
    {CubeAlgorithm::ROTATE_DOWN_COUNTER_CLOCKWISE, DOWN_COUNTER_CLOCKWISE},
    {CubeAlgorithm::ROTATE_RIGHT_COUNTER_CLOCKWISE, RIGHT_COUNTER_CLOCKWISE},
    {CubeAlgorithm::ROTATE_LEFT_COUNTER_CLOCKWISE, LEFT_COUNTER_CLOCKWISE}
};

const map<string, Flip> CubeAlgorithm::flips = {
    {CubeAlgorithm::FLIP_Y_CLOCKWISE_90, Y_CLOCKWISE_90},
    {CubeAlgorithm::FLIP_Y_COUNTER_CLOCKWISE_90, Y_COUNTER_CLOCKWISE_90},
    {CubeAlgorithm::FLIP_X_CLOCKWISE_90, X_CLOCKWISE_90},
    {CubeAlgorithm::FLIP_X_COUNTER_CLOCKWISE_90, X_COUNTER_CLOCKWISE_90},
    {CubeAlgorithm::FLIP_Z_COUNTER_CLOCKWISE_90, Z_COUNTER_CLOCKWISE_90},
    {CubeAlgorithm::FLIP_Z_COUNTER_CLOCKWISE_90, Z_COUNTER_CLOCKWISE_90},
    {CubeAlgorithm::FLIP_UPSIDE_DOWN, UPSIDE_DOWN}
};

const array<string, 4> CubeAlgorithm::RIGHTY = {
    ROTATE_RIGHT_CLOCKWISE, ROTATE_UP_CLOCKWISE,
    ROTATE_RIGHT_COUNTER_CLOCKWISE, ROTATE_UP_COUNTER_CLOCKWISE
};

const array<string, 4> CubeAlgorithm::LEFTY = {
    ROTATE_LEFT_COUNTER_CLOCKWISE, ROTATE_UP_COUNTER_CLOCKWISE,
    ROTATE_LEFT_CLOCKWISE, ROTATE_UP_CLOCKWISE
};

const array<CubePosition, 4> Dasy::WHITE_PETALS = {
    CubePosition(UP, 0, 1), CubePosition(UP, 1, 0),
    CubePosition(UP, 1, 2), CubePosition(UP, 2, 1)
};

const array<PetalSolution, 1> Dasy::PETAL_SOLUTIONS = {
    PetalSolution(CubePosition(FRONT, 1, 2), CubePosition(UP, 1, 2), ROTATE_RIGHT_CLOCKWISE)
};

string Dasy::findStartingPosition(Cube &cube) {
    return "";
}

string Dasy::rotate(Cube &cube) {
    const CubePosition *whitePetal = nextMissingWhitePetal(cube);

    if (whitePetal) {
        cout << whitePetal->side << ", " << whitePetal->row << ", "
                << whitePetal->column;
    }

    return "";
}

const CubePosition* Dasy::nextMissingWhitePetal(Cube cube) {
    for (auto it = WHITE_PETALS.begin(); it != WHITE_PETALS.end(); ++it) {
        if (cube.cube[it->side][it->row][it->column] != WHITE) {
            return it;
        }
    }

    return nullptr;
}