/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   beginners_method.hpp
 * Author: roman.subik
 *
 * Created on 16 January 2018, 22:31
 */

#ifndef BEGINNERS_METHOD_HPP
#define BEGINNERS_METHOD_HPP

#include "cube.h"

enum State {
    DASY, WHITE_CROSS, FIRST_LAYER_CORNERS, SECOND_LAYER_EDGES, 
    YELLOW_DOT, YELLOW_LINE, YELLOW_ARC,
    YELLOW_CROSS, POSITION_LAST_LAYER_CORNERS, PERMUTE_LAST_LAYER_CORNERS,
    PERMUTE_LAST_LAYER_EDGES
};

class BeginnersMethod {
public:
    BeginnersMethod();
    bool isDasyDone(Cube &cube);
    bool isWhiteCrossDone(Cube &cube);
    bool areFirstLayerCornersDone(Cube &cube);
    bool areSecondLayerEdgesDone(Cube &cube);
    bool isYellowDotDone(Cube &cube);
    bool isYellowLineDone(Cube &cube);
    bool isStateDone(Cube &cube, State state);
    void ensureColorOnTop(Cube &cube, Color color);

private:
    bool checkDasy(Cube &cube);
    bool checkWhiteCross(Cube &cube);
    bool checkFirstLayerCorners(Cube &cube);
    bool checkSecondLayerEdges(Cube &cube);
    bool checkYellowDot(Cube &cube);
    bool checkYellowLine(Cube &cube);
    bool isSideCompleted(Cube &cube, Side leadingSide);
    Color getSideLeadingColor(Cube &cube, Side leadingSide);
    bool hasLowerT(Cube &cube, Side leadingSide);
    bool hasSecondLayerEdgesPositioned(Cube &cube, Side leadingSide);
};

#endif /* BEGINNERS_METHOD_HPP */

