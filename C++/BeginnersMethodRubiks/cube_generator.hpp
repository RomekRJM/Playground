/* 
 * File:   cube_generator.hpp
 * Author: roman.subik
 *
 * Created on 03 March 2018, 20:36
 */

#ifndef CUBE_GENERATOR_HPP
#define CUBE_GENERATOR_HPP

#include <stdlib.h>
#include "cube.hpp"

using namespace std;

class CubeGenerator {
public:
    static Cube unscrambled();
    static Cube fromArray(array<array<array<Color, Cube::SIZE>, Cube::SIZE>, Cube::SIDES> c);
    static Cube fromRandomScramble(string &rotationsPerformed);
    static Cube fromString(string s);
};

#endif /* CUBE_GENERATOR_HPP */

