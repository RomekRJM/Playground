#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "cube.hpp"
#include "cube_generator.hpp"
#include "cube_algorithms.hpp"
#include <iostream>

BOOST_AUTO_TEST_CASE(test_white_cross_r) {
    Cube cube = CubeGenerator::fromString(
            "GGYRRYRRY,WWGWWRWWR,WBBWOOWOO,YYOYYOYYB,BBRBBRBBR,OOOGGGGGG"
            );
    WhiteCross whiteCross = WhiteCross();
    string s = whiteCross.perform(cube);
    BOOST_CHECK(s == "R");
}

BOOST_AUTO_TEST_CASE(test_white_cross_rr) {
    Cube cube = CubeGenerator::fromString(
            "GGORRORRB,WWYWWYWWY,RBBROOGOO,YYWYYWYYW,BBBBBBRRR,OOOGGGGGG"
            );
    WhiteCross whiteCross = WhiteCross();
    whiteCross.perform(cube);
    string s = whiteCross.perform(cube);
    BOOST_CHECK(s == "R,R");
}

BOOST_AUTO_TEST_CASE(test_white_cross_fff) {
    Cube cube = CubeGenerator::fromString(
            "RRGRRGRRG,OGGWWWWWW,BBBOOOOOO,BBRYYYYYY,WRRWBBWBB,OOYGGYGGY"
            );
    WhiteCross whiteCross = WhiteCross();
    whiteCross.perform(cube);
    whiteCross.perform(cube);
    string s = whiteCross.perform(cube);
    BOOST_CHECK(s == "F,F,F");
}

BOOST_AUTO_TEST_CASE(test_white_cross_l) {
    Cube cube = CubeGenerator::fromString(
            "YGGYRRYRR,GWWRWWRWW,BBWOOWOOW,OYYOYYBYY,RRRBBBBBB,OGGOGGOGG"
            );
    WhiteCross whiteCross = WhiteCross();
    string s = whiteCross.perform(cube);
    BOOST_CHECK(s == "L");
}

BOOST_AUTO_TEST_CASE(test_white_cross_b) {
    Cube cube = CubeGenerator::fromString(
            "GGGRRRRRR,GGOWWWWWW,BOOBOOBOO,YYYYYYBBR,RRWBBWBBW,YOOYGGYGG"
            );
    WhiteCross whiteCross = WhiteCross();
    string s = whiteCross.perform(cube);
    BOOST_CHECK(s == "B");
}