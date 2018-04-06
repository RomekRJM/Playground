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

#include "cube.hpp"
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <boost/algorithm/string.hpp>

using namespace std;

bool CubePosition::operator==(CubePosition &other) {
    return (side == other.side) && (row == other.row) && (column == other.column);
}

Cube::Cube() {
    setUpRotations();
    setUpFlips();
    setUpNeighbours();
}

void Cube::setUpRotations() {
    function<void() > fc = [this]() {
        rotateSideClockwise(FRONT);
        rotateSidesClockwiseForFront();
    };
    function<void() > fcc = [this]() {
        rotateSideCounterClockwise(FRONT);

        for (int i = 0; i < 3; ++i) {
            rotateSidesClockwiseForFront();
        }
    };
    rotations.insert(pair<Rotation, function<void()>>(FRONT_CLOCKWISE, fc));
    rotations.insert(pair<Rotation, function<void()>>(FRONT_COUNTER_CLOCKWISE, fcc));

    function<void() > bc = [this]() {
        rotateSideClockwise(BACK);
        rotateSidesClockwiseForBack();
    };
    function<void() > bcc = [this]() {
        rotateSideCounterClockwise(BACK);

        for (int i = 0; i < 3; ++i) {
            rotateSidesClockwiseForBack();
        }
    };
    rotations.insert(pair<Rotation, function<void()>>(BACK_CLOCKWISE, bc));
    rotations.insert(pair<Rotation, function<void()>>(BACK_COUNTER_CLOCKWISE, bcc));

    function<void() > uc = [this]() {
        rotateSideClockwise(UP);
        rotateSidesClockwiseForUp();
    };
    function<void() > ucc = [this]() {
        rotateSideCounterClockwise(UP);

        for (int i = 0; i < 3; ++i) {
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
        rotateSidesClockwiseUpDown(DOWN);
    };
    rotations.insert(pair<Rotation, function<void()>>(DOWN_CLOCKWISE, dc));
    rotations.insert(pair<Rotation, function<void()>>(DOWN_COUNTER_CLOCKWISE, dcc));

    function<void() > rc = [this]() {
        rotateSideClockwise(RIGHT);
        rotateSidesClockwiseForRight();
    };
    function<void() > rcc = [this]() {
        rotateSideCounterClockwise(RIGHT);
        rotateSidesClockwiseLeftOrCounterClockwiseRight(RIGHT);
    };
    rotations.insert(pair<Rotation, function<void()>>(RIGHT_CLOCKWISE, rc));
    rotations.insert(pair<Rotation, function<void()>>(RIGHT_COUNTER_CLOCKWISE, rcc));

    function<void() > lc = [this]() {
        rotateSideClockwise(LEFT);
        rotateSidesClockwiseForLeft();
    };
    function<void() > lcc = [this]() {
        rotateSideCounterClockwise(LEFT);

        for (int i = 0; i < 3; ++i) {
            rotateSidesClockwiseForLeft();
        }
    };
    rotations.insert(pair<Rotation, function<void()>>(LEFT_CLOCKWISE, lc));
    rotations.insert(pair<Rotation, function<void()>>(LEFT_COUNTER_CLOCKWISE, lcc));
}

void Cube::setUpFlips() {
    function<void() > xc = [this]() {
        rotateSideCounterClockwise(LEFT);
        rotateSideClockwise(RIGHT);
        flipSidesClockwiseOverX();
    };
    flips.insert(pair<Flip, function<void()>>(X_CLOCKWISE_90, xc));

    function<void() > xcc = [this]() {
        for (int i = 0; i < 3; ++i) {
            rotateSideCounterClockwise(LEFT);
            rotateSideClockwise(RIGHT);
            flipSidesClockwiseOverX();
        }
    };
    flips.insert(pair<Flip, function<void()>>(X_COUNTER_CLOCKWISE_90, xcc));

    function<void() > yc = [this]() {
        rotateSideClockwise(UP);
        rotateSideCounterClockwise(DOWN);
        flipSidesClockwiseOverY();
    };
    flips.insert(pair<Flip, function<void()>>(Y_CLOCKWISE_90, yc));

    function<void() > ycc = [this]() {
        for (int i = 0; i < 3; ++i) {
            rotateSideClockwise(UP);
            rotateSideCounterClockwise(DOWN);
            flipSidesClockwiseOverY();
        }
    };
    flips.insert(pair<Flip, function<void()>>(Y_COUNTER_CLOCKWISE_90, ycc));

    function<void() > zc = [this]() {
        rotateSideClockwise(FRONT);
        rotateSideCounterClockwise(BACK);
        flipSidesClockwiseOverZ();
    };
    flips.insert(pair<Flip, function<void()>>(Z_CLOCKWISE_90, zc));

    function<void() > zcc = [this]() {
        for (int i = 0; i < 3; ++i) {
            rotateSideClockwise(FRONT);
            rotateSideCounterClockwise(BACK);
            flipSidesClockwiseOverZ();
        }
    };
    flips.insert(pair<Flip, function<void()>>(Z_COUNTER_CLOCKWISE_90, zcc));

    function<void() > z180 = [this]() {
        for (int i = 0; i < 2; ++i) {
            rotateSideClockwise(FRONT);
            rotateSideClockwise(BACK);
            flipSidesClockwiseOverZ();
        }
    };
    flips.insert(pair<Flip, function<void()>>(UPSIDE_DOWN, z180));
}

void Cube::setUpNeighbours() {
    neighbours.insert(pair<Side, set < Side >> (FRONT, set<Side>{UP, DOWN, RIGHT, LEFT}));
    neighbours.insert(pair<Side, set < Side >> (UP, set<Side>{FRONT, BACK, RIGHT, LEFT}));
    neighbours.insert(pair<Side, set < Side >> (BACK, set<Side>{UP, DOWN, RIGHT, LEFT}));
    neighbours.insert(pair<Side, set < Side >> (DOWN, set<Side>{FRONT, BACK, RIGHT, LEFT}));
    neighbours.insert(pair<Side, set < Side >> (RIGHT, set<Side>{UP, DOWN, FRONT, BACK}));
    neighbours.insert(pair<Side, set < Side >> (LEFT, set<Side>{UP, DOWN, FRONT, BACK}));
}
// TODO: Make sure on flips code is right

void Cube::flipSidesClockwiseOverX() {
    array<array<Color, Cube::SIZE>, Cube::SIZE> side1 = copySide(Side::FRONT);
    array<array<Color, Cube::SIZE>, Cube::SIZE> side2 = copySide(Side::UP);

    replaceSide(Side::UP, side1);
    side1 = copySide(Side::BACK);
    replaceSide(Side::BACK, side2);
    side2 = copySide(Side::DOWN);
    replaceSide(Side::DOWN, side1);
    replaceSide(Side::FRONT, side2);

    for (int i = 0; i < 2; ++i) {
        rotateSideClockwise(BACK);
    }

    for (int i = 0; i < 2; ++i) {
        rotateSideClockwise(DOWN);
    }
}

void Cube::flipSidesClockwiseOverY() {
    array<array<Color, Cube::SIZE>, Cube::SIZE> side1 = copySide(Side::FRONT);
    array<array<Color, Cube::SIZE>, Cube::SIZE> side2 = copySide(Side::LEFT);

    replaceSide(Side::LEFT, side1);
    side1 = copySide(Side::BACK);
    replaceSide(Side::BACK, side2);
    side2 = copySide(Side::RIGHT);
    replaceSide(Side::RIGHT, side1);
    replaceSide(Side::FRONT, side2);
}

void Cube::flipSidesClockwiseOverZ() {
    array<array<Color, Cube::SIZE>, Cube::SIZE> side1 = copySide(Side::UP);
    array<array<Color, Cube::SIZE>, Cube::SIZE> side2 = copySide(Side::RIGHT);

    replaceSide(Side::RIGHT, side1);
    side1 = copySide(Side::DOWN);
    replaceSide(Side::DOWN, side2);
    side2 = copySide(Side::LEFT);
    replaceSide(Side::LEFT, side1);
    replaceSide(Side::UP, side2);

    rotateSideClockwise(UP);
    rotateSideClockwise(RIGHT);
    rotateSideClockwise(DOWN);
    rotateSideClockwise(LEFT);
}

void Cube::replaceSide(Side side, array<array<Color, Cube::SIZE>, Cube::SIZE> sideValue) {
    copy(&sideValue[0][0], &sideValue[0][0] + SIZE*SIZE, &cube[side][0][0]);
}

array<array<Color, Cube::SIZE>, Cube::SIZE> Cube::copySide(Side side) {
    array<array<Color, Cube::SIZE>, Cube::SIZE> sideCopy;
    copy(&cube[side][0][0], &cube[side][0][0] + SIZE*SIZE, &sideCopy[0][0]);

    return sideCopy;
}

void Cube::rotateSideClockwise(Side side) {
    array<array<Color, SIZE>, SIZE> side_copy = copySide(side);

    int i, j;
    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            side_copy[j][SIZE - i - 1] = cube[side][i][j];
        }
    }

    cube[side] = side_copy;
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
    rotateSidesClockwiseFrontBack(Side::FRONT);
}

