/* 
 * File:   beginners_method.cpp
 * Author: roman.subik
 * 
 * Created on 16 January 2018, 22:49
 */

#include "method_steps.hpp"
#include "cube_algorithms.hpp"
#include <iostream>
#include <functional>

using namespace std;

BeginnersMethod::BeginnersMethod() {

}

bool BeginnersMethod::isDasyDone(Cube &cube) {
    return isStateDone(cube, State::DASY);
}

bool BeginnersMethod::isWhiteCrossDone(Cube &cube) {
    return isStateDone(cube, State::WHITE_CROSS);
}

bool BeginnersMethod::areFirstLayerCornersDone(Cube &cube) {
    return isStateDone(cube, State::FIRST_LAYER_CORNERS);
}

bool BeginnersMethod::areSecondLayerEdgesDone(Cube &cube) {
    return isStateDone(cube, State::SECOND_LAYER_EDGES);
}

bool BeginnersMethod::isYellowDotDone(Cube &cube) {
    return isStateDone(cube, State::YELLOW_DOT);
};

bool BeginnersMethod::isYellowLineDone(Cube &cube) {
    return isStateDone(cube, State::YELLOW_LINE);
};

bool BeginnersMethod::isYellowArcDone(Cube &cube) {
    return isStateDone(cube, State::YELLOW_ARC);
};

bool BeginnersMethod::isYellowCrossDone(Cube &cube) {
    return isStateDone(cube, State::YELLOW_CROSS);
};

bool BeginnersMethod::areLastLayerCornersPositioned(Cube &cube) {
    return isStateDone(cube, State::POSITION_LAST_LAYER_CORNERS);
};

bool BeginnersMethod::areLastLayerCornersPermuted(Cube &cube) {
    return isStateDone(cube, State::PERMUTE_LAST_LAYER_CORNERS);
};

bool BeginnersMethod::isSolved(Cube &cube) {
    return isStateDone(cube, State::SOLVED);
};

bool BeginnersMethod::isStateDone(Cube &cube, State state) {
    switch (state) {
        case DASY:
            ensureColorOnTop(cube, YELLOW);
            return checkDasy(cube);
        case WHITE_CROSS:
            ensureColorOnTop(cube, WHITE);
            return checkWhiteCross(cube);
        case FIRST_LAYER_CORNERS:
            ensureColorOnTop(cube, YELLOW);
            return checkFirstLayerCorners(cube);
        case SECOND_LAYER_EDGES:
            ensureColorOnTop(cube, YELLOW);
            return checkSecondLayerEdges(cube);
        case YELLOW_DOT:
            ensureColorOnTop(cube, YELLOW);
            return checkYellowDot(cube);
        case YELLOW_LINE:
        {
            ensureColorOnTop(cube, YELLOW);
            function<bool(Cube&) > check = [&](Cube & _cube) {
                return checkYellowLine(_cube);
            };
            return checkConditionOnManyAngles(cube, Y_CLOCKWISE_90, 2, check);
        }
        case YELLOW_ARC:
        {
            ensureColorOnTop(cube, YELLOW);
            function<bool(Cube&) > check = [&](Cube & _cube) {
                return checkYellowArc(_cube);
            };
            return checkConditionOnManyAngles(cube, Y_CLOCKWISE_90, 4, check);
        }
        case YELLOW_CROSS:
        {
            ensureColorOnTop(cube, YELLOW);
            return checkYellowCross(cube);
        }
        case POSITION_LAST_LAYER_CORNERS:
        {
            ensureColorOnTop(cube, YELLOW);
            return checkLastLayerCornersPosition(cube);
        }
        case PERMUTE_LAST_LAYER_CORNERS:
        {
            ensureColorOnTop(cube, YELLOW);
            return checkLastLayerCornersPermutation(cube);
        }
        case SOLVED:
        {
            ensureColorOnTop(cube, WHITE);
            return checkSolved(cube);
        }
        default:
            return false;
    }

};

bool BeginnersMethod::checkDasy(Cube &cube) {
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[UP];

    if (!hasRightColorUnderPetals(cube)) {
        return false;
    }

    return (side[1][1] == YELLOW) &&
            (side[0][1] == side[1][0] == side[1][2] == WHITE);
}

bool BeginnersMethod::checkWhiteCross(Cube &cube) {
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[UP];

    if (!hasRightColorUnderPetals(cube)) {
        return false;
    }

    return (side[0][1] == side[1][1]) && (side[0][1] == side[1][0]) &&
            (side[0][1] == side[1][2]) && (side[0][1] == side[2][1]) &&
            (side[0][1] == WHITE);
}

bool BeginnersMethod::checkFirstLayerCorners(Cube &cube) {
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[DOWN];

    if (cube.getSideLeadingColor(DOWN) != WHITE)
        return false;

    if (!isSideCompleted(cube, DOWN))
        return false;

    array<Side, 4> sides = {LEFT, FRONT, RIGHT, BACK};
    for (Side neighbour : sides) {
        if (!hasLowerT(cube, neighbour))
            return false;
    }

    return true;
}

