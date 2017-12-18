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
#include <array>
#include <map>

using namespace std;

enum Color {
    RED, WHITE, YELLOW, ORANGE, BLUE, GREEN
};

string getColorName(Color c);

enum Side {
    FRONT, UP, BACK, DOWN, RIGHT, LEFT
};

string getSideName(Side s);

enum Rotation {
    FRONT_CLOCKWISE, UP_CLOCKWISE, BACK_CLOCKWISE, DOWN_CLOCKWISE, 
    RIGHT_CLOCKWISE, LEFT_CLOCKWISE, FRONT_COUNTER_CLOCKWISE, 
    UP_COUNTER_CLOCKWISE, BACK_COUNTER_CLOCKWISE, DOWN_COUNTER_CLOCKWISE, 
    RIGHT_COUNTER_CLOCKWISE, LEFT_COUNTER_CLOCKWISE
};

class Cube {
public:
    Cube();
    Cube(const Cube& orig);
    virtual ~Cube();
    
    static const int SIZE = 3;
    static const int SIDES = 6;
    
    map<Rotation, function<void()>> rotations;
    
    void rotate(Rotation rotation) {
        auto iter = rotations.find(rotation);
        if (iter != end(rotations)) {
            iter->second();
        }
    }
    
    void printCube();
    void printCubeSide(array<array<Color, SIZE>, SIZE> side);
private:
    void rotateSideClockwise(Side front);
    void rotateSideCounterClockwise(Side front);
    void rotateSidesClockwiseForFront();
    void rotateSidesClockwiseForBack();
    void rotateSidesClockwiseFrontBack(Side side);
    void rotateSidesClockwiseForUp();
    void rotateSidesClockwiseForDown();
    void rotateSidesClockwiseUpDown(Side side);
    
    array<array<Color, Cube::SIZE>, Cube::SIZE> copySide(Side side);
    array<array<array<Color, SIZE>, SIZE>, SIDES> cube = 
    {{
        {{ // FRONT
           {RED, RED, RED},
           {RED, RED, RED},
           {ORANGE, BLUE, GREEN}
        }},
        {{ // UP
           {WHITE, WHITE, WHITE},
           {WHITE, WHITE, WHITE},
           {WHITE, GREEN, ORANGE}
        }},
        {{ // BACK
          {RED, ORANGE, WHITE},
          {ORANGE, ORANGE, ORANGE},
          {ORANGE, ORANGE, ORANGE}
        }},
        {{ // DOWN
          {ORANGE, BLUE, GREEN},
          {YELLOW, YELLOW, YELLOW},
          {YELLOW, YELLOW, YELLOW}
        }},
        {{ // RIGHT
          {RED, BLUE, BLUE},
          {BLUE, BLUE, BLUE},
          {GREEN, BLUE, BLUE}
        }},
        {{ // LEFT
          {RED, YELLOW, GREEN},
          {GREEN, GREEN, YELLOW},
          {GREEN, GREEN, RED}
        }}
     }};
};


#endif /* CUBE_H */

