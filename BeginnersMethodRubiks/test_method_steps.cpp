#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "cube_generator.hpp"
#include "method_steps.hpp"

BOOST_AUTO_TEST_CASE(test_is_dasy_done_true) {
    Cube cube = CubeGenerator::fromString(
            "BGGGGBOOR,YWYWYWWWW,OBRBBGBRG,YYYYWYWYW,ROGOORBBO,GRRORROGB"
            );
    BOOST_CHECK(MethodSteps().isDasyDone(cube));
}

BOOST_AUTO_TEST_CASE(test_is_dasy_done_incomplete_petals) {
    Cube cube = CubeGenerator::fromString(
            "RBWGBYGOW,WYBYWBWYO,YGOWGBYRB,YWRWYGYWG,BRROOGBRR,GRGOROOBO"
            );
    BOOST_CHECK(!MethodSteps().isDasyDone(cube));
}

BOOST_AUTO_TEST_CASE(test_is_white_cross_done) {
    Cube cube = CubeGenerator::fromString(
            "OOWOORWOR,BYYYYYYBR,ROYRRGORG,GWBWWWYWB,GBBBBGWBW,ORGYGGRGO"
            );
    BOOST_CHECK(MethodSteps().isWhiteCrossDone(cube));
}

BOOST_AUTO_TEST_CASE(test_is_white_cross_done_incomplete_cross) {
    Cube cube = CubeGenerator::fromString(
            "OGBOGGRBG,YWYWYWBRR,OBRBBGBRG,BORYWYWYW,WOGWORWBO,GRYORYOGY"
            );
    BOOST_CHECK(!MethodSteps().isWhiteCrossDone(cube));
}

BOOST_AUTO_TEST_CASE(test_are_first_layer_corners_done) {
    Cube cube = CubeGenerator::fromString(
            "YRGROOOOO,RYYYYYOYY,GOYORRRRR,WWWWWWWWW,OGRBBGBBB,BBBBGGGGG"
            );
    BOOST_CHECK(MethodSteps().areFirstLayerCornersDone(cube));
}

BOOST_AUTO_TEST_CASE(test_are_first_layer_corners_done_misplaced_corner) {
    Cube cube = CubeGenerator::fromString(
            "YRWROYOOG,YYGYYOOYO,YGRORRRRR,WWOWWWWWW,BBROBGYBB,GBBBGGGGG"
            );
    BOOST_CHECK(!MethodSteps().areFirstLayerCornersDone(cube));
}

BOOST_AUTO_TEST_CASE(test_are_second_layer_edges_done) {
    Cube cube = CubeGenerator::fromString(
            "YOROOOOOO,OBYRYYOYY,RYYRRRRRR,WWWWWWWWW,GGBBBBBBB,GYBGGGGGG"
            );
    BOOST_CHECK(MethodSteps().areSecondLayerEdgesDone(cube));
}

BOOST_AUTO_TEST_CASE(test_are_second_layer_edges_done_misplaced_edge) {
    Cube cube = CubeGenerator::fromString(
            "YGOGGYGGG,YORBYYOYG,YGBBBBBBB,WWWWWWWWW,YRGOOOOOO,RYBRRRRRR"
            );
    BOOST_CHECK(!MethodSteps().areSecondLayerEdgesDone(cube));
}

BOOST_AUTO_TEST_CASE(test_is_yellow_dot_done) {
    Cube cube = CubeGenerator::fromString(
            "GYBGGGGGG,YYYBYYORO,GGBBBBBBB,WWWWWWWWW,YOROOOOOO,RYYRRRRRR"
            );
    BOOST_CHECK(MethodSteps().isYellowDotDone(cube));
}

BOOST_AUTO_TEST_CASE(test_is_yellow_dot_done_misplaced_dot) {
    Cube cube = CubeGenerator::fromString(
            "GYBGGGGGG,YYYBWYORO,GGBBBBBBB,WWWWWWWWW,YOROOOOOO,RYYRRRRRR"
            );
    BOOST_CHECK(!MethodSteps().isYellowDotDone(cube));
}