void Cube::rotateSidesClockwiseForBack() {
    for (int i = 0; i < 3; ++i) {
        rotateSidesClockwiseFrontBack(Side::BACK);
    }
}

void Cube::rotateSidesClockwiseFrontBack(Side side) {
    int i, up_left = -1, down_right = -1;
    if (side == Side::FRONT) {
        up_left = SIZE - 1;
        down_right = 0;
    } else if (side == Side::BACK) {
        up_left = 0;
        down_right = SIZE - 1;
    }

    array<Color, SIZE> rowCopy, columnCopy;
    copy(&cube[Side::UP][up_left][0], &cube[Side::UP][up_left][0] + SIZE, &rowCopy[0]);

    for (i = 0; i < SIZE; ++i) {
        cube[Side::UP][up_left][i] = cube[Side::LEFT][SIZE - i - 1][up_left];
    }

    for (i = 0; i < SIZE; ++i) {
        columnCopy[i] = cube[Side::RIGHT][i][down_right];
        cube[Side::RIGHT][i][down_right] = rowCopy[i];
    }

    copy(&cube[Side::DOWN][down_right][0], &cube[Side::DOWN][down_right][0] + SIZE, &rowCopy[0]);

    for (i = 0; i < SIZE; ++i) {
        cube[Side::DOWN][down_right][SIZE - i - 1] = columnCopy[i];
    }

    for (i = 0; i < SIZE; ++i) {
        cube[Side::LEFT][i][up_left] = rowCopy[i];
    }
}

