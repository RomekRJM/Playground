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

BOOST_AUTO_TEST_CASE(test_dasy) {
    Cube DOWN_EDGE_PIECE = CubeGenerator::fromString(
            "WGBRGYYRW,GWOWYWRYY,GOBGRRGRB,OWOGWYGBO,RGWBBBROY,YBBOOYWOR"
            );
    Cube FIRST_LAYER_EDGE_PIECE = CubeGenerator::fromString(
            "WGOORRWWR,YWYWYWBYW,GOGYOOBGY,RRBOWYORY,GGRBGBWRR,OBOGBYBBG"
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
    
    vector<CubeTest> dasy_scenarios = {
        CubeTest(DOWN_EDGE_PIECE, new Dasy(), "F,F,", 2),                // DOWN, 0, 1
        CubeTest(FIRST_LAYER_EDGE_PIECE, new Dasy(), "F,U,L',", 2),      // FRONT, 2, 1
        CubeTest(SECOND_LAYER_RIGHT_EDGE_PIECE, new Dasy(), "F,", 1),    // LEFT, 1, 2
        CubeTest(SECOND_LAYER_LEFT_EDGE_PIECE, new Dasy(), "F',", 1),    // RIGHT, 1, 0
        CubeTest(THIRD_LAYER_LEFT_EDGE_PIECE, new Dasy(), "F,R,", 2),    // FRONT, 0, 1
        
        CubeTest(*DOWN_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90), new Dasy(), "L',L',", 2),              // DOWN, 1, 0
        CubeTest(*FIRST_LAYER_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90), new Dasy(), "L,U,B',", 2),      // LEFT, 2, 1
        CubeTest(*SECOND_LAYER_RIGHT_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90), new Dasy(), "L,", 1),    // BACK, 1, 2
        CubeTest(*SECOND_LAYER_LEFT_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90), new Dasy(), "L',", 1),    // BACK, 1, 0
        CubeTest(*THIRD_LAYER_LEFT_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90), new Dasy(), "L,F,", 2),    // LEFT, 0, 1
        
        CubeTest(*DOWN_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90), new Dasy(), "B,B,", 2),                // DOWN, 2, 1
        CubeTest(*FIRST_LAYER_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90), new Dasy(), "B,U,R',", 2),      // BACK, 2, 1
        CubeTest(*SECOND_LAYER_RIGHT_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90), new Dasy(), "B,", 1),    // RIGHT, 1, 2
        CubeTest(*SECOND_LAYER_LEFT_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90), new Dasy(), "B',", 1),    // LEFT, 1, 0
        CubeTest(*THIRD_LAYER_LEFT_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90), new Dasy(), "B,L,", 2),    // BACK, 0, 1
        
        CubeTest(*DOWN_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90), new Dasy(), "R,R,", 2),                // DOWN, 1, 2
        CubeTest(*FIRST_LAYER_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90), new Dasy(), "R,U,F',", 2),      // RIGHT, 2, 1
        CubeTest(*SECOND_LAYER_RIGHT_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90), new Dasy(), "R,", 1),    // FRONT, 1, 2
        CubeTest(*SECOND_LAYER_LEFT_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90), new Dasy(), "R',", 1),    // FRONT, 1, 0
        CubeTest(*THIRD_LAYER_LEFT_EDGE_PIECE.flip(Flip::Y_CLOCKWISE_90), new Dasy(), "R,B,", 2),    // RIGHT, 0, 1
    };

    for (CubeTest scenario : dasy_scenarios) {
        single_algorithm_test(scenario);
        delete dynamic_cast<Dasy*>(scenario.algorithm);
    }
}

BOOST_AUTO_TEST_CASE(test_white_cross) {
    Cube FF = CubeGenerator::fromString(
            "RROGRYWOY,YWYWYWWWW,GOGBOOWGY,OYBOWYORB,GGRRGRRBR,OBGGBYBBB"
            );
    Cube BB = CubeGenerator::fromString(
            "YOWYRGORR,YWYWYWBYO,GOGBOOWGY,WWWOWYORB,BGRYGRGBR,OBRGBRBBG"
            );
    Cube RR = CubeGenerator::fromString(
            "YOWYRGORR,BROWYWBYO,YGWOOBGOG,WWWOWYYWY,BGBYGGGBO,RBRRBRRBG"
            );
    Cube LL = CubeGenerator::fromString(
            "YOGYROORY,BRWWYYBYY,RGWGOBWOG,WWOOWWYWO,OBGGGYBGB,RBRRBRRBG"
            );
    Cube UULL = CubeGenerator::fromString(
            "GOWOOYGOY,WROOYWYYO,YGOBRGWRR,YWBYWWWWB,BGBRBRRBR,GBRYGGGBO"
            );
    
    vector<CubeTest> white_cross_scenarios = {
        CubeTest(FF, new WhiteCross(), "F,F,"),
        CubeTest(BB, new WhiteCross(), "B,B,"),
        CubeTest(RR, new WhiteCross(), "R,R,"),
        CubeTest(LL, new WhiteCross(), "L,L,"),
        CubeTest(UULL, new WhiteCross(), "U,U,L,L,")
    };

    for (CubeTest scenario : white_cross_scenarios) {
        single_algorithm_test(scenario);
        delete dynamic_cast<WhiteCross*>(scenario.algorithm);
    }
}