bool BeginnersMethod::checkSecondLayerEdges(Cube &cube) {
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

bool BeginnersMethod::checkYellowDot(Cube &cube) {
    if (!areSecondLayerEdgesDone(cube)) {
        return false;
    }

    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[UP];

    return side[1][1] == YELLOW;
}

bool BeginnersMethod::checkYellowLine(Cube &cube) {
    if (!isYellowDotDone(cube)) {
        return false;
    }

    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[UP];

    return (side[1][0] == side[1][2]) && (side[1][0] == YELLOW);
}

bool BeginnersMethod::checkYellowArc(Cube &cube) {
    if (!isYellowDotDone(cube)) {
        return false;
    }

    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[UP];

    return (side[1][2] == side[2][1]) && (side[1][2] == YELLOW);
}

bool BeginnersMethod::checkYellowCross(Cube &cube) {
    if (!isYellowDotDone(cube)) {
        return false;
    }

    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[UP];

    return (side[0][1] == side[1][0]) && (side[0][1] == side[1][2]) &&
            (side[0][1] == side[2][1]) && (side[0][1] == YELLOW);
}

bool BeginnersMethod::checkLastLayerCornersPosition(Cube& cube) {
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

bool BeginnersMethod::checkLastLayerCornersPermutation(Cube& cube) {
    if (!areLastLayerCornersPositioned(cube)) {
        return false;
    }

    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[DOWN];

    if (cube.getSideLeadingColor(DOWN) != WHITE) {
        return false;
    }

    if (!isSideCompleted(cube, DOWN)) {
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

bool BeginnersMethod::checkSolved(Cube& cube) {
    for (int sideNum = FRONT; sideNum <= LEFT; ++sideNum) {
        Side currentSide = static_cast<Side> (sideNum);
        if (!isSideCompleted(cube, currentSide)) {
            return false;
        }
    }

    return true;
}

bool BeginnersMethod::colorsMatchInAnyOrder(array<Color, 3> a1, array<Color, 3> a2) {
    for (int i = 0; i < 3; ++i) {
        if (find(std::begin(a2), std::end(a2), a1[i]) == std::end(a2)) {
            return false;
        }
    }

    return true;
}

bool BeginnersMethod::isSideCompleted(Cube &cube, Side leadingSide) {
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[leadingSide];
    Color correct = side[Cube::SIZE - 1][Cube::SIZE - 1];

    for (int i = 0; i < Cube::SIZE; ++i) {
        for (int j = 0; j < Cube::SIZE; ++j) {
            if (side[i][j] != correct) {
                return false;
            }
        }
    }

    return true;
}

bool BeginnersMethod::hasRightColorUnderPetals(Cube &cube) {
    return (cube.cube[FRONT][0][1] == cube.cube[FRONT][1][1])&&
            (cube.cube[BACK][0][1] == cube.cube[BACK][1][1]) &&
            (cube.cube[RIGHT][0][1] == cube.cube[RIGHT][1][1]) &&
            (cube.cube[LEFT][0][1] == cube.cube[LEFT][1][1]);
}

bool BeginnersMethod::hasLowerT(Cube &cube, Side leadingSide) {
    Color correct = cube.getSideLeadingColor(leadingSide);
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[leadingSide];
    if ((side[1][1] == side[2][0]) && (side[1][1] == side[2][1]) &&
            (side[1][1] == side[2][2]) && (side[1][1] == correct)) {
        return true;
    }

    return false;
}

bool BeginnersMethod::hasSecondLayerEdgesPositioned(Cube &cube, Side leadingSide) {
    Color correct = cube.getSideLeadingColor(leadingSide);
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[leadingSide];
    if ((side[1][2] == side[1][0]) and (side[1][2] == correct)) {
        return true;
    }

    return false;
}

bool BeginnersMethod::checkConditionOnManyAngles(Cube &cube, Flip flip, int maxFlips, function<bool(Cube&) > condition) {
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

void BeginnersMethod::ensureColorOnTop(Cube &cube, Color color) {
    Side leadingSide = FRONT;

    for (int sideNum = FRONT; sideNum <= LEFT; ++sideNum) {
        Side currentSide = static_cast<Side> (sideNum);
        if (cube.getSideLeadingColor(currentSide) == color) {
            leadingSide = currentSide;
            break;
        }
    }

    switch (leadingSide) {
        case UP:
            break;
        case DOWN:
            cube.flip(UPSIDE_DOWN);
            break;
        case FRONT:
            cube.flip(X_CLOCKWISE_90);
            break;
        case BACK:
            cube.flip(X_COUNTER_CLOCKWISE_90);
            break;
        case RIGHT:
            cube.flip(Z_COUNTER_CLOCKWISE_90);
            break;
        case LEFT:
            cube.flip(Z_CLOCKWISE_90);
            break;
    }
}

