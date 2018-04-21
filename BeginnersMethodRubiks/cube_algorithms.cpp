/* 
 * File:   CubeAlgorithms.cpp
 * Author: roman.subik
 * 
 * Created on 18 February 2018, 14:21
 */

#include "cube_algorithms.hpp"
#include <iostream>

using namespace std;

// rotation string representations
const string CubeAlgorithm::ROTATE_FRONT_CLOCKWISE = "F";
const string CubeAlgorithm::ROTATE_UP_CLOCKWISE = "U";
const string CubeAlgorithm::ROTATE_BACK_CLOCKWISE = "B";
const string CubeAlgorithm::ROTATE_DOWN_CLOCKWISE = "D";
const string CubeAlgorithm::ROTATE_RIGHT_CLOCKWISE = "R";
const string CubeAlgorithm::ROTATE_LEFT_CLOCKWISE = "L";
const string CubeAlgorithm::ROTATE_FRONT_COUNTER_CLOCKWISE = "F'";
const string CubeAlgorithm::ROTATE_UP_COUNTER_CLOCKWISE = "U'";
const string CubeAlgorithm::ROTATE_BACK_COUNTER_CLOCKWISE = "B'";
const string CubeAlgorithm::ROTATE_DOWN_COUNTER_CLOCKWISE = "D'";
const string CubeAlgorithm::ROTATE_RIGHT_COUNTER_CLOCKWISE = "R'";
const string CubeAlgorithm::ROTATE_LEFT_COUNTER_CLOCKWISE = "L'";

// flip string representations
const string CubeAlgorithm::FLIP_Y_CLOCKWISE_90 = "y";
const string CubeAlgorithm::FLIP_Y_COUNTER_CLOCKWISE_90 = "y'";
const string CubeAlgorithm::FLIP_X_CLOCKWISE_90 = "x";
const string CubeAlgorithm::FLIP_X_COUNTER_CLOCKWISE_90 = "x'";
const string CubeAlgorithm::FLIP_Z_CLOCKWISE_90 = "z";
const string CubeAlgorithm::FLIP_Z_COUNTER_CLOCKWISE_90 = "z'";
const string CubeAlgorithm::FLIP_UPSIDE_DOWN = "z2";

const map<string, Rotation> CubeAlgorithm::rotations = {
    {CubeAlgorithm::ROTATE_FRONT_CLOCKWISE, FRONT_CLOCKWISE},
    {CubeAlgorithm::ROTATE_UP_CLOCKWISE, UP_CLOCKWISE},
    {CubeAlgorithm::ROTATE_BACK_CLOCKWISE, BACK_CLOCKWISE},
    {CubeAlgorithm::ROTATE_DOWN_CLOCKWISE, DOWN_CLOCKWISE},
    {CubeAlgorithm::ROTATE_RIGHT_CLOCKWISE, RIGHT_CLOCKWISE},
    {CubeAlgorithm::ROTATE_LEFT_CLOCKWISE, LEFT_CLOCKWISE},
    {CubeAlgorithm::ROTATE_FRONT_COUNTER_CLOCKWISE, FRONT_COUNTER_CLOCKWISE},
    {CubeAlgorithm::ROTATE_UP_COUNTER_CLOCKWISE, UP_COUNTER_CLOCKWISE},
    {CubeAlgorithm::ROTATE_BACK_COUNTER_CLOCKWISE, BACK_COUNTER_CLOCKWISE},
    {CubeAlgorithm::ROTATE_DOWN_COUNTER_CLOCKWISE, DOWN_COUNTER_CLOCKWISE},
    {CubeAlgorithm::ROTATE_RIGHT_COUNTER_CLOCKWISE, RIGHT_COUNTER_CLOCKWISE},
    {CubeAlgorithm::ROTATE_LEFT_COUNTER_CLOCKWISE, LEFT_COUNTER_CLOCKWISE}
};

