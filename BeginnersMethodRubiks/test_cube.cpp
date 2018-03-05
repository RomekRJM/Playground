#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE CUBE_TEST_SUITE
#include <boost/test/unit_test.hpp>
#include "cube.hpp"
#include "cube_generator.hpp"
// FRONT, UP, BACK, DOWN, RIGHT, LEFT

void rotation_test(Rotation rotation, string expectedCube) {
    // On solved cube with white at front / geen on top do U, F, x', 2xz'
    Cube actual = CubeGenerator::fromString(
        "WRRGGGGGG,OWWOWWOWW,OOYBBBBBB,RRRYYYYYY,BBBWRRWRR,GGGOOYOOY"
    );
    actual.rotate(rotation);

    Cube expected = CubeGenerator::fromString(expectedCube);
    BOOST_CHECK(actual == expected);
}

BOOST_AUTO_TEST_CASE(test_rotate_front_clockwise) {
    rotation_test(FRONT_CLOCKWISE, "GGWGGRGGR,OWWOWWYYG,OOYBBBBBB,WWBYYYYYY,OBBWRRWRR,GGROOROOR");
}

BOOST_AUTO_TEST_CASE(test_rotate_front_counter_clockwise) {
    rotation_test(FRONT_COUNTER_CLOCKWISE, "RGGRGGWGG,OWWOWWBWW,OOYBBBBBB,GYYYYYYYY,RBBRRRRRR,GGWOOWOOO");
}

BOOST_AUTO_TEST_CASE(test_rotate_up_clockwise) {
    rotation_test(UP_CLOCKWISE, "BBBGGGGGG,OOOWWWWWW,GGGBBBBBB,RRRYYYYYY,OOYWRRWRR,WRROOYOOY");
}

BOOST_AUTO_TEST_CASE(test_rotate_up_counter_clockwise) {
    rotation_test(UP_COUNTER_CLOCKWISE, "GGGGGGGGG,WWWWWWOOO,BBBBBBBBB,RRRYYYYYY,WRRWRRWRR,OOYOOYOOY");
}