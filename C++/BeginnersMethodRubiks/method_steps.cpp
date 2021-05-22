/* 
 * File:   beginners_method.cpp
 * Author: roman.subik
 * 
 * Created on 16 January 2018, 22:49
 */

#include "method_steps.hpp"
#include "cube_algorithms.hpp"
#include "cube_logging.hpp"
#include <iostream>
#include <functional>

using namespace std;

bool MethodSteps::isDasyDone(Cube &cube) {
    return isStateDone(cube, State::DASY);
}

bool MethodSteps::isWhiteCrossDone(Cube &cube) {
    return isStateDone(cube, State::WHITE_CROSS);
}

bool MethodSteps::areFirstLayerCornersDone(Cube &cube) {
    return isStateDone(cube, State::FIRST_LAYER_CORNERS);
}

bool MethodSteps::areSecondLayerEdgesDone(Cube &cube) {
    return isStateDone(cube, State::SECOND_LAYER_EDGES);
}

bool MethodSteps::isYellowDotDone(Cube &cube) {
    return isStateDone(cube, State::YELLOW_DOT);
};

bool MethodSteps::isYellowLineDone(Cube &cube) {
    return isStateDone(cube, State::YELLOW_LINE);
};

bool MethodSteps::isYellowArcDone(Cube &cube) {
    return isStateDone(cube, State::YELLOW_ARC);
};

bool MethodSteps::isYellowCrossDone(Cube &cube) {
    return isStateDone(cube, State::YELLOW_CROSS);
};

bool MethodSteps::areLastLayerCornersPositioned(Cube &cube) {
    return isStateDone(cube, State::POSITION_LAST_LAYER_CORNERS);
};

bool MethodSteps::areLastLayerCornersPermuted(Cube &cube) {
    return isStateDone(cube, State::PERMUTE_LAST_LAYER_CORNERS);
};

bool MethodSteps::isSolved(Cube &cube) {
    return isStateDone(cube, State::POSITION_LAST_LAYER_EDGES);
};

bool MethodSteps::isStateDone(Cube &cube, State state) {
    switch (state) {
        case DASY:
            cube.ensureOnTop(Color::YELLOW);
            return checkDasy(cube);
        case WHITE_CROSS:
            cube.ensureOnTop(Color::YELLOW);
            return checkWhiteCross(cube);
        case FIRST_LAYER_CORNERS:
            cube.ensureOnTop(Color::YELLOW);
            return checkFirstLayerCorners(cube);
        case SECOND_LAYER_EDGES:
            cube.ensureOnTop(Color::YELLOW);
            return checkSecondLayerEdges(cube);
        case YELLOW_DOT:
            cube.ensureOnTop(Color::YELLOW);
            return checkYellowDot(cube);
        case YELLOW_LINE:
        {
            cube.ensureOnTop(Color::YELLOW);
            function<bool(Cube&) > check = [&](Cube & _cube) {
                return checkYellowLine(_cube);
            };
            return checkConditionOnManyAngles(cube, Y_CLOCKWISE_90, 2, check);
        }
        case YELLOW_ARC:
        {
            cube.ensureOnTop(Color::YELLOW);
            function<bool(Cube&) > check = [&](Cube & _cube) {
                return checkYellowArc(_cube);
            };
            return checkConditionOnManyAngles(cube, Y_CLOCKWISE_90, 4, check);
        }
        case YELLOW_CROSS:
        {
            cube.ensureOnTop(Color::YELLOW);
            return checkYellowCross(cube);
        }
        case POSITION_LAST_LAYER_CORNERS:
        {
            cube.ensureOnTop(Color::YELLOW);
            return checkLastLayerCornersPosition(cube);
        }
        case PERMUTE_LAST_LAYER_CORNERS:
        {
            cube.ensureOnTop(Color::WHITE);
            return checkLastLayerCornersPermutation(cube);
        }
        case POSITION_LAST_LAYER_EDGES:
        {
            cube.ensureOnTop(Color::YELLOW);
            return checkSolved(cube);
        }
        default:
            return false;
    }

};