const map<string, Flip> CubeAlgorithm::flips = {
    {CubeAlgorithm::FLIP_Y_CLOCKWISE_90, Y_CLOCKWISE_90},
    {CubeAlgorithm::FLIP_Y_COUNTER_CLOCKWISE_90, Y_COUNTER_CLOCKWISE_90},
    {CubeAlgorithm::FLIP_X_CLOCKWISE_90, X_CLOCKWISE_90},
    {CubeAlgorithm::FLIP_X_COUNTER_CLOCKWISE_90, X_COUNTER_CLOCKWISE_90},
    {CubeAlgorithm::FLIP_Z_CLOCKWISE_90, Z_CLOCKWISE_90},
    {CubeAlgorithm::FLIP_Z_COUNTER_CLOCKWISE_90, Z_COUNTER_CLOCKWISE_90},
    {CubeAlgorithm::FLIP_UPSIDE_DOWN, UPSIDE_DOWN}
};

const vector<string> CubeAlgorithm::RIGHTY = {
    ROTATE_RIGHT_CLOCKWISE, ROTATE_UP_CLOCKWISE,
    ROTATE_RIGHT_COUNTER_CLOCKWISE, ROTATE_UP_COUNTER_CLOCKWISE
};

const vector<string> CubeAlgorithm::LEFTY = {
    ROTATE_LEFT_COUNTER_CLOCKWISE, ROTATE_UP_COUNTER_CLOCKWISE,
    ROTATE_LEFT_CLOCKWISE, ROTATE_UP_CLOCKWISE
};

const array<CubePosition, 4> Dasy::WHITE_PETALS = {
    CubePosition(UP, 0, 1), CubePosition(UP, 1, 0),
    CubePosition(UP, 1, 2), CubePosition(UP, 2, 1)
};

const array<PetalSolution, 20> Dasy::PETAL_SOLUTIONS = {
    PetalSolution(CubePosition(FRONT, 0, 1), CubePosition(UP, 2, 1), ROTATE_FRONT_CLOCKWISE),
    PetalSolution(CubePosition(FRONT, 1, 0), CubePosition(UP, 1, 0), ROTATE_LEFT_COUNTER_CLOCKWISE),
    PetalSolution(CubePosition(FRONT, 1, 2), CubePosition(UP, 1, 2), ROTATE_RIGHT_CLOCKWISE),
    PetalSolution(CubePosition(FRONT, 2, 1), CubePosition(UP, 2, 1), ROTATE_FRONT_CLOCKWISE),
    PetalSolution(CubePosition(RIGHT, 0, 1), CubePosition(UP, 1, 2), ROTATE_RIGHT_CLOCKWISE),
    PetalSolution(CubePosition(RIGHT, 1, 0), CubePosition(UP, 2, 1), ROTATE_FRONT_COUNTER_CLOCKWISE),
    PetalSolution(CubePosition(RIGHT, 1, 2), CubePosition(UP, 0, 1), ROTATE_BACK_CLOCKWISE),
    PetalSolution(CubePosition(RIGHT, 2, 1), CubePosition(UP, 1, 2), ROTATE_RIGHT_CLOCKWISE),
    PetalSolution(CubePosition(LEFT, 0, 1), CubePosition(UP, 1, 0), ROTATE_LEFT_CLOCKWISE),
    PetalSolution(CubePosition(LEFT, 1, 0), CubePosition(UP, 0, 1), ROTATE_BACK_COUNTER_CLOCKWISE),
    PetalSolution(CubePosition(LEFT, 1, 2), CubePosition(UP, 2, 1), ROTATE_FRONT_CLOCKWISE),
    PetalSolution(CubePosition(LEFT, 2, 1), CubePosition(UP, 1, 0), ROTATE_LEFT_CLOCKWISE),
    PetalSolution(CubePosition(BACK, 0, 1), CubePosition(UP, 0, 1), ROTATE_BACK_CLOCKWISE),
    PetalSolution(CubePosition(BACK, 1, 0), CubePosition(UP, 1, 2), ROTATE_RIGHT_COUNTER_CLOCKWISE),
    PetalSolution(CubePosition(BACK, 1, 2), CubePosition(UP, 1, 0), ROTATE_LEFT_CLOCKWISE),
    PetalSolution(CubePosition(BACK, 2, 1), CubePosition(UP, 0, 1), ROTATE_BACK_CLOCKWISE),
    PetalSolution(CubePosition(DOWN, 0, 1), CubePosition(UP, 2, 1), ROTATE_FRONT_CLOCKWISE),
    PetalSolution(CubePosition(DOWN, 1, 0), CubePosition(UP, 1, 0), ROTATE_LEFT_COUNTER_CLOCKWISE),
    PetalSolution(CubePosition(DOWN, 1, 2), CubePosition(UP, 1, 2), ROTATE_RIGHT_CLOCKWISE),
    PetalSolution(CubePosition(DOWN, 2, 1), CubePosition(UP, 0, 1), ROTATE_BACK_CLOCKWISE)
};

