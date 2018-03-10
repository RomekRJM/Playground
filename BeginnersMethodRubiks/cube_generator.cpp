#include "cube_generator.hpp"
#include <stdlib.h>
#include <iostream>
#include <string.h>

using namespace std;

Cube CubeGenerator::unscrambled() {
    return Cube();
}

Cube CubeGenerator::fromArray(array<array<array<Color, SIZE>, SIZE>, SIDES> c) {
    Cube cube = Cube();
    cube.cube = c;
    return cube;
}

Cube CubeGenerator::fromRandomScramble() {
    Cube cube = Cube();
    srand((int) time(0));
    int moves = (rand() % 10) + 20;
    int i = 0;

    while (i++ < moves) {
        int r = rand() % (Rotation::LEFT_COUNTER_CLOCKWISE + 1);
        cube.rotate(static_cast<Rotation> (r));
    }

    return cube;
}

Cube CubeGenerator::fromString(string s) {
    Cube cube = Cube();
    bool skipThisLine = false;
    int side_counter = 0;
    int row = 0;
    int column = 0;
    Side side = FRONT;

    for (string::iterator it = s.begin(); it != s.end(); ++it) {
        if (*it == '#') {
            skipThisLine = true;
        } else if (*it == '\n') {
            skipThisLine = false;
        }

        if (!skipThisLine) {
            switch (*it) {
                case 'W':
                    cube.cube[side][row][column] = WHITE;
                    break;
                case 'Y':
                    cube.cube[side][row][column] = YELLOW;
                    break;
                case 'R':
                    cube.cube[side][row][column] = RED;
                    break;
                case 'G':
                    cube.cube[side][row][column] = GREEN;
                    break;
                case 'O':
                    cube.cube[side][row][column] = ORANGE;
                    break;
                case 'B':
                    cube.cube[side][row][column] = BLUE;
                    break;
                default:
                    continue;
            }

            ++column;
            if (column >= SIZE) {
                column = 0;
                ++row;
                if (row >= SIZE) {
                    row = 0;
                    ++side_counter;
                    side = static_cast<Side> (side_counter);
                }
            }
        }
    }

    return cube;
}