bool MethodSteps::checkDasy(Cube &cube) {
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[UP];
    
    return (side[1][1] == YELLOW) && (side[0][1] == WHITE) && 
           (side[1][0] == WHITE) && (side[1][2] == WHITE) && 
           (side[2][1] == WHITE);
}

bool MethodSteps::checkWhiteCross(Cube &cube) {
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[DOWN];

    if (!hasRightColorUnderPetals(cube)) {
        return false;
    }

    return (side[0][1] == side[1][1]) && (side[0][1] == side[1][0]) &&
            (side[0][1] == side[1][2]) && (side[0][1] == side[2][1]) &&
            (side[0][1] == WHITE);
}

bool MethodSteps::checkFirstLayerCorners(Cube &cube) {
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[DOWN];

    if (cube.getSideLeadingColor(DOWN) != WHITE) {
        debug << "Down not white!";
        return false;
    }
    
    if (!cube.isSideCompleted(DOWN)) {
        debug << "Down not completed!";
        return false;
    }

    array<Side, 4> sides = {LEFT, FRONT, RIGHT, BACK};
    for (Side neighbour : sides) {
        if (!hasLowerT(cube, neighbour)) {
            debug << "Side " << neighbour << " not done";
            return false;
        }
    }

    return true;
}

bool MethodSteps::checkSecondLayerEdges(Cube &cube) {
    if (!areFirstLayerCornersDone(cube)) {
        return false;
    }

    array<Side, 4> sides = {LEFT, FRONT, RIGHT, BACK};
    for (Side side : sides) {
        if (!hasSecondLayerEdgesPositioned(cube, side)) {
            return false;
        }
    }

    return true;
}

bool MethodSteps::checkYellowDot(Cube &cube) {
    if (!areSecondLayerEdgesDone(cube)) {
        return false;
    }

    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[UP];

    return side[1][1] == YELLOW;
}

bool MethodSteps::checkYellowLine(Cube &cube) {
    if (!isYellowDotDone(cube)) {
        return false;
    }

    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[UP];

    return (side[1][0] == side[1][2]) && (side[1][0] == YELLOW);
}

bool MethodSteps::checkYellowArc(Cube &cube) {
    if (!isYellowDotDone(cube)) {
        return false;
    }

    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[UP];

    return (side[1][2] == side[2][1]) && (side[1][2] == YELLOW);
}

bool MethodSteps::checkYellowCross(Cube &cube) {
    if (!isYellowDotDone(cube)) {
        return false;
    }

    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[UP];

    return (side[0][1] == side[1][0]) && (side[0][1] == side[1][2]) &&
            (side[0][1] == side[2][1]) && (side[0][1] == YELLOW);
}

bool MethodSteps::checkLastLayerCornersPosition(Cube& cube) {
    if (!isYellowCrossDone(cube)) {
        return false;
    }

    map<array<Color, 3>, array<Color, 3 >> cornersToSides;

    array<Color, 3> uflCornerColors = {cube.cube[UP][2][0], cube.cube[FRONT][0][0], cube.cube[LEFT][0][2]};
    array<Color, 3> uflSideColors = {cube.getSideLeadingColor(UP), cube.getSideLeadingColor(FRONT), cube.getSideLeadingColor(LEFT)};
    cornersToSides.insert(pair<array<Color, 3>, array<Color, 3 >> (uflCornerColors, uflSideColors));

    array<Color, 3> ufrCornerColors = {cube.cube[UP][2][2], cube.cube[FRONT][0][2], cube.cube[RIGHT][0][0]};
    array<Color, 3> ufrSideColors = {cube.getSideLeadingColor(UP), cube.getSideLeadingColor(FRONT), cube.getSideLeadingColor(RIGHT)};
    cornersToSides.insert(pair<array<Color, 3>, array<Color, 3 >> (ufrCornerColors, ufrSideColors));

    array<Color, 3> ublCornerColors = {cube.cube[UP][0][0], cube.cube[BACK][0][2], cube.cube[LEFT][0][0]};
    array<Color, 3> ublSideColors = {cube.getSideLeadingColor(UP), cube.getSideLeadingColor(BACK), cube.getSideLeadingColor(LEFT)};
    cornersToSides.insert(pair<array<Color, 3>, array<Color, 3 >> (ublCornerColors, ublSideColors));

    array<Color, 3> ubrCornerColors = {cube.cube[UP][0][2], cube.cube[BACK][0][0], cube.cube[RIGHT][0][2]};
    array<Color, 3> ubrSideColors = {cube.getSideLeadingColor(UP), cube.getSideLeadingColor(BACK), cube.getSideLeadingColor(RIGHT)};
    cornersToSides.insert(pair<array<Color, 3>, array<Color, 3 >> (ubrCornerColors, ubrSideColors));

    for (map<array<Color, 3>, array < Color, 3 >> ::iterator it = cornersToSides.begin(); it != cornersToSides.end(); ++it) {
        if (!colorsMatchInAnyOrder(it->first, it->second)) {
            return false;
        }
    }

    return true;
}

