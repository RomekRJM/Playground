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


Cube::Cube(const Cube& orig) {
}

Cube::~Cube() {
}

array<array<Color, Cube::SIZE>, Cube::SIZE> Cube::copySide(Side side) {
    array<array<Color, Cube::SIZE>, Cube::SIZE> sideCopy;
    copy(&cube[side][0][0], &cube[side][0][0]+SIZE*SIZE, &sideCopy[0][0]);

    return sideCopy;
}

void Cube::rotateClockwise(Side front, Side up, Side left,
        Side down, Side right) {
    rotateFrontClockwise(front);
    rotateSidesClockwise(up, left, down, right);
}

void Cube::rotateFrontClockwise(Side front) {
    array<array<Color, SIZE>, SIZE> front_copy = copySide(front);

    int i, j;
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            front_copy[j][SIZE - i - 1] = cube[front][i][j];
        }
    }

    cube[front] = front_copy;
}

void Cube::rotateSidesClockwise(Side up, Side left, Side down, Side right) {
    int i;
    array<Color, SIZE> rowCopy, columnCopy;
    copy(&cube[up][SIZE - 1][0], &cube[up][SIZE - 1][0]+SIZE, &rowCopy[0]);

    for (i = 0; i < SIZE; ++i) {
        cube[up][SIZE-1][i] = cube[left][SIZE - i - 1][SIZE - 1];
    }
    
    for (i = 0; i < SIZE; ++i) {
        columnCopy[i] = cube[right][i][0];
        cube[right][i][0] = rowCopy[i];
    }
    
    copy(&cube[down][0][0], &cube[down][0][0]+SIZE, &rowCopy[0]);
    
    for (i = 0; i < SIZE; ++i) {
        cube[down][0][SIZE - i - 1] = columnCopy[i];
    }
    
    for (i = 0; i < SIZE; ++i) {
        cube[left][i][SIZE - 1] = rowCopy[i];
    }

}

void Cube::rotateCounterClockwise(Side front, Side up, Side left,
        Side down, Side right) {
    rotateFrontCounterClockwise(front);
    rotateSidesCounterClockwise(up, left, down, right);
}

void Cube::rotateFrontCounterClockwise(Side front) {
    array<array<Color, SIZE>, SIZE> front_copy = copySide(front);

    int i, j;
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            front_copy[SIZE - j - 1][i] = cube[front][i][j];
        }
    }

    cube[front] = front_copy;
}

void Cube::rotateSidesCounterClockwise(Side up, Side left, Side down, Side right) {
    int i;
    array<Color, SIZE> rowCopy, columnCopy;
    copy(&cube[up][SIZE - 1][0], &cube[up][SIZE - 1][0]+SIZE, &rowCopy[0]);
    
    for (i = 0; i < SIZE; ++i) {
        cube[up][SIZE - 1][i] = cube[right][i][0];
    }
    
    for (i = 0; i < SIZE; ++i) {
        columnCopy[SIZE - i - 1] = cube[left][SIZE - i - 1][SIZE - 1];
        cube[left][SIZE - i - 1][SIZE - 1] = rowCopy[i];
    }
    
    copy(&cube[down][0][0], &cube[down][0][0]+SIZE, &rowCopy[0]);
    
    for (i = 0; i < SIZE; ++i) {
        cube[down][0][i] = columnCopy[i];
    }
    
    for (i = 0; i < SIZE; ++i) {
        cube[right][SIZE - i - 1][0] = rowCopy[i];
    }
}

string getSideName(Side s) {
    switch (s) {
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
    switch (c) {
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

    for (s = Side::FRONT; s <= Side::LEFT; ++s) {
        cout << endl << getSideName(static_cast<Side> (s)) << ":" << endl;
        printCubeSide(cube[s]);
    }
}

void Cube::printCubeSide(array<array<Color, SIZE>, SIZE> side) {
    int i, j;
    for (i = 0; i < Cube::SIZE; ++i) {
        for (j = 0; j < Cube::SIZE; ++j) {
            cout << getColorName(side[i][j]) << ", ";
        }
        cout << endl;
    }
}

int main(int argc, char** argv) {
    Cube cube = Cube();
    //cube.rotateCounterClockwise(Side::FRONT, Side::UP, Side::LEFT, Side::DOWN, Side::RIGHT);
    cube.rotate(Rotation::UP_CLOCKWISE);
    cube.printCube();

    return 0;
}