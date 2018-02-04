/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   beginners_method.cpp
 * Author: roman.subik
 * 
 * Created on 16 January 2018, 22:49
 */

#include "beginners_method.hpp"
#include <iostream>

using namespace std;

BeginnersMethod::BeginnersMethod() {

}

bool BeginnersMethod::isDasyDone(Cube &cube) {
    return isStateDone(cube, State::DASY);
}

bool BeginnersMethod::isWhiteCrossDone(Cube &cube) {
    return isStateDone(cube, State::WHITE_CROSS);
}

bool BeginnersMethod::areFirstLayerCornersDone(Cube &cube) {
    return isStateDone(cube, State::FIRST_LAYER_CORNERS);
}

bool BeginnersMethod::areSecondLayerEdgesDone(Cube &cube) {
    return isStateDone(cube, State::SECOND_LAYER_EDGES);
}

bool BeginnersMethod::isYellowDotDone(Cube &cube) {
    return isStateDone(cube, State::YELLOW_DOT);
};

bool BeginnersMethod::isStateDone(Cube &cube, State state) {
    switch (state) {
        case DASY:
            ensureColorOnTop(cube, YELLOW);
            return checkDasy(cube);
        case WHITE_CROSS:
            ensureColorOnTop(cube, WHITE);
            return checkWhiteCross(cube);
        case FIRST_LAYER_CORNERS:
            ensureColorOnTop(cube, YELLOW);
            return checkFirstLayerCorners(cube);
        case SECOND_LAYER_EDGES:
            ensureColorOnTop(cube, YELLOW);
            return checkSecondLayerEdges(cube);
        case YELLOW_DOT:
            ensureColorOnTop(cube, YELLOW);
            return checkYellowDot(cube);
        default:
            return false;
    }
};

bool BeginnersMethod::checkDasy(Cube &cube) {
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[UP];

    return (side[1][1] == YELLOW) &&
            (side[0][1] == side[1][0] == side[1][2] == WHITE);
}

bool BeginnersMethod::checkWhiteCross(Cube &cube) {
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[UP];

    return side[1][1] == side[0][1] == side[1][0] == side[1][2] ==
            side[2][1] == WHITE;
}

bool BeginnersMethod::checkFirstLayerCorners(Cube &cube) {
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[DOWN];

    if (getSideLeadingColor(cube, DOWN) != WHITE)
        return false;

    if (!isSideCompleted(cube, DOWN))
        return false;

    array<Side, 4> sides = {LEFT, FRONT, RIGHT, BACK};
    for (Side neighbour : sides) {
        if (!hasLowerT(cube, neighbour))
            return false;
    }

    return true;
}

bool BeginnersMethod::checkSecondLayerEdges(Cube &cube) {
    if (!checkFirstLayerCorners(cube)) {
        return false;
    }
    
    array<Side, 4> sides = {LEFT, FRONT, RIGHT, BACK};
    for (Side side : sides) {
        if (!hasSecondLayerEdgesPositioned(cube, side)) {
            return false;
        }
    }
    
    return true;
}

bool BeginnersMethod::checkYellowDot(Cube &cube) {
    if (!checkSecondLayerEdges(cube)) {
        return false;
    }
    
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[UP];

    return side[1][1] == YELLOW;
}

bool BeginnersMethod::isSideCompleted(Cube &cube, Side leadingSide) {
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[leadingSide];
    Color correct = side[Cube::SIZE - 1][Cube::SIZE - 1];

    for (int i = 0; i < Cube::SIZE; ++i) {
        for (int j = 0; j < Cube::SIZE; ++j) {
            if (side[i][j] != correct) {
                return false;
            }
        }
    }

    return true;
}

bool BeginnersMethod::hasLowerT(Cube &cube, Side leadingSide) {
    Color correct = getSideLeadingColor(cube, leadingSide);
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[leadingSide];
    if ((side[1][1] == side[2][0]) && (side[1][1] == side[2][1]) &&
        (side[1][1] == side[2][2]) && (side[1][1] == correct)) {
        return true;
    }
    
    return false;
}

bool BeginnersMethod::hasSecondLayerEdgesPositioned(Cube &cube, Side leadingSide) {
    Color correct = getSideLeadingColor(cube, leadingSide);
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[leadingSide];
    if ((side[1][2] == side[1][0]) and (side[1][2] == correct)) {
        return true;
    }

    return false;
}

void BeginnersMethod::ensureColorOnTop(Cube &cube, Color color) {
    Side leadingSide = FRONT;

    for (int sideNum = FRONT; sideNum <= LEFT; ++sideNum) {
        Side currentSide = static_cast<Side> (sideNum);
        if (getSideLeadingColor(cube, currentSide) == color) {
            leadingSide = currentSide;
            break;
        }
    }
    
    switch(leadingSide) {
        case UP:
            cout << "Doing nothing, color on top already" << endl;
            break;
        case DOWN:
            cout << "Filipping upside down." << endl;
            cube.flip(UPSIDE_DOWN);
            break;
        case FRONT:
            cout << "Filipping X_CLOCKWISE_90." << endl;
            cube.flip(X_CLOCKWISE_90);
            break;
        case BACK:
            cout << "Filipping X_COUNTER_CLOCKWISE_90." << endl;
            cube.flip(X_COUNTER_CLOCKWISE_90);
            break;
        case RIGHT:
            cout << "Filipping Z_COUNTER_CLOCKWISE_90." << endl;
            cube.flip(Z_COUNTER_CLOCKWISE_90);
            break;
        case LEFT:
            cout << "Filipping Z_CLOCKWISE_90." << endl;
            cube.flip(Z_CLOCKWISE_90);
            break;
    }
}

Color BeginnersMethod::getSideLeadingColor(Cube &cube, Side leadingSide) {
    return cube.cube[leadingSide][Cube::SIZE - 2][Cube::SIZE - 2];
}

int main(int argc, char** argv) {
    Cube cube = Cube();
    //cube.rotate(Rotation::UP_CLOCKWISE);
    //cube.flip(Flip::UPSIDE_DOWN);
    //cube.printCube();

    BeginnersMethod beginnersMethod = BeginnersMethod();
    //beginnersMethod.ensureColorOnTop(cube, RED);
    cout << beginnersMethod.isYellowDotDone(cube);
    cube.printCube();

    return 0;
}