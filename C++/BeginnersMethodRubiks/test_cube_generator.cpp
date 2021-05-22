#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "cube_generator.hpp"

BOOST_AUTO_TEST_CASE(test_from_string) {
    Cube unscrambled = CubeGenerator::unscrambled();
    Cube cube = CubeGenerator::fromString(
            "GGGGGGGGG,WWWWWWWWW,BBBBBBBBB,YYYYYYYYY,RRRRRRRRR,OOOOOOOOO"
            );
    BOOST_CHECK(cube == unscrambled);
}

BOOST_AUTO_TEST_CASE(test_from_array) {
    Cube unscrambled = CubeGenerator::unscrambled();
    Cube cube = CubeGenerator::fromArray({
        {
            {
                { // FRONT
                    {GREEN, GREEN, GREEN},
                    {GREEN, GREEN, GREEN},
                    {GREEN, GREEN, GREEN}
                }
            },
            {
                { // UP
                    {WHITE, WHITE, WHITE},
                    {WHITE, WHITE, WHITE},
                    {WHITE, WHITE, WHITE}
                }
            },
            {
                { // BACK
                    {BLUE, BLUE, BLUE},
                    {BLUE, BLUE, BLUE},
                    {BLUE, BLUE, BLUE}
                }
            },
            {
                { // DOWN
                    {YELLOW, YELLOW, YELLOW},
                    {YELLOW, YELLOW, YELLOW},
                    {YELLOW, YELLOW, YELLOW}
                }
            },
            {
                { // RIGHT
                    {RED, RED, RED},
                    {RED, RED, RED},
                    {RED, RED, RED}
                }
            },
            {
                { // LEFT
                    {ORANGE, ORANGE, ORANGE},
                    {ORANGE, ORANGE, ORANGE},
                    {ORANGE, ORANGE, ORANGE}
                }
            }
        }
    }
    );
    BOOST_CHECK(cube == unscrambled);
}
