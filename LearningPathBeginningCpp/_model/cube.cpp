/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cube.cpp
 * Author: roman.subik
 * 
 * Created on 04 December 2017, 06:57
 */

#include "cube.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

Cube::Cube() {
}

Cube::Cube(const Cube& orig) {
}

Cube::~Cube() {
}

array<array<Color, Cube::SIZE>, Cube::SIZE> Cube::copySide(Side side) {
    array<array<Color, Cube::SIZE>, Cube::SIZE> sideCopy;
    
    for(int i=0; i < SIZE; ++i) {
        copy(std::begin(cube[side][i]), std::end(cube[side][i]), std::begin(sideCopy[i]));
    }
    
    return sideCopy;
}

void Cube::rotateClockwise(Side front, Side top, Side left, 
                      Side bottom, Side right) {
    array<array<Color, SIZE>, SIZE> front_copy = copySide(front);
    
    int i, j;
    for(i=0; i<SIZE; ++i) {
        for(j=0; j<SIZE; ++j) {
            front_copy[j][SIZE-i] = cube[front][i][j];
        }
    }
    
    cube[front] = front_copy;
}

string getSideName(Side s) {
    switch(s) {
        case Side::FRONT:
            return "FRONT";
        case Side::UP:
            return "UP";
        case Side::BACK:
            return "BACK";
        case Side::DOWN:
            return "DOWN";
        case Side::RIGHT:
            return "RIGHT";
        case Side::LEFT:
            return "LEFT";
    }
}

string getColorName(Color c) {
    switch(c) {
        case Color::RED:
            return "RED";
        case Color::WHITE:
            return "WHITE";
        case Color::YELLOW:
            return "YELLOW";
        case Color::ORANGE:
            return "ORANGE";
        case Color::BLUE:
            return "BLUE";
        case Color::GREEN:
            return "GREEN";
    }
}

void Cube::printCube() {
    int s, i, j;
    
    for(s=Side::FRONT; s != Side::LEFT; ++s) {
        cout << endl << getSideName(static_cast<Side>(s)) << ":" << endl;
        
        for(i = 0; i < Cube::SIZE; ++i) {
            
            for(j = 0; j < Cube::SIZE; ++j) {
                cout << getColorName(cube[s][i][j]) << ", ";
            }
            cout << endl;
        }
    }
}

int main(int argc, char** argv) {
    Cube cube = Cube();
    cube.rotateClockwise(Side::FRONT, Side::UP, Side::LEFT, Side::DOWN, Side::RIGHT);
    cube.printCube();
    
    return 0;
}