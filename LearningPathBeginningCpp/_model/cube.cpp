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
    function<void() > fc = [this]() {
        rotateSideClockwise(FRONT);
        rotateSidesClockwiseForFront();
    };
    function<void() > fcc = [this]() {
        rotateSideCounterClockwise(FRONT);
        
        for(int i=0; i<3; ++i) {
            rotateSidesClockwiseForFront();
        }
    };
    rotations.insert(pair<Rotation, function<void()>>(FRONT_CLOCKWISE, fc));
    rotations.insert(pair<Rotation, function<void()>>(FRONT_COUNTER_CLOCKWISE, fcc));

    function<void() > uc = [this]() {
        rotateSideClockwise(UP);
        rotateSidesClockwiseForUp();
    };
    function<void() > ucc = [this]() {
        rotateSideCounterClockwise(UP);
        
        for(int i=0; i<3; ++i) {
            rotateSidesClockwiseForUp();
        }
    };
    rotations.insert(pair<Rotation, function<void()>>(UP_CLOCKWISE, uc));
    rotations.insert(pair<Rotation, function<void()>>(UP_COUNTER_CLOCKWISE, ucc));
    
    function<void() > dc = [this]() {
        rotateSideClockwise(DOWN);
        rotateSidesClockwiseForDown();
    };
    function<void() > dcc = [this]() {
        rotateSideCounterClockwise(DOWN);
        
        for(int i=0; i<3; ++i) {
            rotateSidesClockwiseForDown();
        }
    };
    rotations.insert(pair<Rotation, function<void()>>(DOWN_CLOCKWISE, dc));
    rotations.insert(pair<Rotation, function<void()>>(DOWN_COUNTER_CLOCKWISE, dcc));
}

Cube::Cube(const Cube& orig) {
}

Cube::~Cube() {
}

array<array<Color, Cube::SIZE>, Cube::SIZE> Cube::copySide(Side side) {
    array<array<Color, Cube::SIZE>, Cube::SIZE> sideCopy;
    copy(&cube[side][0][0], &cube[side][0][0] + SIZE*SIZE, &sideCopy[0][0]);

    return sideCopy;
}

void Cube::rotateSideClockwise(Side front) {
    array<array<Color, SIZE>, SIZE> front_copy = copySide(front);

    int i, j;
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            front_copy[j][SIZE - i - 1] = cube[front][i][j];
        }
    }

    cube[front] = front_copy;
}

void Cube::rotateSideCounterClockwise(Side front) {
    array<array<Color, SIZE>, SIZE> front_copy = copySide(front);

    int i, j;
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            front_copy[SIZE - j - 1][i] = cube[front][i][j];
        }
    }

    cube[front] = front_copy;
}

void Cube::rotateSidesClockwiseForFront() {
    int i;
    array<Color, SIZE> rowCopy, columnCopy;
    copy(&cube[Side::UP][SIZE - 1][0], &cube[Side::UP][SIZE - 1][0] + SIZE, &rowCopy[0]);

    for (i = 0; i < SIZE; ++i) {
        cube[Side::UP][SIZE - 1][i] = cube[Side::LEFT][SIZE - i - 1][SIZE - 1];
    }

    for (i = 0; i < SIZE; ++i) {
        columnCopy[i] = cube[Side::RIGHT][i][0];
        cube[Side::RIGHT][i][0] = rowCopy[i];
    }

    copy(&cube[Side::DOWN][0][0], &cube[Side::DOWN][0][0] + SIZE, &rowCopy[0]);

    for (i = 0; i < SIZE; ++i) {
        cube[Side::DOWN][0][SIZE - i - 1] = columnCopy[i];
    }

    for (i = 0; i < SIZE; ++i) {
        cube[Side::LEFT][i][SIZE - 1] = rowCopy[i];
    }
}

void Cube::rotateSidesClockwiseForUp() {
    rotateSidesClockwiseUpDown(Side::UP);
}

void Cube::rotateSidesClockwiseForDown() {
    rotateSidesClockwiseUpDown(Side::DOWN);
}

void Cube::rotateSidesClockwiseUpDown(Side side) {
    int i, row = -1;
    if (side == Side::UP) {
        row = 0;
    } else if (side == Side::DOWN) {
        row = SIZE - 1;
    }
    
    array<Color, SIZE> rowCopy, columnCopy;
    copy(&cube[Side::BACK][row][0], &cube[Side::BACK][row][0] + SIZE, &rowCopy[0]);

    for (i = 0; i < SIZE; ++i) {
        cube[Side::BACK][row][i] = cube[Side::LEFT][row][i];
    }

    for (i = 0; i < SIZE; ++i) {
        columnCopy[i] = cube[Side::RIGHT][row][i];
        cube[Side::RIGHT][row][i] = rowCopy[i];
    }

    copy(&cube[Side::FRONT][row][0], &cube[Side::FRONT][row][0] + SIZE, &rowCopy[0]);

    for (i = 0; i < SIZE; ++i) {
        cube[Side::FRONT][row][i] = columnCopy[i];
    }

    for (i = 0; i < SIZE; ++i) {
        cube[Side::LEFT][row][i] = rowCopy[i];
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
    cube.rotate(Rotation::DOWN_CLOCKWISE);
    cube.printCube();

    return 0;
}