int Cublet::countPartiallyMatchedSides(Cube cube) const {
    vector<Color> colors = getColors(cube);
    int matchedSides = 0;

    for (CubePosition position : pieces) {
        Color sideColor = cube.getSideLeadingColor(position.side);
        if (hasColorOnAnySide(sideColor, cube)) {
            ++matchedSides;
        }
    }

    return matchedSides;
}

int Cublet::countFullyMatchedSides(Cube cube) const {
    vector<Color> colors = getColors(cube);
    int matchedSides = 0;

    for (int i = 0; i < colors.size(); ++i) {
        Color cubletColor = colors[i];
        CubePosition position = pieces[i];
        Color sideColor = cube.getSideLeadingColor(position.side);

        if (cubletColor == sideColor) {
            ++matchedSides;
        }
    }

    return matchedSides;
}

vector<Color> Cublet::getColors(Cube cube) const {
    vector<Color> colors;
    for (CubePosition piece : pieces) {
        colors.push_back(cube.getColor(piece));
    }
    return colors;
}

bool Cublet::hasColorOnAnySide(Color color, Cube cube) const {
    vector<Color> colors = getColors(cube);
    return find(colors.begin(), colors.end(), color) != colors.end();
}

CubePosition Cublet::getCubePosition(Side side) const {
    for (CubePosition cubePosition : pieces) {
        if (cubePosition.side == side) {
            return cubePosition;
        }
    }

    throw SideNotFoundException();
}

string CubeAlgorithm::perform(Cube &cube) {
    if (!initialPositionSet) {
        findInitialPosition(cube);
    }

    findPositionBeforeRotation(cube);
    rotate(cube);
    shorten(ss);
    return getMovesAsString();
}

string CubeAlgorithm::getMovesAsString() {
    string moves = ss.str();
    return moves.size() > 1 ? moves.substr(0, moves.size() - 1) : moves;
}

void CubeAlgorithm::doMove(Cube &cube, string move) {
    map<string, Rotation>::const_iterator itRot = rotations.find(move);

    if (itRot != rotations.end()) {
        cube.rotate(itRot->second);
        ss << move << ",";
    }

    map<string, Flip>::const_iterator itFlp = flips.find(move);

    if (itFlp != flips.end()) {
        cube.flip(itFlp->second);
        ss << move << ",";
    }
}

void CubeAlgorithm::doMoves(Cube &cube, vector<string> moves) {
    for (string move : moves) {
        doMove(cube, move);
    }
}

void Dasy::rotate(Cube &cube) {
    const PetalSolution* solution = nextMissingWhiteEdge(cube);

    if (!solution) {
        return;
    }

    for (int i = 0; i < 3; ++i) {
        if (cube.getColor(solution->cantBeWhite) == WHITE) {
            CubeAlgorithm::doMove(cube, CubeAlgorithm::ROTATE_UP_CLOCKWISE);
        }
    }

    CubeAlgorithm::doMove(cube, solution->rotation);
}

const PetalSolution* Dasy::nextMissingWhiteEdge(Cube cube) {
    for (auto it = PETAL_SOLUTIONS.begin(); it != PETAL_SOLUTIONS.end(); ++it) {
        if (cube.getColor(it->startingPosition) == WHITE) {
            return it;
        }
    }

    return nullptr;
}

void WhiteCross::findPositionBeforeRotation(Cube &cube) {
    for (int i = 0; i < 3; ++i) {
        try {
            matchingSide = findMatchingSide(cube);
            break;
        } catch (SideNotFoundException exc) {
            cout << "Another rotation - side was not found" << endl;
            CubeAlgorithm::doMove(cube, CubeAlgorithm::ROTATE_UP_CLOCKWISE);
        }
    }
}

Side WhiteCross::findMatchingSide(Cube cube) {
    array<Side, 4> topLayerSides = {FRONT, RIGHT, BACK, LEFT};

    for (Side side : topLayerSides) {
        if ((cube.cube[side][0][1] == cube.cube[side][1][1]) &&
                (cube.cube[side][0][1] == cube.getSideLeadingColor(side))) {
            return side;
        }
    }

    throw SideNotFoundException();
}

