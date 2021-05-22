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
#include "cube_logging.hpp"

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
const Edge THIRD_LAYER_RIGHT_EDGE = Edge(CubePosition(RIGHT, 0, 1), CubePosition(UP, 1, 2));
const Edge THIRD_LAYER_BACK_EDGE = Edge(CubePosition(BACK, 0, 1), CubePosition(UP, 0, 1));
const Edge THIRD_LAYER_LEFT_EDGE = Edge(CubePosition(LEFT, 0, 1), CubePosition(UP, 1, 0));

const array<Edge, 4> UPPER_EDGES = {
    THIRD_LAYER_FRONT_EDGE,
    THIRD_LAYER_RIGHT_EDGE,
    THIRD_LAYER_BACK_EDGE,
    THIRD_LAYER_LEFT_EDGE,
};

const Edge SECOND_LAYER_LEFT_EDGE = Edge(CubePosition(LEFT, 1, 2), CubePosition(FRONT, 1, 0));
const Edge SECOND_LAYER_RIGHT_EDGE = Edge(CubePosition(RIGHT, 1, 0), CubePosition(FRONT, 1, 2));

void replaceAllInStringStream(stringstream& ss, string toBeReplaced, string replacement);

// rotation string representations
const string ROTATE_FRONT_CLOCKWISE = "F";
const string ROTATE_UP_CLOCKWISE = "U";
const string ROTATE_BACK_CLOCKWISE = "B";
const string ROTATE_DOWN_CLOCKWISE = "D";
const string ROTATE_RIGHT_CLOCKWISE = "R";
const string ROTATE_LEFT_CLOCKWISE = "L";
const string ROTATE_FRONT_COUNTER_CLOCKWISE = "F'";
const string ROTATE_UP_COUNTER_CLOCKWISE = "U'";
const string ROTATE_BACK_COUNTER_CLOCKWISE = "B'";
const string ROTATE_DOWN_COUNTER_CLOCKWISE = "D'";
const string ROTATE_RIGHT_COUNTER_CLOCKWISE = "R'";
const string ROTATE_LEFT_COUNTER_CLOCKWISE = "L'";

// flip string representations
const string FLIP_Y_CLOCKWISE_90 = "y";
const string FLIP_Y_COUNTER_CLOCKWISE_90 = "y'";
const string FLIP_X_CLOCKWISE_90 = "x";
const string FLIP_X_COUNTER_CLOCKWISE_90 = "x'";
const string FLIP_Z_CLOCKWISE_90 = "z";
const string FLIP_Z_COUNTER_CLOCKWISE_90 = "z'";
const string FLIP_UPSIDE_DOWN = "z2";

const map<string, Rotation> rotations = {
    {ROTATE_FRONT_CLOCKWISE, FRONT_CLOCKWISE},
    {ROTATE_UP_CLOCKWISE, UP_CLOCKWISE},
    {ROTATE_BACK_CLOCKWISE, BACK_CLOCKWISE},
    {ROTATE_DOWN_CLOCKWISE, DOWN_CLOCKWISE},
    {ROTATE_RIGHT_CLOCKWISE, RIGHT_CLOCKWISE},
    {ROTATE_LEFT_CLOCKWISE, LEFT_CLOCKWISE},
    {ROTATE_FRONT_COUNTER_CLOCKWISE, FRONT_COUNTER_CLOCKWISE},
    {ROTATE_UP_COUNTER_CLOCKWISE, UP_COUNTER_CLOCKWISE},
    {ROTATE_BACK_COUNTER_CLOCKWISE, BACK_COUNTER_CLOCKWISE},
    {ROTATE_DOWN_COUNTER_CLOCKWISE, DOWN_COUNTER_CLOCKWISE},
    {ROTATE_RIGHT_COUNTER_CLOCKWISE, RIGHT_COUNTER_CLOCKWISE},
    {ROTATE_LEFT_COUNTER_CLOCKWISE, LEFT_COUNTER_CLOCKWISE}
};