BOOST_AUTO_TEST_CASE(test_first_layer_corners) {
    Cube RIGHTY = CubeGenerator::fromString(
            "YORRRYWRG,OBGOYYRGG,YOBRORBOB,OWWWWWRWR,WBOGGYOGW,YYGGBBYBB"
            );
    Cube RIGHTY_2 = CubeGenerator::fromString(
            "YORGOBOOB,OYGOYRRGB,YRBBRBRRR,WWOWWWWWW,YGORBYWBB,YYGOGYGGG"
            );
    Cube RIGHTY_3 = CubeGenerator::fromString(
            "RRORGGBGO,BYRYYRBYW,YGRBBYGBR,WWBWWWWWY,GGGOOOYOO,YBWORBGRO"
            );
    Cube RIGHTY_5 = CubeGenerator::fromString(
            "RRWYGWGGR,BYOGYBGBG,GOWYBYWBO,WWYWWGBWO,OOYOOGBRB,ROYRRBYRR"
            );
    Cube YCLOCKWISE_RIGHTY_UP_3_RIGHTY_5 = CubeGenerator::fromString(
            "YOWRRBWRR,GYYOYYRGG,BBORORBOB,OWWWWWRWR,OGOOGYGGW,YYGGBBYBB"
            );
    
    vector<CubeTest> first_layer_corner_scenarios = {
        CubeTest(RIGHTY, new FirstLayerCorners(), 
                "R,U,R',U',"),
        CubeTest(RIGHTY_2, new FirstLayerCorners(), 
                "R,U,R',U',R,U,R',U',", 2),
        CubeTest(RIGHTY_3, new FirstLayerCorners(), 
                "R,U,R',U',R,U,R',U',R,U,R',U',"),
        CubeTest(RIGHTY_5, new FirstLayerCorners(), 
                "R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',"),
        CubeTest(YCLOCKWISE_RIGHTY_UP_3_RIGHTY_5, new FirstLayerCorners(), 
                "y,R,U,R',U',U,U,U,R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',", 2)
    };

    for (CubeTest scenario : first_layer_corner_scenarios) {
        single_algorithm_test(scenario);
        delete dynamic_cast<FirstLayerCorners*>(scenario.algorithm);
    }
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
    
    vector<CubeTest> second_layer_edges_scenarios = {
        CubeTest(TO_THE_RIGHT, new SecondLayerEdges(), 
                "U,R,U,R',U',y,L',U',L,U,"),
        CubeTest(TO_THE_LEFT, new SecondLayerEdges(), 
                "U',L',U',L,U,y',R,U,R',U',"),
        CubeTest(Y3_UP_TO_THE_LEFT, new SecondLayerEdges(), 
                "y,y,y,U,U',L',U',L,U,y',R,U,R',U',"),
        CubeTest(RIGHT_IN_PLACE_BUT_TWISTED, new SecondLayerEdges(), 
                "U,R,U,R',U',y,L',U',L,U,")
    };

    for (CubeTest scenario : second_layer_edges_scenarios) {
        single_algorithm_test(scenario);
        delete dynamic_cast<SecondLayerEdges*>(scenario.algorithm);
    }
}

BOOST_AUTO_TEST_CASE(test_yellow_dot) {

    Cube cube = CubeGenerator::fromString(
            "GYBGGGGGG,YYYBYYORO,GGBBBBBBB,WWWWWWWWW,YOROOOOOO,RYYRRRRRR"
            );
    YellowDot yellowDot = YellowDot();
    string s = yellowDot.perform(cube);
    BOOST_CHECK(s == "F,R,U,R',U',F',");
}

BOOST_AUTO_TEST_CASE(test_yellow_line) {

    Cube cube = CubeGenerator::fromString(
            "GYBGGGGGG,YYYYYYORO,GGBBBBBBB,WWWWWWWWW,YOROOOOOO,RYBRRRRRR"
            );
    YellowLine yellowLine = YellowLine();
    string s = yellowLine.perform(cube);
    BOOST_CHECK(s == "F,R,U,R',U',F',");
}

BOOST_AUTO_TEST_CASE(test_yellow_line_with_initial_move) {

    Cube cube = CubeGenerator::fromString(
            "GYBGGGGGG,YYOYYRYYO,GGBBBBBBB,WWWWWWWWW,YOROOOOOO,RYBRRRRRR"
            );
    YellowLine yellowLine = YellowLine();
    string s = yellowLine.perform(cube);
    BOOST_CHECK(s == "U,F,R,U,R',U',F',");
}

