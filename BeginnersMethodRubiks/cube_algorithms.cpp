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

const array<PetalSolution, 20> Dasy::PETAL_SOLUTIONS = {
    PetalSolution(CubePosition(FRONT, 0, 1), CubePosition(UP, 2, 1), ROTATE_FRONT_CLOCKWISE),
    PetalSolution(CubePosition(FRONT, 1, 0), CubePosition(UP, 1, 0), ROTATE_LEFT_COUNTER_CLOCKWISE),
    PetalSolution(CubePosition(FRONT, 1, 2), CubePosition(UP, 1, 2), ROTATE_RIGHT_CLOCKWISE),
    PetalSolution(CubePosition(FRONT, 2, 1), CubePosition(UP, 2, 1), ROTATE_FRONT_CLOCKWISE),
    PetalSolution(CubePosition(RIGHT, 0, 1), CubePosition(UP, 1, 2), ROTATE_RIGHT_CLOCKWISE),
    PetalSolution(CubePosition(RIGHT, 1, 0), CubePosition(UP, 2, 1), ROTATE_FRONT_COUNTER_CLOCKWISE),
    PetalSolution(CubePosition(RIGHT, 1, 2), CubePosition(UP, 0, 1), ROTATE_BACK_CLOCKWISE),
    PetalSolution(CubePosition(RIGHT, 2, 1), CubePosition(UP, 1, 2), ROTATE_RIGHT_CLOCKWISE),
    PetalSolution(CubePosition(LEFT, 0, 1), CubePosition(UP, 1, 0), ROTATE_LEFT_CLOCKWISE),
    PetalSolution(CubePosition(LEFT, 1, 0), CubePosition(UP, 0, 1), ROTATE_BACK_COUNTER_CLOCKWISE),
    PetalSolution(CubePosition(LEFT, 1, 2), CubePosition(UP, 2, 1), ROTATE_FRONT_CLOCKWISE),
    PetalSolution(CubePosition(LEFT, 2, 1), CubePosition(UP, 1, 0), ROTATE_LEFT_CLOCKWISE),
    PetalSolution(CubePosition(BACK, 0, 1), CubePosition(UP, 0, 1), ROTATE_BACK_CLOCKWISE),
    PetalSolution(CubePosition(BACK, 1, 0), CubePosition(UP, 1, 2), ROTATE_RIGHT_COUNTER_CLOCKWISE),
    PetalSolution(CubePosition(BACK, 1, 2), CubePosition(UP, 1, 0), ROTATE_LEFT_CLOCKWISE),
    PetalSolution(CubePosition(BACK, 2, 1), CubePosition(UP, 0, 1), ROTATE_BACK_CLOCKWISE),
    PetalSolution(CubePosition(DOWN, 0, 1), CubePosition(UP, 2, 1), ROTATE_FRONT_CLOCKWISE),
    PetalSolution(CubePosition(DOWN, 1, 0), CubePosition(UP, 1, 0), ROTATE_LEFT_COUNTER_CLOCKWISE),
    PetalSolution(CubePosition(DOWN, 1, 2), CubePosition(UP, 1, 2), ROTATE_RIGHT_CLOCKWISE),
    PetalSolution(CubePosition(DOWN, 2, 1), CubePosition(UP, 0, 1), ROTATE_BACK_CLOCKWISE)
};

void CubeAlgorithm::doMove(Cube &cube, string move) {
    map<string, Rotation>::const_iterator itRot = rotations.find(move);
    
    if(itRot != rotations.end()) {
        cube.rotate(itRot->second);
        ss << move << ","; 
    }
    
    map<string, Flip>::const_iterator itFlp = flips.find(move);
    
    if(itFlp != flips.end()) {
        cube.flip(itFlp->second);
        ss << move << ","; 
    }
}

void Dasy::findStartingPosition(Cube &cube) {
}

void Dasy::rotate(Cube &cube) {
    const PetalSolution* solution = nextMissingWhiteEdge(cube);
    
    if(!solution) {
        return;
    }
    
    for(int i=0; i<3; ++i) {
        if(cube.getColor(solution->cantBeWhite) == WHITE) {
            CubeAlgorithm::doMove(cube, CubeAlgorithm::ROTATE_UP_CLOCKWISE);
        }
    }
    
    CubeAlgorithm::doMove(cube, solution->rotation);
}

const PetalSolution* Dasy::nextMissingWhiteEdge(Cube cube) {
    for(auto it=PETAL_SOLUTIONS.begin(); it != PETAL_SOLUTIONS.end(); ++it) {
        if(cube.getColor(it->startingPosition) == WHITE) {
            return it;
        }
    }

    return nullptr;
}

void WhiteCross::findStartingPosition(Cube &cube) {
    for(int i=0; i<3; ++i) {
        try {
            matchingSide = findMatchingSide(cube);
            break;
        } catch (SideNotFoundException exc) {
            cout << "Another rotation - side was not found" << endl;
            CubeAlgorithm::doMove(cube, CubeAlgorithm::ROTATE_UP_CLOCKWISE);
        }
    }
}

Side WhiteCross::findMatchingSide(Cube cube) {
    array<Side, 4> topLayerSides = {FRONT, RIGHT, BACK, LEFT};
    
    for (Side side : topLayerSides) {
        if ((cube.cube[side][0][1] == cube.cube[side][1][1]) &&
                (cube.cube[side][0][1] == cube.getSideLeadingColor(side))) {
            return side;
        }
    }
    
    throw SideNotFoundException();
}

void WhiteCross::rotate(Cube &cube) {
    string rotation;
    
    switch(matchingSide) {
        case FRONT:
            rotation = CubeAlgorithm::ROTATE_FRONT_CLOCKWISE;
            break;
        case LEFT:
            rotation = CubeAlgorithm::ROTATE_LEFT_CLOCKWISE;
            break;
        case RIGHT:
            rotation = CubeAlgorithm::ROTATE_RIGHT_CLOCKWISE;
            break;
        case BACK:
            rotation = CubeAlgorithm::ROTATE_BACK_CLOCKWISE;
            break;
        default:
            break;
    }
    
    CubeAlgorithm::doMove(cube, rotation);
    //CubeAlgorithm::doMove(cube, rotation);
}