/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   cube.h
 * Author: roman.subik
 *
 * Created on 04 December 2017, 06:57
 */

#ifndef CUBE_H
#define CUBE_H

#include <stdlib.h>
#include <stdexcept>
#include <array>
#include <map>
#include <set>

using namespace std;

enum Color {
    RED, WHITE, YELLOW, ORANGE, BLUE, GREEN
};

string getColorName(Color c);

enum Side {
    FRONT, UP, BACK, DOWN, RIGHT, LEFT
};

//map<Side, array<Side> neighbours;

string getSideName(Side s);

enum Rotation {
    FRONT_CLOCKWISE, UP_CLOCKWISE, BACK_CLOCKWISE, DOWN_CLOCKWISE,
    RIGHT_CLOCKWISE, LEFT_CLOCKWISE, FRONT_COUNTER_CLOCKWISE,
    UP_COUNTER_CLOCKWISE, BACK_COUNTER_CLOCKWISE, DOWN_COUNTER_CLOCKWISE,
    RIGHT_COUNTER_CLOCKWISE, LEFT_COUNTER_CLOCKWISE
};

enum Flip {
    Y_CLOCKWISE_90, Y_COUNTER_CLOCKWISE_90,
    X_CLOCKWISE_90, X_COUNTER_CLOCKWISE_90,
    Z_CLOCKWISE_90, Z_COUNTER_CLOCKWISE_90,
    UPSIDE_DOWN
};

template<typename T, typename U>
void executeFunctionFromMap(T key, map<T, U> _map) {
    auto iter = _map.find(key);
    if (iter != end(_map)) {
        iter->second();
    }
}

template<typename K, typename V>
V findInMap(K key, map<K, V> _map) {
    auto iter = _map.find(key);
    if (iter != end(_map)) {
        return iter->second;
    }

    throw domain_error("Key not found in map.");
}

class Cube {
    friend class BeginnersMethod;

public:
    Cube();
    Cube(const Cube& orig);
    virtual ~Cube();

    static const int SIZE = 3;
    static const int SIDES = 6;

    map<Rotation, function<void() >> rotations;

    void rotate(Rotation rotation) {
        return executeFunctionFromMap(rotation, rotations);
    }

    map<Flip, function<void() >> flips;

    void flip(Flip flip) {
        return executeFunctionFromMap(flip, flips);
    }

    map<Side, set<Side>> neighbours;

    set<Side> getNeighbours(Side side) {
        return findInMap(side, neighbours);
    }

    void printCube();
    void printCubeSide(array<array<Color, SIZE>, SIZE> side);
private:
    void setUpRotations();
    void setUpFlips();
    void setUpNeighbours();
    void rotateSideClockwise(Side front);
    void rotateSideCounterClockwise(Side front);
    void rotateSidesClockwiseForFront();
    void rotateSidesClockwiseForBack();
    void rotateSidesClockwiseFrontBack(Side side);
    void rotateSidesClockwiseForUp();
    void rotateSidesClockwiseForDown();
    void rotateSidesClockwiseUpDown(Side side);
    void rotateSidesClockwiseForLeft();
    void rotateSidesClockwiseForRight();
    void rotateSidesClockwiseLeftOrCounterClockwiseRight(Side side);
    void flipSidesClockwiseOverX();
    void flipSidesClockwiseOverY();
    void flipSidesClockwiseOverZ();
    void replaceSide(Side side, array<array<Color, Cube::SIZE>, Cube::SIZE> sideValue);


    array<array<Color, Cube::SIZE>, Cube::SIZE> copySide(Side side);
    array<array<array<Color, SIZE>, SIZE>, SIDES> cube = {
        {
            {
                { // FRONT
                    {ORANGE, ORANGE, RED},
                    {ORANGE, ORANGE, ORANGE},
                    {ORANGE, ORANGE, ORANGE}
                }
            },
            {
                { // UP
                    {BLUE, BLUE, GREEN},
                    {BLUE, BLUE, WHITE},
                    {BLUE, BLUE, WHITE}
                }
            },
            {
                { // BACK
                    {BLUE, GREEN, GREEN},
                    {BLUE, GREEN, GREEN},
                    {BLUE, GREEN, GREEN}
                }
            },
            {
                { // DOWN
                    {RED, RED, RED},
                    {RED, RED, RED},
                    {RED, RED, RED}
                }
            },
            {
                { // RIGHT
                    {BLUE, RED, WHITE},
                    {YELLOW, YELLOW, YELLOW},
                    {RED, YELLOW, RED}
                }
            },
            {
                { // LEFT
                    {WHITE, WHITE, WHITE},
                    {WHITE, WHITE, WHITE},
                    {WHITE, WHITE, WHITE}
                }
            }
        }
    };
};


#endif /* CUBE_H */