BOOST_AUTO_TEST_CASE(test_yellow_arc) {

    Cube cube = CubeGenerator::fromString(
            "GYBGGGGGG,OBYRYYOYY,GGBBBBBBB,WWWWWWWWW,YOROOOOOO,RYYRRRRRR"
            );
    YellowArc yellowArc = YellowArc();
    string s = yellowArc.perform(cube);
    BOOST_CHECK(s == "z,B,R,U,R',U',B',z',");
}

BOOST_AUTO_TEST_CASE(test_yellow_arc_with_initial_move) {

    Cube cube = CubeGenerator::fromString(
            "GYBGGGGGG,YYYBYYORO,GGBBBBBBB,WWWWWWWWW,YOROOOOOO,RYYRRRRRR"
            );
    YellowArc yellowArc = YellowArc();
    string s = yellowArc.perform(cube);
    BOOST_CHECK(s == "U,z,B,R,U,R',U',B',z',");
}

BOOST_AUTO_TEST_CASE(test_position_last_layer_corners) {
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
        CubeTest(FLIP_Y_THEN_ALG, new PositionLastLayerCorners(),
            "y,R,U,R',U',R,U,R',U',R,U,R',U',y,L',U',L,U,L',U',L,U,L',U',L,U,"),
        CubeTest(ALG_TWICE, new PositionLastLayerCorners(),
            "R,U,R',U',R,U,R',U',R,U,R',U',y,L',U',L,U,L',U',L,U,L',U',L,U,R,U,R',U',"
                "R,U,R',U',R,U,R',U',y,L',U',L,U,L',U',L,U,L',U',L,U,"),
        CubeTest(UP_TRIPLE_THEN_ALG_TWICE, new PositionLastLayerCorners(),
            "U,R,U,R',U',R,U,R',U',R,U,R',U',y,L',U',L,U,L',U',L,U,L',U',L,U,R,U,R',U',"
                "R,U,R',U',R,U,R',U',y,L',U',L,U,L',U',L,U,L',U',L,U,")
    };

    for (CubeTest scenario : position_last_layer_corner_scenarios) {
        single_algorithm_test(scenario);
        delete dynamic_cast<PositionLastLayerCorners*>(scenario.algorithm);
    }
}

BOOST_AUTO_TEST_CASE(test_permute_last_layer_corners) {
    Cube cube = CubeGenerator::fromString(
            "RRRRRRGGB,WWWWWWWWW,OOOOOOBOG,RYRYYYOYO,BBBBBBYRY,GGGGGGYBY"
            );
    PermuteLastLayerCorners permuteLastLayerCorners = PermuteLastLayerCorners();
    string s = permuteLastLayerCorners.perform(cube);
    
    BOOST_CHECK(s == "R,U,R',U',R,U,R',U',D',R,U,R',U',R,U,R',U',R,U,R',U',"
            "R,U,R',U',D',R,U,R',U',R,U,R',U',D',R,U,R',U',R,U,R',U',R,U,R',U',"
            "R,U,R',U',D',");
}

BOOST_AUTO_TEST_CASE(test_position_last_layer_edges) {
    Cube FRONT_SIDE_SOLVED = CubeGenerator::fromString(
            "OBORRRRRR,YYYYYYYYY,RRROOOOOO,WWWWWWWWW,BGBGGGGGG,GOGBBBBBB"
            );
    Cube NONE_SIDE_SOLVED = CubeGenerator::fromString(
            "GOGOOOOOO,YYYYYYYYY,BRBRRRRRR,WWWWWWWWW,OGOBBBBBB,RBRGGGGGG"
            );
    
    vector<CubeTest> position_last_layer_edges_scenarios = {
        CubeTest(FRONT_SIDE_SOLVED, new PositionLastLayerEdges(),
            "U,U,R,U,R',U',L',U',L,U,R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',"
                "L',U',L,U,L',U',L,U,L',U',L,U,L',U',L,U,L',U',L,U,"),
        CubeTest(NONE_SIDE_SOLVED, new PositionLastLayerEdges(),
            "U,R,U,R',U',L',U',L,U,R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',"
            "L',U',L,U,L',U',L,U,L',U',L,U,L',U',L,U,L',U',L,U,y,y,R,U,R',U',L',U',L,U,"
            "R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',"
            "L',U',L,U,L',U',L,U,L',U',L,U,L',U',L,U,L',U',L,U,R,U,R',U',L',U',L,U,"
            "R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',R,U,R',U',L',U',L,U,L',U',L,U,L',U',L,U,L',U',L,U,L',U',L,U,")
    };
    
    for (CubeTest scenario : position_last_layer_edges_scenarios) {
        single_algorithm_test(scenario);
        delete dynamic_cast<PositionLastLayerEdges*>(scenario.algorithm);
    }
}