void WhiteCross::rotate(Cube &cube) {
    string rotation;

    switch (matchingSide) {
        case FRONT:
            rotation = CubeAlgorithm::ROTATE_FRONT_CLOCKWISE;
            break;
        case LEFT:
            rotation = CubeAlgorithm::ROTATE_LEFT_CLOCKWISE;
            break;
        case RIGHT:
            rotation = CubeAlgorithm::ROTATE_RIGHT_CLOCKWISE;
            break;
        case BACK:
            rotation = CubeAlgorithm::ROTATE_BACK_CLOCKWISE;
            break;
        default:
            break;
    }

    CubeAlgorithm::doMove(cube, rotation);
}

void FirstLayerCorners::findPositionBeforeRotation(Cube &cube) {
    bool match = false;
    int numberOfRotations = 0;

    while (!match) {
        if (LOWER_CORNERS[0].countFullyMatchedSides(cube) == 3) {
            // already solved, move to the next corner
            CubeAlgorithm::doMove(cube, FLIP_Y_CLOCKWISE_90);
        }

        if (!isCandidateForSwap(UPPER_CORNERS[0], cube)
                && !isCandidateForSwap(LOWER_CORNERS[0], cube)) {
            CubeAlgorithm::doMove(cube, ROTATE_UP_CLOCKWISE);
        } else {
            match = true;
        }
    }
}

void FirstLayerCorners::rotate(Cube &cube) {
    while (LOWER_CORNERS[0].countFullyMatchedSides(cube) < 3) {
        CubeAlgorithm::doMoves(cube, RIGHTY);
    }
}

bool FirstLayerCorners::isCandidateForSwap(Corner corner, Cube cube) {
    return corner.hasColorOnAnySide(Color::WHITE, cube) &&
            (corner.countPartiallyMatchedSides(cube) >= 2);
}

void SecondLayerEdges::findPositionBeforeRotation(Cube &cube) {
    int rotations = 0;
    currentSwap = Swap::NOTHING;

    while (currentSwap == Swap::NOTHING) {

        if (sideSolved(cube) || rotations >= 3) {
            CubeAlgorithm::doMove(cube, FLIP_Y_CLOCKWISE_90);
            rotations = 0;
            continue;
        }

        currentSwap = findSwap(cube);

        if (currentSwap == Swap::NOTHING) {
            CubeAlgorithm::doMove(cube, ROTATE_UP_CLOCKWISE);
            ++rotations;
        }

    }
}

void SecondLayerEdges::rotate(Cube &cube) {
    switch (currentSwap) {
        case Swap::LEFT_FRONT_EDGE:
            CubeAlgorithm::doMove(cube, ROTATE_UP_COUNTER_CLOCKWISE);
            CubeAlgorithm::doMoves(cube, LEFTY);
            CubeAlgorithm::doMove(cube, FLIP_Y_COUNTER_CLOCKWISE_90);
            CubeAlgorithm::doMoves(cube, RIGHTY);
            break;
        case Swap::RIGHT_FRONT_EDGE:
            CubeAlgorithm::doMove(cube, ROTATE_UP_CLOCKWISE);
            CubeAlgorithm::doMoves(cube, RIGHTY);
            CubeAlgorithm::doMove(cube, FLIP_Y_CLOCKWISE_90);
            CubeAlgorithm::doMoves(cube, LEFTY);
            break;
        case NOTHING:
            break;
    }
}

