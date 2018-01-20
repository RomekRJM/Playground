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

};

bool BeginnersMethod::isDasyDone(Cube cube) {
    return isStateDone(cube, State::DASY);
};

bool BeginnersMethod::isWhiteCrossDone(Cube cube) {
    return isStateDone(cube, State::DASY);
};

bool BeginnersMethod::isStateDone(Cube cube, State state) {
    for (int sideNum = FRONT; sideNum != LEFT; ++sideNum) {
        Side leadingSide = static_cast<Side> (sideNum);
        if (isStateDone(cube, state, leadingSide)) {
            return true;
        }
    }
    return false;
};

bool BeginnersMethod::isStateDone(Cube cube, State state, Side leadingSide) {
    switch (state) {
        case DASY:
            return checkDasy(cube, leadingSide);
        case WHITE_CROSS:
            return checkWhiteCross(cube, leadingSide);
        default:
            return false;
    }
};

bool BeginnersMethod::checkDasy(Cube cube, Side leadingSide) {
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[leadingSide];
    
    return (side[1][1] == YELLOW) &&
            (side[0][1] == side[1][0] == side[1][2] == WHITE);
}

bool BeginnersMethod::checkWhiteCross(Cube cube, Side leadingSide) {
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[leadingSide];
    
    return (side[1][1] == YELLOW) &&
            (side[0][1] == side[1][0] == side[1][2] == WHITE);
}

int main(int argc, char** argv) {
    Cube cube = Cube();
    //cube.rotate(Rotation::UP_CLOCKWISE);
    cube.flip(Flip::Y_CLOCKWISE_90);
    cube.printCube();
    
    for(Side s : cube.getNeighbours(DOWN))
        cout << getSideName(s);
    //BeginnersMethod beginnersMethod = BeginnersMethod();

    //cout << beginnersMethod.isDasyDone(cube);

    return 0;
}