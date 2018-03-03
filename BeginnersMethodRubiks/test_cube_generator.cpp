#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SIMPLEST_TEST_SUITE
#include <boost/test/unit_test.hpp>
#include "cube_generator.hpp"

BOOST_AUTO_TEST_CASE(test_from_string)
{
    Cube unscrambled = CubeGenerator::unscrambled();
    Cube cube = CubeGenerator::fromString(
        "OOOOOOOOO,WWWWWWWWW,RRRRRRRRR,YYYYYYYYY,BBBBBBBBB,GGGGGGGGG"
    );
    BOOST_CHECK(cube == unscrambled);
}
