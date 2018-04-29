#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "cube.hpp"
#include "cube_generator.hpp"
#include "cube_algorithms.hpp"
#include <algorithm>
#include <iostream>

struct CubeTest {
public:

    CubeTest(Cube c,
            CubeAlgorithm* a,
            string em,
            int ar = 1) : cube(c), algorithm(a), expectedMoves(em), algorithmRuns(ar) {
    };

    Cube cube;
    CubeAlgorithm* algorithm;
    string expectedMoves;
    int algorithmRuns;
};

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

    s = s.substr(0, s.size() - 1);

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

void single_algorithm_test(pair<string, Cube> p, CubeAlgorithm* algorithm) {
    string expectedMoves = p.first;
    Cube cube = p.second;

    string s = algorithm->perform(cube);

    if (s != expectedMoves) {
        cout << "Expected: " << expectedMoves << " but actual: " << s << endl;
    }

    BOOST_CHECK(s == expectedMoves);
}

void single_first_layer_corners_test(pair<string, Cube> p) {
    FirstLayerCorners* firstLayerCorners = new FirstLayerCorners();
    single_algorithm_test(p, firstLayerCorners);
    delete firstLayerCorners;
}

void single_second_layer_edges_test(pair<string, Cube> p) {
    SecondLayerEdges* secondLayerEdges = new SecondLayerEdges();
    single_algorithm_test(p, secondLayerEdges);
    delete secondLayerEdges;
}

void single_algorithm_test(CubeTest test) {
    string s = "";
    
    for (int i = 0; i < test.algorithmRuns; ++i) {
        s = test.algorithm->perform(test.cube);
        
        if (i < test.algorithmRuns - 1) {
            s += ",";
        }
    }

    if (s != test.expectedMoves) {
        cout << "Expected: " << test.expectedMoves << " but actual: " << s << endl;
    }

    BOOST_CHECK(s == test.expectedMoves);
}

BOOST_AUTO_TEST_CASE(test_first_layer_corners_5_rightys) {
    Cube RIGHTY = CubeGenerator::fromString(
            "YORRRYWRG,OBGOYYRGG,YOBRORBOB,OWWWWWRWR,WBOGGYOGW,YYGGBBYBB"
            );
    Cube RIGHTY_3 = CubeGenerator::fromString(
            "RRORGGBGO,BYRYYRBYW,YGRBBYGBR,WWBWWWWWY,GGGOOOYOO,YBWORBGRO"
            );
    Cube RIGHTY_5 = CubeGenerator::fromString(
            "RRWYGWGGR,BYOGYBGBG,GOWYBYWBO,WWYWWGBWO,OOYOOGBRB,ROYRRBYRR"
            );
    Cube YCLOCKWISE_UP_3_RIGHTY_5 = CubeGenerator::fromString(
            "YOWRRBWRR,GYYOYYRGG,BBORORBOB,OWWWWWRWR,OGOOGYGGW,YYGGBBYBB"
            );
    Cube RIGHTY_2 = CubeGenerator::fromString(
            "YORGOBOOB,OYGOYRRGB,YRBBRBRRR,WWOWWWWWW,YGORBYWBB,YYGOGYGGG"
            );

    map <string, Cube> first_layer_corner_scenarios = {
        {"R,U,R',U'", RIGHTY},
        {"R,U,R',U',R,U,R',U',R,U,R',U'", RIGHTY_3},
        {"R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U'", RIGHTY_5},
        {"y,U,U,U,R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U'", YCLOCKWISE_UP_3_RIGHTY_5},
        {"R,U,R',U',R,U,R',U'", RIGHTY_2},
    };

    std::for_each(first_layer_corner_scenarios.begin(),
            first_layer_corner_scenarios.end(), &single_first_layer_corners_test);
}

BOOST_AUTO_TEST_CASE(test_second_layer_edges) {
    Cube TO_THE_RIGHT = CubeGenerator::fromString(
            "YRBRRRRRR,OBYOYOOGY,GYYOOYOOO,WWWWWWWWW,RBRYGGGGG,GYBGBBBBB"
            );
    Cube TO_THE_LEFT = CubeGenerator::fromString(
            "YBOBBRBBB,YOOBYYROY,GGBGGYGGG,WWWWWWWWW,BGYYRRRRR,RRGOOYOOO"
            );
    Cube Y3_UP_TO_THE_LEFT = CubeGenerator::fromString(
            "RBGRRRRRR,YRYBYYYOY,GYOOOYOOO,WWWWWWWWW,OORGGGGGG,BYBGBBBBB"
            );
    Cube RIGHT_IN_PLACE_BUT_TWISTED = CubeGenerator::fromString(
            "GROBBRBBB,OYBGYBYGY,YOYRGGGGG,WWWWWWWWW,BORBRYRRR,GYROOYOOO"
            );

    map <string, Cube> second_layer_edges_scenarios = {
        {"U,R,U,R',U',y,L',U',L,U", TO_THE_RIGHT},
        {"U',L',U',L,U,y',R,U,R',U'", TO_THE_LEFT},
        {"y,y,U',L',U',L,U,y',R,U,R',U'", Y3_UP_TO_THE_LEFT},
        {"U,R,U,R',U',y,L',U',L,U", RIGHT_IN_PLACE_BUT_TWISTED},
    };

    std::for_each(second_layer_edges_scenarios.begin(),
            second_layer_edges_scenarios.end(), &single_second_layer_edges_test);
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

BOOST_AUTO_TEST_CASE(test_position_last_layer_corner) {
    Cube FLIP_Y_THEN_ALG = CubeGenerator::fromString(
            "OROOOOOOO,YYYYYYYYY,GGBRRRRRR,WWWWWWWWW,BORBBBBBB,RBGGGGGGG"
            );
    Cube ALG_TWICE = CubeGenerator::fromString(
            "YGBRRRRRR,RYYYYYBYO,ORGOOOOOO,WWWWWWWWW,YBGGGGGGG,YORBBBBBB"
            );
    Cube UP_TRIPLE_THEN_ALG_TWICE = CubeGenerator::fromString(
            "YGBBBBBBB,RYYYYYBYO,ORGGGGGGG,WWWWWWWWW,YBGRRRRRR,YOROOOOOO"
            );
    
    vector<CubeTest> position_last_layer_corner_scenarios = {
        CubeTest(FLIP_Y_THEN_ALG, new PositionLayerCorners(),
            "y,R,U,R',U',R,U,R',U',R,U,R',U',y,L',U',L,U,L',U',L,U,L',U',L,U"),
        CubeTest(ALG_TWICE, new PositionLayerCorners(),
            "R,U,R',U',R,U,R',U',R,U,R',U',y,L',U',L,U,L',U',L,U,L',U',L,U,R,U,R',U',R,U,R',U',R,U,R',U',y,L',U',L,U,L',U',L,U,L',U',L,U",
            2),
        CubeTest(UP_TRIPLE_THEN_ALG_TWICE, new PositionLayerCorners(),
            "U,R,U,R',U',R,U,R',U',R,U,R',U',y,L',U',L,U,L',U',L,U,L',U',L,U,R,U,R',U',R,U,R',U',R,U,R',U',y,L',U',L,U,L',U',L,U,L',U',L,U",
            2),
    };

    for (CubeTest scenario : position_last_layer_corner_scenarios) {
        single_algorithm_test(scenario);
        delete dynamic_cast<PositionLayerCorners*>(scenario.algorithm);
    }
}