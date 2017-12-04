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

class Cube {
public:
    Cube();
    Cube(const Cube& orig);
    virtual ~Cube();
private:
    array<array<array<array <Color>, 3>, 3>, 9> cube = 
    {
        {
            {WHITE, WHITE, WHITE},
            {WHITE, WHITE, WHITE},
            {WHITE, WHITE, WHITE}
        },
        {
            {GREEN, GREEN, GREEN},
            {GREEN, GREEN, GREEN},
            {GREEN, GREEN, GREEN}
        },
        {
            {YELLOW, YELLOW, YELLOW},
            {YELLOW, YELLOW, YELLOW},
            {YELLOW, YELLOW, YELLOW}
        },
        {
            {BLUE, BLUE, BLUE},
            {BLUE, BLUE, BLUE},
            {BLUE, BLUE, BLUE}
        },
        {
            {ORANGE, ORANGE, ORANGE},
            {ORANGE, ORANGE, ORANGE},
            {ORANGE, ORANGE, ORANGE}
        },
        {
            {RED, RED, RED},
            {RED, RED, RED},
            {RED, RED, RED}
        }
    };
};

class Rotation {
    
};

enum Color {
    WHITE, RED, YELLOW, GREEN, ORANGE, BLUE
};

enum Direction {
    FRONT, UP, BACK, DOWN, RIGHT, LEFT
};

#endif /* CUBE_H */

