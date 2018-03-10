#define BOOST_TEST_DYN_LINK
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

BOOST_AUTO_TEST_CASE(test_rotate_back_clockwise) {
    rotation_test(BACK_CLOCKWISE, "WRRGGGGGG,BRROWWOWW,BBOBBOBBY,RRRYYYGOO,BBYWRYWRY,WGGWOYOOY");
}

BOOST_AUTO_TEST_CASE(test_rotate_back_counter_clockwise) {
    rotation_test(BACK_COUNTER_CLOCKWISE, "WRRGGGGGG,OOGOWWOWW,YBBOBBOBB,RRRYYYRRB,BBOWRWWRW,YGGYOYYOY");
}

BOOST_AUTO_TEST_CASE(test_rotate_down_clockwise) {
    rotation_test(DOWN_CLOCKWISE, "WRRGGGOOY,OWWOWWOWW,OOYBBBWRR,YYRYYRYYR,BBBWRRGGG,GGGOOYBBB");
}

BOOST_AUTO_TEST_CASE(test_rotate_down_counter_clockwise) {
    rotation_test(DOWN_COUNTER_CLOCKWISE, "WRRGGGWRR,OWWOWWOWW,OOYBBBOOY,RYYRYYRYY,BBBWRRBBB,GGGOOYGGG");
}

BOOST_AUTO_TEST_CASE(test_rotate_right_clockwise) {
    rotation_test(RIGHT_CLOCKWISE, "WRRGGYGGY,OWROWGOWG,WOYWBBWBB,RRBYYBYYO,WWBRRBRRB,GGGOOYOOY");
}

BOOST_AUTO_TEST_CASE(test_rotate_right_counter_clockwise) {
    rotation_test(RIGHT_COUNTER_CLOCKWISE, "WRWGGWGGW,OWBOWBOWO,YOYYBBRBB,RRRYYGYYG,BRRBRRBWW,GGGOOYOOY");
}

BOOST_AUTO_TEST_CASE(test_rotate_left_clockwise) {
    rotation_test(LEFT_CLOCKWISE, "ORROGGOGG,BWWBWWYWW,OOYBBYBBR,WRRGYYGYY,BBBWRRWRR,OOGOOGYYG");
}

BOOST_AUTO_TEST_CASE(test_rotate_left_counter_clockwise) {
    rotation_test(LEFT_COUNTER_CLOCKWISE, "RRRYGGYGG,WWWGWWGWW,OOOBBOBBO,BRRBYYYYY,BBBWRRWRR,GYYGOOGOO");
}

void flip_test(Flip flip, string expectedCube) {
    // On solved cube with white at front / geen on top do U, F, x', 2xz'
    Cube actual = CubeGenerator::fromString(
        "WRRGGGGGG,OWWOWWOWW,OOYBBBBBB,RRRYYYYYY,BBBWRRWRR,GGGOOYOOY"
    );
    actual.flip(flip);

    Cube expected = CubeGenerator::fromString(expectedCube);
    BOOST_CHECK(actual == expected);
}

BOOST_AUTO_TEST_CASE(test_flip_x_clockwise_90) {
    flip_test(X_CLOCKWISE_90, "RRRYYYYYY,WRRGGGGGG,WWOWWOWWO,BBBBBBYOO,WWBRRBRRB,GYYGOOGOO");
}

BOOST_AUTO_TEST_CASE(test_flip_x_counter_clockwise_90) {
    flip_test(X_COUNTER_CLOCKWISE_90, "OWWOWWOWW,BBBBBBYOO,YYYYYYRRR,WRRGGGGGG,BRRBRRBWW,OOGOOGYYG");
}

BOOST_AUTO_TEST_CASE(test_flip_y_clockwise_90) {
    flip_test(Y_CLOCKWISE_90, "BBBWRRWRR,OOOWWWWWW,GGGOOYOOY,RYYRYYRYY,OOYBBBBBB,WRRGGGGGG");
}

BOOST_AUTO_TEST_CASE(test_flip_y_counter_clockwise_90) {
    flip_test(Y_COUNTER_CLOCKWISE_90, "GGGOOYOOY,WWWWWWOOO,BBBWRRWRR,YYRYYRYYR,WRRGGGGGG,OOYBBBBBB");
}

BOOST_AUTO_TEST_CASE(test_flip_z_clockwise_90) {
    flip_test(Z_CLOCKWISE_90, "GGWGGRGGR,OOGOOGYYG,YBBOBBOBB,WWBRRBRRB,OOOWWWWWW,YYRYYRYYR");
}

BOOST_AUTO_TEST_CASE(test_flip_z_counter_clockwise_90) {
    flip_test(Z_COUNTER_CLOCKWISE_90, "RGGRGGWGG,BRRBRRBWW,BBOBBOBBY,GYYGOOGOO,RYYRYYRYY,WWWWWWOOO");
}

BOOST_AUTO_TEST_CASE(test_upside_down) {
    flip_test(UPSIDE_DOWN, "GGGGGGRRW,YYYYYYRRR,BBBBBBYOO,WWOWWOWWO,YOOYOOGGG,RRWRRWBBB");
}