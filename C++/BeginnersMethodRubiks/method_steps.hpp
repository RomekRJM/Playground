/* 
 * File:   beginners_method.hpp
 * Author: roman.subik
 *
 * Created on 16 January 2018, 22:31
 */

#ifndef METHOD_STEPS_HPP
#define METHOD_STEPS_HPP

#include "cube.hpp"
#include "cube_logging.hpp"

enum State {
    DASY, WHITE_CROSS, FIRST_LAYER_CORNERS, SECOND_LAYER_EDGES, 
    YELLOW_DOT, YELLOW_LINE, YELLOW_ARC,
    YELLOW_CROSS, POSITION_LAST_LAYER_CORNERS, PERMUTE_LAST_LAYER_CORNERS,
    POSITION_LAST_LAYER_EDGES
};

class MethodSteps {
public:
    MethodSteps() {};
    bool isDasyDone(Cube &cube);
    bool isWhiteCrossDone(Cube &cube);
    bool areFirstLayerCornersDone(Cube &cube);
    bool areSecondLayerEdgesDone(Cube &cube);
    bool isYellowDotDone(Cube &cube);
    bool isYellowLineDone(Cube &cube);
    bool isYellowArcDone(Cube &cube);
    bool isYellowCrossDone(Cube &cube);
    bool areLastLayerCornersPositioned(Cube &cube);
    bool areLastLayerCornersPermuted(Cube &cube);
    bool isSolved(Cube &cube);
    bool isStateDone(Cube &cube, State state);

private:
    bool checkDasy(Cube &cube);
    bool checkWhiteCross(Cube &cube);
    bool checkFirstLayerCorners(Cube &cube);
    bool checkSecondLayerEdges(Cube &cube);
    bool checkYellowDot(Cube &cube);
    bool checkYellowLine(Cube &cube);
    bool checkYellowArc(Cube &cube);
    bool checkYellowCross(Cube &cube);
    bool checkLastLayerCornersPosition(Cube &cube);
    bool checkLastLayerCornersPermutation(Cube &cube);
    bool checkSolved(Cube &cube);
    bool checkConditionOnManyAngles(Cube &cube, Flip flip, int maxFlips, function<bool(Cube&)> condition);
    bool hasLowerT(Cube &cube, Side leadingSide);
    bool hasSecondLayerEdgesPositioned(Cube &cube, Side leadingSide);
    bool colorsMatchInAnyOrder(array<Color, 3> a1, array<Color, 3> a2);
    bool hasRightColorUnderPetals(Cube &cube);
};

#endif /* METHOD_STEPS_HPP */