void Cube::rotateSidesClockwiseForUp() {
    rotateSidesClockwiseUpDown(Side::UP);
}

void Cube::rotateSidesClockwiseForDown() {
    for (int i = 0; i < 3; ++i) {
        rotateSidesClockwiseUpDown(Side::DOWN);
    }
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

void Cube::rotateSidesClockwiseForLeft() {
    rotateSidesClockwiseLeftOrCounterClockwiseRight(Side::LEFT);
}

void Cube::rotateSidesClockwiseForRight() {
    for (int i = 0; i < 3; ++i) {
        rotateSidesClockwiseLeftOrCounterClockwiseRight(Side::RIGHT);
    }
}

void Cube::rotateSidesClockwiseLeftOrCounterClockwiseRight(Side side) {
    int i, column = -1, columnBack = -1;
    if (side == Side::LEFT) {
        column = 0;
        columnBack = SIZE - 1;
    } else if (side == Side::RIGHT) {
        column = SIZE - 1;
        columnBack = 0;
    }

    array<Color, SIZE> columnCopy1, columnCopy2;

    for (i = 0; i < SIZE; ++i) {
        columnCopy1[i] = cube[Side::FRONT][i][column];
        cube[Side::FRONT][i][column] = cube[Side::UP][i][column];
    }

    for (i = 0; i < SIZE; ++i) {
        columnCopy2[i] = cube[Side::DOWN][i][column];
        cube[Side::DOWN][i][column] = columnCopy1[i];
    }

    for (i = 0; i < SIZE; ++i) {
        columnCopy1[SIZE - i - 1] = cube[Side::BACK][SIZE - i - 1][columnBack];
        cube[Side::BACK][SIZE - i - 1][columnBack] = columnCopy2[i];
    }

    for (i = 0; i < SIZE; ++i) {
        cube[Side::UP][SIZE - i - 1][column] = columnCopy1[i];
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
    for (int s = Side::FRONT; s <= Side::LEFT; ++s) {
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

string Cube::asShortString() {
    stringstream ss;
    for (int s = Side::FRONT; s <= Side::LEFT; ++s) {
        ss << sideAsShortString(cube[s]);
        if (s != LEFT) {
            ss << ",";
        }
    }
    return ss.str();
}

string Cube::sideAsShortString(array<array<Color, SIZE>, SIZE> side) {
    stringstream ss;
    int i, j;
    for (i = 0; i < Cube::SIZE; ++i) {
        for (j = 0; j < Cube::SIZE; ++j) {
            ss << getColorName(side[i][j]);
        }
    }
    return ss.str();
}

Color Cube::getSideLeadingColor(Side leadingSide) {
    return cube[leadingSide][Cube::SIZE - 2][Cube::SIZE - 2];
}

bool Cube::operator==(Cube & other) {
    return this->cube == other.cube;
}