SecondLayerEdges::Swap SecondLayerEdges::findSwap(Cube cube) {
    Color thirdLayerFrontEdgeColor = cube.getColor(THIRD_LAYER_FRONT_EDGE.getCubePosition(Side::FRONT));
    Color thirdLayerUpEdgeColor = cube.getColor(THIRD_LAYER_FRONT_EDGE.getCubePosition(Side::UP));
    Color secondLayerLeftEdgeColor = cube.getColor(SECOND_LAYER_LEFT_EDGE.getCubePosition(Side::LEFT));
    Color secondLayerRightEdgeColor = cube.getColor(SECOND_LAYER_RIGHT_EDGE.getCubePosition(Side::RIGHT));

    if (thirdLayerFrontEdgeColor == cube.getSideLeadingColor(FRONT)) {
        if (thirdLayerUpEdgeColor == cube.getSideLeadingColor(LEFT)) {
            return Swap::LEFT_FRONT_EDGE;
        } else if (thirdLayerUpEdgeColor == cube.getSideLeadingColor(RIGHT)) {
            return Swap::RIGHT_FRONT_EDGE;
        }
    }

    if (SECOND_LAYER_LEFT_EDGE.countFullyMatchedSides(cube) < 2 && 
            !SECOND_LAYER_LEFT_EDGE.hasColorOnAnySide(Color::YELLOW, cube)) {
        return Swap::LEFT_FRONT_EDGE;
    }

    if (SECOND_LAYER_RIGHT_EDGE.countFullyMatchedSides(cube) < 2 && 
            !SECOND_LAYER_RIGHT_EDGE.hasColorOnAnySide(Color::YELLOW, cube)) {
        return Swap::RIGHT_FRONT_EDGE;
    }
    
    if (SECOND_LAYER_LEFT_EDGE.countPartiallyMatchedSides(cube) == 2) {
        return Swap::LEFT_FRONT_EDGE;
    }

    if (SECOND_LAYER_RIGHT_EDGE.countPartiallyMatchedSides(cube) == 2) {
        return Swap::RIGHT_FRONT_EDGE;
    }

    return Swap::NOTHING;
}

bool SecondLayerEdges::sideSolved(Cube cube) {
    return (SECOND_LAYER_LEFT_EDGE.countFullyMatchedSides(cube) == 2) &&
            (SECOND_LAYER_RIGHT_EDGE.countFullyMatchedSides(cube) == 2);
}

void SecondLayerEdges::shorten(stringstream &ss) {
    std::string s = ss.str();
    const string FAILED_SIDE = "U,U,U,y,U";
    size_t found;
    
    do {
        found = s.find(FAILED_SIDE);
        if (found != std::string::npos) {
            s.replace(s.find(FAILED_SIDE), FAILED_SIDE.length(), "y");
        }
    } while (found != std::string::npos);
    
    ss.str(s);
}

void YellowDot::rotate(Cube & cube) {
    CubeAlgorithm::doMove(cube, CubeAlgorithm::ROTATE_FRONT_CLOCKWISE);
    CubeAlgorithm::doMoves(cube, RIGHTY);
    CubeAlgorithm::doMove(cube, CubeAlgorithm::ROTATE_FRONT_COUNTER_CLOCKWISE);
}

void YellowLine::findInitialPosition(Cube & cube) {
    for (int i = 0; i < 2; ++i) {
        if (!isYellowLine(cube)) {
            CubeAlgorithm::doMove(cube, CubeAlgorithm::ROTATE_UP_CLOCKWISE);
        }
    }
}

bool YellowLine::isYellowLine(Cube cube) {
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[UP];
    return (side[1][0] == side[1][2]) && (side[1][0] == side[1][1])
            && (side[1][0] == YELLOW);
}

void YellowLine::rotate(Cube & cube) {
    CubeAlgorithm::doMove(cube, CubeAlgorithm::ROTATE_FRONT_CLOCKWISE);
    CubeAlgorithm::doMoves(cube, RIGHTY);
    CubeAlgorithm::doMove(cube, CubeAlgorithm::ROTATE_FRONT_COUNTER_CLOCKWISE);
}

void YellowArc::findInitialPosition(Cube & cube) {
    for (int i = 0; i < 3; ++i) {
        if (!isYellowArc(cube)) {
            CubeAlgorithm::doMove(cube, CubeAlgorithm::ROTATE_UP_CLOCKWISE);
        }
    }
}

bool YellowArc::isYellowArc(Cube cube) {
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[UP];
    return (side[1][1] == side[1][2]) && (side[1][1] == side[2][1])
            && (side[1][1] == YELLOW);
}

void YellowArc::rotate(Cube & cube) {
    CubeAlgorithm::doMove(cube, CubeAlgorithm::FLIP_Z_CLOCKWISE_90);
    CubeAlgorithm::doMove(cube, CubeAlgorithm::ROTATE_BACK_CLOCKWISE);
    CubeAlgorithm::doMoves(cube, RIGHTY);
    CubeAlgorithm::doMove(cube, CubeAlgorithm::ROTATE_BACK_COUNTER_CLOCKWISE);
    CubeAlgorithm::doMove(cube, CubeAlgorithm::FLIP_Z_COUNTER_CLOCKWISE_90);
}