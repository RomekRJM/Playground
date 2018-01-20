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
    DASY, WHITE_CROSS, FIRST_LAYER_CORNERS, SECOND_LAYER_EDGES, YELLOW_CROSS,
    POSITION_LAST_LAYER_CORNERS, PERMUTE_LAST_LAYER_CORNERS,
    PERMUTE_LAST_LAYER_EDGES
};

class BeginnersMethod {
public:
    BeginnersMethod();
    bool isDasyDone(Cube cube);
    bool isWhiteCrossDone(Cube cube);
    bool isStateDone(Cube cube, State state);

private:
    bool isStateDone(Cube cube, State state, Side leadingSide);
    bool checkDasy(Cube cube, Side leadingSide);
    bool checkWhiteCross(Cube cube, Side leadingSide);
};

#endif /* BEGINNERS_METHOD_HPP */