const map<string, Flip> flips = {
    {FLIP_Y_CLOCKWISE_90, Y_CLOCKWISE_90},
    {FLIP_Y_COUNTER_CLOCKWISE_90, Y_COUNTER_CLOCKWISE_90},
    {FLIP_X_CLOCKWISE_90, X_CLOCKWISE_90},
    {FLIP_X_COUNTER_CLOCKWISE_90, X_COUNTER_CLOCKWISE_90},
    {FLIP_Z_CLOCKWISE_90, Z_CLOCKWISE_90},
    {FLIP_Z_COUNTER_CLOCKWISE_90, Z_COUNTER_CLOCKWISE_90},
    {FLIP_UPSIDE_DOWN, UPSIDE_DOWN}
};

string toString(Rotation);

class CubeAlgorithm {
public:

    CubeAlgorithm() : colorOnTop(Color::YELLOW), invocations(0) {
    };
    
    CubeAlgorithm(Color c) : colorOnTop(c), invocations(0) {
    };

    string perform(Cube & cube);

    static const vector<string> RIGHTY;
    static const vector<string> LEFTY;

private:
    stringstream ss;
    bool initialPositionSet = false;
    Color colorOnTop;
    const int MAX_ALLOWED_INVOCATIONS = 200;
    int invocations;
    
    void ensureOnTop(Cube &cube, Color color);
    bool isStalemate();

protected:
    
    string getMovesAsString();

    virtual void findPositionBeforeRotation(Cube &cube) {
    };

    virtual void findInitialPosition(Cube &cube) {
    };
    
    virtual void shorten(stringstream &ss) {
    };
    
    virtual void rotate(Cube &cube) = 0;
    void doMove(Cube &cube, string move, bool recordInString);
    void doMoves(Cube &cube, vector<string> moves, int repeat, bool recordInString);
    void cancelLastMoves(Cube &cube, int number);
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
    enum CornerMoveType {
        EXTRACT_UNSOLVABLE_UP, PUT_SOLVABE_DOWN
    };
    bool isCandidateForSwap(Corner corner, Cube cube);
    CornerMoveType cornerMoveType;
};

class SecondLayerEdges : public CubeAlgorithm {
    void findPositionBeforeRotation(Cube &cube) override;
    void rotate(Cube &cube) override;
    void shorten(stringstream &ss) override;
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

class PositionLastLayerCorners : public CubeAlgorithm {
    void findInitialPosition(Cube &cube) override;
    void rotate(Cube &cube) override;
    void shorten(stringstream &ss) override;
public:
    PositionLastLayerCorners() : CubeAlgorithm(), alreadySolved(false) {};
private:
    array<int, 4> countUpperCornersInRightPlace(Cube cube);
    void findOptimalLastLayerRotation(Cube &cube);
    void findOptimalCubeFlip(Cube &cube);
    bool alreadySolved;
};

class PermuteLastLayerCorners : public CubeAlgorithm {
    void rotate(Cube &cube) override;
public:
    PermuteLastLayerCorners() : CubeAlgorithm(Color::WHITE) {};
private:
    void orientLowerCubletsYellowDown(Cube &cube);
    void findOptimalFirstLayerRotation(Cube &cube);
    bool hasLowerFrontRightCornerFacingYellowDown(Cube cube);
};

class PositionLastLayerEdges : public CubeAlgorithm {
    void rotate(Cube &cube) override;
private:
    int countSolvedUpperEdges(Cube cube);
    int countSolvedUpperCorners(Cube cube);
    void findOptimalLastLayerRotation(Cube &cube);
};

class SideNotFoundException : public exception {

    virtual const char* what() const throw () {
        return "Couldn't find matching side";
    }
};

class StalemateException : public exception {
    virtual const char* what() const throw () {
        return "Detected stalemate! Algorithm seems to be stuck in infinite loop.";
    }
};

#endif /* CUBE_ALGORITHMS_HPP */
