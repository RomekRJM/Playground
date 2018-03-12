#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "cube_generator.hpp"
#include "method_steps.hpp"

BOOST_AUTO_TEST_CASE(test_is_dasy_done_true) {
    Cube cube = CubeGenerator::fromString(
            "BGGGGBOOR,YWYWYWWWW,OBRBBGBRG,YYYYWYWYW,ROGOORBBO,GRRORROGB"
            );
    BOOST_CHECK(BeginnersMethod().isDasyDone(cube));
}

BOOST_AUTO_TEST_CASE(test_is_dasy_done_incomplete_petals) {
    Cube cube = CubeGenerator::fromString(
            "RBWGBYGOW,WYBYWBWYO,YGOWGBYRB,YWRWYGYWG,BRROOGBRR,GRGOROOBO"
            );
    BOOST_CHECK(!BeginnersMethod().isDasyDone(cube));
}

BOOST_AUTO_TEST_CASE(test_is_dasy_done_incomplete_sides) {
    Cube cube = CubeGenerator::fromString(
            "RGOROORBO,YWWWYWYWW,OBRRROOGR,WYYYWYWYY,GOBGBBGRB,GRBBGGGOB"
            );
    BOOST_CHECK(!BeginnersMethod().isDasyDone(cube));
}

BOOST_AUTO_TEST_CASE(test_is_white_cross_done) {
    Cube cube = CubeGenerator::fromString(
            "RGOBGGRBO,WWYWWWWWY,OBRGBBOGR,YYWYYYYYW,BRGORRBOG,BOGOORBRG"
            );
    BOOST_CHECK(BeginnersMethod().isWhiteCrossDone(cube));
}

BOOST_AUTO_TEST_CASE(test_is_white_cross_done_incomplete_cross) {
    Cube cube = CubeGenerator::fromString(
            "OGBOGGRBG,YWYWYWBRR,OBRBBGBRG,BORYWYWYW,WOGWORWBO,GRYORYOGY"
            );
    BOOST_CHECK(!BeginnersMethod().isWhiteCrossDone(cube));
}

BOOST_AUTO_TEST_CASE(test_is_white_cross_done_incomplete_sides) {
    Cube cube = CubeGenerator::fromString(
            "GRRBBGBRG,YWWWYWYWW,ROGGGBOOR,WYWYWYYYY,BGGORROGB,OBROORBBO"
            );
    BOOST_CHECK(!BeginnersMethod().isWhiteCrossDone(cube));
}