BOOST_AUTO_TEST_CASE(test_is_yellow_line_done) {
    Cube cube = CubeGenerator::fromString(
            "OYYRRRRRR,OBYYYYYOR,GYBOOOOOO,WWWWWWWWW,BGRGGGGGG,YRGBBBBBB"
            );
    BOOST_CHECK(MethodSteps().isYellowLineDone(cube));
}

BOOST_AUTO_TEST_CASE(test_is_yellow_line_done_mising_center) {
    Cube cube = CubeGenerator::fromString(
            "OYYRRRRRR,OBYYWYYOR,GYBOOOOOO,WWWWYWWWW,BGRGGGGGG,YRGBBBBBB"
            );
    BOOST_CHECK(!MethodSteps().isYellowLineDone(cube));
}

BOOST_AUTO_TEST_CASE(test_is_yellow_arc_done) {
    Cube cube = CubeGenerator::fromString(
            "GYBGGGGGG,YYYBYYORO,GGBBBBBBB,WWWWWWWWW,YOROOOOOO,RYYRRRRRR"
            );
    BOOST_CHECK(MethodSteps().isYellowArcDone(cube));
}

BOOST_AUTO_TEST_CASE(test_is_yellow_arc_done_mising_center) {
    Cube cube = CubeGenerator::fromString(
            "GYBGGGGGG,YYYBWYORO,GGBBBBBBB,WWWWWWWWW,YOROOOOOO,RYYRRRRRR"
            );
    BOOST_CHECK(!MethodSteps().isYellowArcDone(cube));
}

BOOST_AUTO_TEST_CASE(test_is_yellow_cross_done) {
    Cube cube = CubeGenerator::fromString(
            "YOOGGGGGG,RYYYYYGYY,GRYBBBBBB,WWWWWWWWW,BGROOOOOO,BBORRRRRR"
            );
    BOOST_CHECK(MethodSteps().isYellowCrossDone(cube));
}

BOOST_AUTO_TEST_CASE(test_is_yellow_cross_done_incompleted) {
    Cube cube = CubeGenerator::fromString(
            "GYBGGGGGG,YYYBYYORO,GGBBBBBBB,WWWWWWWWW,YOROOOOOO,RYYRRRRRR"
            );
    BOOST_CHECK(!MethodSteps().isYellowCrossDone(cube));
}

BOOST_AUTO_TEST_CASE(test_are_last_layer_corners_positioned) {
    Cube cube = CubeGenerator::fromString(
            "GRYGGGGGG,YYOYYYYYO,YOBBBBBBB,WWWWWWWWW,GBBOOOOOO,RGRRRRRRR"
            );
    BOOST_CHECK(MethodSteps().areLastLayerCornersPositioned(cube));
}

BOOST_AUTO_TEST_CASE(test_are_last_layer_corners_positioned_incompleted) {
    Cube cube = CubeGenerator::fromString(
            "BBOGGGGGG,YYYYYYRYG,BGRBBBBBB,WWWWWWWWW,YOOOOOOOO,GRYRRRRRR"
            );
    BOOST_CHECK(!MethodSteps().areLastLayerCornersPositioned(cube));
}

BOOST_AUTO_TEST_CASE(test_are_last_layer_corners_permuted) {
    Cube cube = CubeGenerator::fromString(
            "GRGGGGGGG,YYYYYYYYY,BOBBBBBBB,WWWWWWWWW,OBOOOOOOO,RGRRRRRRR"
            );
    BOOST_CHECK(MethodSteps().areLastLayerCornersPermuted(cube));
}

BOOST_AUTO_TEST_CASE(test_are_last_layer_corners_permuted_incompleted) {
    Cube cube = CubeGenerator::fromString(
            "GROGGGGGG,YYYYYYYYY,BOBBBBBBB,WWWWWWWWW,GBOOOOOOO,RGRRRRRRR"
            );
    BOOST_CHECK(!MethodSteps().areLastLayerCornersPermuted(cube));
}

BOOST_AUTO_TEST_CASE(test_is_solved) {
    Cube cube = CubeGenerator::fromString(
            "GGGGGGGGG,YYYYYYYYY,BBBBBBBBB,WWWWWWWWW,OOOOOOOOO,RRRRRRRRR"
            );
    BOOST_CHECK(MethodSteps().isSolved(cube));
}