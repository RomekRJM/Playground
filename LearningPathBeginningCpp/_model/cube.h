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

using namespace std;

enum Color {
    RED, WHITE, YELLOW, ORANGE, BLUE, GREEN
};

string getColorName(Color c);

enum Side {
    FRONT, UP, BACK, DOWN, RIGHT, LEFT
};

string getSideName(Side s);

class Cube {
public:
    Cube();
    Cube(const Cube& orig);
    virtual ~Cube();
    
    static const int SIZE = 3;
    static const int SIDES = 6;
    
    void rotateClockwise(Side front, Side top, Side left, 
                         Side bottom, Side right);
    void rotateCounterClockwise(Side front, Side top, Side left, 
                         Side bottom, Side right);
    
    array<array<Color, Cube::SIZE>, Cube::SIZE> copySide(Side side);
    
    void printCube();
    void printCubeSide(array<array<Color, SIZE>, SIZE> side);
private:
    void rotateFrontClockwise(Side front);
    void rotateSidesClockwise(Side top, Side left, Side bottom, Side right);
    void rotateFrontCounterClockwise(Side front);
    void rotateSidesCounterClockwise(Side top, Side left, Side bottom, Side right);
    array<array<array<Color, SIZE>, SIZE>, SIDES> cube = 
    {{
        {{
           {RED, RED, RED},
           {RED, RED, RED},
           {ORANGE, BLUE, GREEN}
        }},
        {{
           {WHITE, WHITE, WHITE},
           {WHITE, WHITE, WHITE},
           {WHITE, GREEN, ORANGE}
        }},
        {{
          {ORANGE, ORANGE, ORANGE},
          {ORANGE, ORANGE, ORANGE},
          {ORANGE, ORANGE, ORANGE}
        }},
        {{
          {ORANGE, BLUE, GREEN},
          {YELLOW, YELLOW, YELLOW},
          {YELLOW, YELLOW, YELLOW}
        }},
        {{
          {RED, BLUE, BLUE},
          {BLUE, BLUE, BLUE},
          {GREEN, BLUE, BLUE}
        }},
        {{
          {GREEN, GREEN, GREEN},
          {GREEN, GREEN, YELLOW},
          {GREEN, GREEN, RED}
        }}
     }};
};

class Rotation {
    
};

#endif /* CUBE_H */

