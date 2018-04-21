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

#include <array>
#include <string>
#include <sstream>
#include <exception>
#include <vector>
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

class Cublet {
    
protected:    
    Cublet(CubePosition c1, CubePosition c2) : pieces({c1, c2}) {
    };

    Cublet(CubePosition c1, CubePosition c2, CubePosition c3) : pieces({c1, c2, c3}) {
    };
    
public: 
    int countFullyMatchedSides(Cube cube) const;
    int countPartiallyMatchedSides(Cube cube) const;
    bool hasColorOnAnySide(Color color, Cube cube) const;
    vector<Color> getColors(Cube cube) const;
    CubePosition getCubePosition(Side side) const;
    
protected:
    const vector<CubePosition> pieces;
};

class Corner : public Cublet {
public:
    Corner(CubePosition c1, CubePosition c2, CubePosition c3) : Cublet(c1, c2, c3) {
    };
};

const array<Corner, 4> UPPER_CORNERS = {
    Corner(CubePosition(RIGHT, 0, 0), CubePosition(UP, 2, 2), CubePosition(FRONT, 0, 2)),
    Corner(CubePosition(BACK, 0, 0), CubePosition(UP, 0, 2), CubePosition(RIGHT, 0, 2)),
    Corner(CubePosition(LEFT, 0, 0), CubePosition(UP, 0, 0), CubePosition(BACK, 0, 2)),
    Corner(CubePosition(FRONT, 0, 0), CubePosition(UP, 2, 0), CubePosition(LEFT, 0, 2)),
};

const array<Corner, 4> LOWER_CORNERS = {
    Corner(CubePosition(RIGHT, 2, 0), CubePosition(DOWN, 0, 2), CubePosition(FRONT, 2, 2)),
    Corner(CubePosition(BACK, 2, 0), CubePosition(DOWN, 2, 2), CubePosition(RIGHT, 2, 2)),
    Corner(CubePosition(LEFT, 2, 0), CubePosition(DOWN, 2, 0), CubePosition(BACK, 2, 2)),
    Corner(CubePosition(FRONT, 2, 0), CubePosition(DOWN, 0, 0), CubePosition(LEFT, 2, 2)),
};

class Edge : public Cublet {
public:
    Edge(CubePosition c1, CubePosition c2) : Cublet(c1, c2) {
    };
};

const Edge THIRD_LAYER_FRONT_EDGE = Edge(CubePosition(FRONT, 0, 1), CubePosition(UP, 2, 1));
const Edge SECOND_LAYER_LEFT_EDGE = Edge(CubePosition(LEFT, 1, 2), CubePosition(FRONT, 1, 0));
const Edge SECOND_LAYER_RIGHT_EDGE = Edge(CubePosition(RIGHT, 1, 0), CubePosition(FRONT, 1, 2));

class CubeAlgorithm {
public:

    CubeAlgorithm() {
    };

    string perform(Cube & cube);

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

    static const vector<string> RIGHTY;
    static const vector<string> LEFTY;

private:
    string getMovesAsString();
    static const map<string, Rotation> rotations;
    static const map<string, Flip> flips;
    stringstream ss;
    bool initialPositionSet = false;

protected:

    virtual void findPositionBeforeRotation(Cube &cube) {
    };

    virtual void findInitialPosition(Cube &cube) {
    };
    virtual void rotate(Cube &cube) = 0;
    void doMove(Cube &cube, string move);
    void doMoves(Cube &cube, vector<string> moves);
};

class Dasy : public CubeAlgorithm {
    void rotate(Cube &cube) override;
private:
    const PetalSolution* nextMissingWhiteEdge(Cube cube);
    static const array<CubePosition, 4> WHITE_PETALS;
    static const array<PetalSolution, 20> PETAL_SOLUTIONS;
};

class WhiteCross : public CubeAlgorithm {
    void findPositionBeforeRotation(Cube &cube) override;
    void rotate(Cube &cube) override;
private:
    Side matchingSide;
    Side findMatchingSide(Cube cube);
};

class FirstLayerCorners : public CubeAlgorithm {
    void findPositionBeforeRotation(Cube &cube) override;
    void rotate(Cube &cube) override;
private:
    bool isCandidateForSwap(Corner corner, Cube cube);
};

class SecondLayerEdges : public CubeAlgorithm {
    void findPositionBeforeRotation(Cube &cube) override;
    void rotate(Cube &cube) override;
private:
    enum Swap {
        NOTHING, LEFT_FRONT_EDGE, RIGHT_FRONT_EDGE
    };
    Swap findSwap(Cube cube);
    bool sideSolved(Cube cube);
    Swap currentSwap;
};

class YellowDot : public CubeAlgorithm {
    void rotate(Cube &cube) override;
};

class YellowLine : public CubeAlgorithm {
    void findInitialPosition(Cube &cube) override;
    void rotate(Cube &cube) override;
private:
    bool isYellowLine(Cube cube);
};

class YellowArc : public CubeAlgorithm {
    void findInitialPosition(Cube &cube) override;
    void rotate(Cube &cube) override;
private:
    bool isYellowArc(Cube cube);
};

class SideNotFoundException : public exception {

    virtual const char* what() const throw () {
        return "Couldn't find matching side";
    }
};
#endif /* CUBE_ALGORITHMS_HPP */
