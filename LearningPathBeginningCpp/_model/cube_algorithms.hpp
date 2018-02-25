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
#include <sstream>
#include "cube.hpp"

using namespace std;

struct PetalSolution {
public:

    PetalSolution(CubePosition s, CubePosition d, string r) :
        startingPosition(s), cantBeWhite(d), rotation(r) {
    };
    
public:
    CubePosition startingPosition;
    CubePosition cantBeWhite;
    string rotation;
};

class CubeAlgorithm {
public:

    CubeAlgorithm() {
    };

    string perform(Cube & cube) {
        findStartingPosition(cube);
        rotate(cube);
        return ss.str();
    };

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

    static const array<string, 4> RIGHTY;
    static const array<string, 4> LEFTY;

private:
    static const map<string, Rotation> rotations;
    static const map<string, Flip> flips;
    stringstream ss;
    
protected:
    virtual void findStartingPosition(Cube &cube) = 0;
    virtual void rotate(Cube &cube) = 0;
    void doMove(Cube &cube, string move);
    
};

class Dasy : public CubeAlgorithm {
    void findStartingPosition(Cube &cube) override;
    void rotate(Cube &cube) override;
private:
    const PetalSolution* nextMissingWhiteEdge(Cube cube);
    static const array<CubePosition, 4> WHITE_PETALS;
    static const array<PetalSolution, 20> PETAL_SOLUTIONS;
};

class WhiteCross : public CubeAlgorithm {
    void findStartingPosition(Cube &cube) override;
    void rotate(Cube &cube) override;
};

class FirstLayerCorners : public CubeAlgorithm {
    void findStartingPosition(Cube &cube) override;
    void rotate(Cube &cube) override;
};

#endif /* CUBE_ALGORITHMS_HPP */