bool MethodSteps::checkLastLayerCornersPermutation(Cube& cube) {
    if (!areLastLayerCornersPositioned(cube)) {
        return false;
    }

    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[DOWN];

    if (cube.getSideLeadingColor(DOWN) != WHITE) {
        return false;
    }

    if (!cube.isSideCompleted(DOWN)) {
        return false;
    }

    array<Side, 4> topLayerSides = {FRONT, RIGHT, BACK, LEFT};

    for (Side side : topLayerSides) {
        if ((cube.cube[side][0][0] != cube.cube[side][0][2]) ||
                (cube.cube[side][0][0] != cube.getSideLeadingColor(side))) {
            return false;
        }
    }

    return true;
}

bool MethodSteps::checkSolved(Cube& cube) {
    for (int sideNum = FRONT; sideNum <= LEFT; ++sideNum) {
        Side currentSide = static_cast<Side> (sideNum);
        if (!cube.isSideCompleted(currentSide)) {
            return false;
        }
    }

    return true;
}

bool MethodSteps::colorsMatchInAnyOrder(array<Color, 3> a1, array<Color, 3> a2) {
    for (int i = 0; i < 3; ++i) {
        if (find(std::begin(a2), std::end(a2), a1[i]) == std::end(a2)) {
            return false;
        }
    }

    return true;
}

bool MethodSteps::hasRightColorUnderPetals(Cube &cube) {
    return (cube.cube[FRONT][2][1] == cube.cube[FRONT][1][1])&&
            (cube.cube[BACK][2][1] == cube.cube[BACK][1][1]) &&
            (cube.cube[RIGHT][2][1] == cube.cube[RIGHT][1][1]) &&
            (cube.cube[LEFT][2][1] == cube.cube[LEFT][1][1]);
}

bool MethodSteps::hasLowerT(Cube &cube, Side leadingSide) {
    Color correct = cube.getSideLeadingColor(leadingSide);
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[leadingSide];
    if ((side[1][1] == side[2][0]) && (side[1][1] == side[2][1]) &&
            (side[1][1] == side[2][2]) && (side[1][1] == correct)) {
        return true;
    }

    return false;
}

bool MethodSteps::hasSecondLayerEdgesPositioned(Cube &cube, Side leadingSide) {
    Color correct = cube.getSideLeadingColor(leadingSide);
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[leadingSide];
    if ((side[1][2] == side[1][0]) and (side[1][2] == correct)) {
        return true;
    }

    return false;
}

bool MethodSteps::checkConditionOnManyAngles(Cube &cube, Flip flip, int maxFlips, function<bool(Cube&) > condition) {
    bool conditionMatched = false;
    for (int i = 0; i < maxFlips; ++i) {
        if (condition(cube)) {
            conditionMatched = true;
            break;
        } else if (i < maxFlips - 1) {
            cube.flip(flip);
        }
    }

    return conditionMatched;
}
