#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "cube.hpp"
#include "cube_generator.hpp"
#include "cube_algorithms.hpp"
#include <algorithm>
#include <iostream>

BOOST_AUTO_TEST_CASE(test_corner_count_partially_matched_sides) {
    Cube cube = CubeGenerator::fromString(
            "RRWYGWGGR,BYOGYBGBG,GOWYBYWBO,WWYWWGBWO,OOYOOGBRB,ROYRRBYRR"
            );
    
    BOOST_CHECK(UPPER_CORNERS[0].countPartiallyMatchedSides(cube) == 2);
    BOOST_CHECK(UPPER_CORNERS[1].countPartiallyMatchedSides(cube) == 2);
    BOOST_CHECK(UPPER_CORNERS[2].countPartiallyMatchedSides(cube) == 2);
    BOOST_CHECK(UPPER_CORNERS[3].countPartiallyMatchedSides(cube) == 3);
    
    BOOST_CHECK(LOWER_CORNERS[0].countPartiallyMatchedSides(cube) == 0);
    BOOST_CHECK(LOWER_CORNERS[1].countPartiallyMatchedSides(cube) == 3);
    BOOST_CHECK(LOWER_CORNERS[2].countPartiallyMatchedSides(cube) == 1);
    BOOST_CHECK(LOWER_CORNERS[3].countPartiallyMatchedSides(cube) == 3);
}

BOOST_AUTO_TEST_CASE(test_corner_count_fully_matched_sides) {
    Cube cube = CubeGenerator::fromString(
            "RRWYGWGGR,BYOGYBGBG,GOWYBYWBO,WWYWWGBWO,OOYOOGBRB,ROYRRBYRR"
            );
    
    BOOST_CHECK(UPPER_CORNERS[0].countFullyMatchedSides(cube) == 1);
    BOOST_CHECK(UPPER_CORNERS[1].countFullyMatchedSides(cube) == 0);
    BOOST_CHECK(UPPER_CORNERS[2].countFullyMatchedSides(cube) == 1);
    BOOST_CHECK(UPPER_CORNERS[3].countFullyMatchedSides(cube) == 0);
    
    BOOST_CHECK(LOWER_CORNERS[0].countFullyMatchedSides(cube) == 0);
    BOOST_CHECK(LOWER_CORNERS[1].countFullyMatchedSides(cube) == 0);
    BOOST_CHECK(LOWER_CORNERS[2].countFullyMatchedSides(cube) == 0);
    BOOST_CHECK(LOWER_CORNERS[3].countFullyMatchedSides(cube) == 3);
}

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

void single_first_layer_corners_test(pair<string, Cube> p) {
    string expectedMoves = p.first;
    Cube cube = p.second;

    FirstLayerCorners firstLayerCorners = FirstLayerCorners();
    string s = firstLayerCorners.perform(cube);
    BOOST_CHECK(s == expectedMoves);
}

BOOST_AUTO_TEST_CASE(test_first_layer_corners_5_rightys) {
    Cube RIGHTY_5 = CubeGenerator::fromString(
            "RRWYGWGGR,BYOGYBGBG,GOWYBYWBO,WWYWWGBWO,OOYOOGBRB,ROYRRBYRR"
            );
    
    map <string, Cube> first_layer_corner_scenarios = {
        {"R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U'", RIGHTY_5}
    };
    
    std::for_each(first_layer_corner_scenarios.begin(), 
            first_layer_corner_scenarios.end(), &single_first_layer_corners_test);
}

BOOST_AUTO_TEST_CASE(test_yellow_dot) {
    Cube cube = CubeGenerator::fromString(
            "GYBGGGGGG,YYYBYYORO,GGBBBBBBB,WWWWWWWWW,YOROOOOOO,RYYRRRRRR"
            );
    YellowDot yellowDot = YellowDot();
    string s = yellowDot.perform(cube);
    BOOST_CHECK(s == "F,R,U,R',U',F'");
}

BOOST_AUTO_TEST_CASE(test_yellow_line) {
    Cube cube = CubeGenerator::fromString(
            "GYBGGGGGG,YYYYYYORO,GGBBBBBBB,WWWWWWWWW,YOROOOOOO,RYBRRRRRR"
            );
    YellowLine yellowLine = YellowLine();
    string s = yellowLine.perform(cube);
    BOOST_CHECK(s == "F,R,U,R',U',F'");
}

BOOST_AUTO_TEST_CASE(test_yellow_line_with_initial_move) {
    Cube cube = CubeGenerator::fromString(
            "GYBGGGGGG,YYOYYRYYO,GGBBBBBBB,WWWWWWWWW,YOROOOOOO,RYBRRRRRR"
            );
    YellowLine yellowLine = YellowLine();
    string s = yellowLine.perform(cube);
    BOOST_CHECK(s == "U,F,R,U,R',U',F'");
}

