#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "cube_generator.hpp"

BOOST_AUTO_TEST_CASE(test_from_string) {
    Cube unscrambled = CubeGenerator::unscrambled();
    Cube cube = CubeGenerator::fromString(
            "OOOOOOOOO,WWWWWWWWW,RRRRRRRRR,YYYYYYYYY,BBBBBBBBB,GGGGGGGG"
            );
    BOOST_CHECK(cube == unscrambled);
}

BOOST_AUTO_TEST_CASE(test_from_array) {
    Cube unscrambled = CubeGenerator::unscrambled();
    Cube cube = CubeGenerator::fromArray({
        {
            {
                { // FRONT
                    {ORANGE, ORANGE, ORANGE},
                    {ORANGE, ORANGE, ORANGE},
                    {ORANGE, ORANGE, ORANGE}
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
                    {RED, RED, RED},
                    {RED, RED, RED},
                    {RED, RED, RED}
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
                    {BLUE, BLUE, BLUE},
                    {BLUE, BLUE, BLUE},
                    {BLUE, BLUE, BLUE}
                }
            },
            {
                { // LEFT
                    {GREEN, GREEN, GREEN},
                    {GREEN, GREEN, GREEN},
                    {GREEN, GREEN, GREEN}
                }
            }
        }
    }
    );
    BOOST_CHECK(cube == unscrambled);
}