BOOST_AUTO_TEST_CASE(test_yellow_arc) {
    Cube cube = CubeGenerator::fromString(
            "GYBGGGGGG,OBYRYYOYY,GGBBBBBBB,WWWWWWWWW,YOROOOOOO,RYYRRRRRR"
            );
    YellowArc yellowArc = YellowArc();
    string s = yellowArc.perform(cube);
    BOOST_CHECK(s == "z,B,R,U,R',U',B',z'");
}

BOOST_AUTO_TEST_CASE(test_yellow_arc_with_initial_move) {
    Cube cube = CubeGenerator::fromString(
            "GYBGGGGGG,YYYBYYORO,GGBBBBBBB,WWWWWWWWW,YOROOOOOO,RYYRRRRRR"
            );
    YellowArc yellowArc = YellowArc();
    string s = yellowArc.perform(cube);
    BOOST_CHECK(s == "U,z,B,R,U,R',U',B',z'");
}

void single_dasy_test(pair<string, Cube> p) {
    string expectedMoves = p.first;
    Cube cube = p.second;

    Dasy dasy = Dasy();
    string s = "";
    const string U_GROUP = "U,";
    int uCount = std::count(expectedMoves.begin(), expectedMoves.end(), 'U');
    int howManyMoves = std::count(expectedMoves.begin(), expectedMoves.end(), ',') - uCount + 1;
    int moves = 0;

    do {
        s = dasy.perform(cube) + ",";
        ++moves;
    } while (moves < howManyMoves);
    
    s = s.substr(0, s.size()-1);

    if (s != expectedMoves) {
        cout << "Expected: " << expectedMoves << " but actual: " << s << endl;
    }
    
    BOOST_CHECK(s == expectedMoves);
}

BOOST_AUTO_TEST_CASE(test_dasy) {
    Cube DOWN_EDGE_PIECE = CubeGenerator::fromString(
            "WGBRGYYRW,GWOWYWRYY,GOBGRRGRB,OWOGWYGBO,RGWBBBROY,YBBOOYWOR"
            );
    Cube FIRST_LAYER_EDGE_PIECE = CubeGenerator::fromString(
            "WGBOGYOWY,WWYWWORBW,GGGORBBRW,ROGWYROBY,GROGOGBYR,ORBYBYRBY"
            );
    Cube SECOND_LAYER_RIGHT_EDGE_PIECE = CubeGenerator::fromString(
            "YGORGBBOO,RWRWYWORG,YBWOBBRBW,YGWRWYORW,YOGOOYBGB,GGBYRWGYR"
            );
    Cube SECOND_LAYER_LEFT_EDGE_PIECE = CubeGenerator::fromString(
            "OOBBGROGY,RWRWYWWGY,YBWOBBRBW,GRORWYORW,ROGWOYBGB,GGBYROGYY"
            );
    Cube THIRD_LAYER_LEFT_EDGE_PIECE = CubeGenerator::fromString(
            "YWWYBRWYB,WWBWYBGOR,YGGGOGGYO,GRWOWWYBO,OGRBRORRY,OBBYGORRB"
            );

    map <string, Cube> dasy_scenarios = {
        // { "expected_move", cube } // begining_white_position
        {"F,F", DOWN_EDGE_PIECE}, // DOWN, 0, 1
        {"F,U,L'", FIRST_LAYER_EDGE_PIECE}, // FRONT, 2, 1
        {"F", SECOND_LAYER_RIGHT_EDGE_PIECE}, // LEFT, 1, 2
        {"F'", SECOND_LAYER_LEFT_EDGE_PIECE}, // RIGHT, 1, 0
        {"F,R", THIRD_LAYER_LEFT_EDGE_PIECE}, // FRONT, 0, 1

        {"L',L'", *DOWN_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90)}, // DOWN, 1, 0
        {"L,U,B'", *FIRST_LAYER_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90)}, // LEFT, 2, 1
        {"L", *SECOND_LAYER_RIGHT_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90)}, // BACK, 1, 2
        {"L'", *SECOND_LAYER_LEFT_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90)}, // BACK, 1, 0
        {"L,F", *THIRD_LAYER_LEFT_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90)}, // LEFT, 0, 1

        {"B,B", *DOWN_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90)}, // DOWN, 2, 1
        {"B,U,R'", *FIRST_LAYER_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90)}, // BACK, 2, 1
        {"B", *SECOND_LAYER_RIGHT_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90)}, // RIGHT, 1, 2
        {"B'", *SECOND_LAYER_LEFT_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90)}, // LEFT, 1, 0
        {"B,L", *THIRD_LAYER_LEFT_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90)}, // BACK, 0, 1

        {"R,R", *DOWN_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90)}, // DOWN, 1, 2
        {"R,U,F'", *FIRST_LAYER_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90)}, // RIGHT, 2, 1
        {"R", *SECOND_LAYER_RIGHT_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90)}, // FRONT, 1, 2
        {"R'", *SECOND_LAYER_LEFT_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90)}, // FRONT, 1, 0
        {"R,B", *THIRD_LAYER_LEFT_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90)} // RIGHT, 0, 1
    };

    std::for_each(dasy_scenarios.begin(), dasy_scenarios.end(), &single_dasy_test);
}
