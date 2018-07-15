/* 
 * File:   CubeAlgorithms.cpp
 * Author: roman.subik
 * 
 * Created on 18 February 2018, 14:21
 */

#include "cube_algorithms.hpp"
#include "cube_logging.hpp"
#include <algorithm>
#include <iostream>

using namespace std;

void replaceAllInStringStream(stringstream& ss, string toBeReplaced, string replacement) {
    std::string s = ss.str();
    size_t found;

    do {
        found = s.find(toBeReplaced);
        if (found != std::string::npos) {
            s.replace(s.find(toBeReplaced), toBeReplaced.length(), replacement);
        }
    } while (found != std::string::npos);

    ss.str(s);
}

string toString(Rotation rotation) {
    for(pair<string, Rotation> p : rotations) {
        if(p.second == rotation) {
            return p.first;
        }
    }
    
    return "";
}

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
        initialPositionSet = true;
        invocations = 0;
    }

    ensureOnTop(cube, colorOnTop);
    findPositionBeforeRotation(cube);
    rotate(cube);
    shorten(ss);
    
    return getMovesAsString();
}

string CubeAlgorithm::getMovesAsString() {
    return ss.str();
}

void CubeAlgorithm::doMove(Cube &cube, string move, bool recordInString = true) {
    map<string, Rotation>::const_iterator itRot = rotations.find(move);

    if (itRot != rotations.end()) {
        cube.rotate(itRot->second);
        if (recordInString)
            ss << move << ",";
    }

    map<string, Flip>::const_iterator itFlp = flips.find(move);

    if (itFlp != flips.end()) {
        cube.flip(itFlp->second);
        if (recordInString)
            ss << move << ",";
    }
    
    ++invocations;
    
    if(isStalemate()) {
        throw StalemateException();
    }
}

void CubeAlgorithm::doMoves(Cube &cube, vector<string> moves, int repeat = 1,
        bool recordInString = true) {
    for (int i = 0; i < repeat; ++i) {
        for (string move : moves) {
            doMove(cube, move, recordInString);
        }
    }
}

bool CubeAlgorithm::isStalemate() {
    return invocations > MAX_ALLOWED_INVOCATIONS;
}

void CubeAlgorithm::cancelLastMoves(Cube &cube, int moves) {
    string allMoves = ss.str();
    int revertToPos = allMoves.length() - 2 * moves;
    revertToPos = max(revertToPos, 0);
    string toBeReverted = allMoves.substr(revertToPos);
    stringstream tokenizer(toBeReverted);

    while (tokenizer.good()) {
        string move;
        string newMove;
        getline(tokenizer, move, ',');

        if (move == FLIP_UPSIDE_DOWN) {
            newMove = FLIP_UPSIDE_DOWN;
        } else if (move.length() == 2) {
            // change counterclockwise to clockwise, like U' => U
            newMove = move.substr(0, 1);
        } else if (move.length() == 1) {
            // change clockwise to counterclockwise, like U => U'
            newMove = move + "'";
        }

        CubeAlgorithm::doMove(cube, newMove, false);
    }

    ss.seekp(revertToPos);
}

void CubeAlgorithm::ensureOnTop(Cube &cube, Color color) {
    Flip flip = cube.whatFlipGivesColorOnTop(color);
    
    for(pair<string, Flip> p : flips) {
        if(p.second == flip) {
            doMove(cube, p.first);
            break;
        }
    }
}

void Dasy::rotate(Cube &cube) {
    const PetalSolution* solution = nextMissingWhiteEdge(cube);

    if (!solution) {
        return;
    }

    for (int i = 0; i < 3; ++i) {
        if (cube.getColor(solution->cantBeWhite) == WHITE) {
            CubeAlgorithm::doMove(cube, ROTATE_UP_CLOCKWISE);
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
            debug << "Another rotation - side was not found";
            CubeAlgorithm::doMove(cube, ROTATE_UP_CLOCKWISE);
        }
    }
}

Side WhiteCross::findMatchingSide(Cube cube) {
    map<Side, Edge> topLayerSides = { 
        {FRONT, THIRD_LAYER_FRONT_EDGE},
        {RIGHT, THIRD_LAYER_RIGHT_EDGE},
        {BACK, THIRD_LAYER_BACK_EDGE},
        {LEFT, THIRD_LAYER_LEFT_EDGE}
    }; 
            
    for (map<Side, Edge> ::iterator it = topLayerSides.begin(); it != topLayerSides.end(); ++it) {
        Side side = it->first;
        Edge edge = it->second;
        
        debug << cube.asString();
        debug << getSideName(side) << ", " << getColorName(cube.cube[side][0][1]) << " is " << getColorName(cube.getSideLeadingColor(side));
        if (cube.getColor(edge.getCubePosition(side)) == cube.getSideLeadingColor(side) 
                && cube.getColor(edge.getCubePosition(Side::UP)) == Color::WHITE) {
            return side;
        }
    }

    throw SideNotFoundException();
}

void WhiteCross::rotate(Cube &cube) {
    string rotation;

    switch (matchingSide) {
        case FRONT:
            rotation = ROTATE_FRONT_CLOCKWISE;
            break;
        case LEFT:
            rotation = ROTATE_LEFT_CLOCKWISE;
            break;
        case RIGHT:
            rotation = ROTATE_RIGHT_CLOCKWISE;
            break;
        case BACK:
            rotation = ROTATE_BACK_CLOCKWISE;
            break;
        default:
            break;
    }

    CubeAlgorithm::doMoves(cube, {rotation}, 2);
}

void FirstLayerCorners::findPositionBeforeRotation(Cube &cube) {
    bool match = false;
    int timesRotated = 0;
    cornerMoveType = CornerMoveType::PUT_SOLVABE_DOWN;
    
    while (!match) {
                
        if (LOWER_CORNERS[0].countFullyMatchedSides(cube) == 3) {
            // already solved, move to the next corner
            debug << "No full match"; 
            CubeAlgorithm::doMove(cube, FLIP_Y_CLOCKWISE_90);
        }
        
        bool upperForSwap = isCandidateForSwap(UPPER_CORNERS[0], cube);
        bool upperHasWhite = UPPER_CORNERS[0].hasColorOnAnySide(Color::WHITE, cube);
        bool lowerHasWhite = LOWER_CORNERS[0].hasColorOnAnySide(Color::WHITE, cube);
        debug << "upperForSwap: " << upperForSwap << ", lowerHasWhite: " << lowerHasWhite;
        
        /**
         * Here is the reasoning behind it:
         * upperForSwap | lowerHasWhite | rotate?             |
         * 0            | 0             | 1                   |
         * 1            | 0             | 0                   |
         * 0            | 1             | upperHasWhite       | 
         * 1            | 1             | 0                   |
         */
        if (!upperForSwap && (!lowerHasWhite || (lowerHasWhite && upperHasWhite))) {
            //debug << "Rotate up clockwise.";
            CubeAlgorithm::doMove(cube, ROTATE_UP_CLOCKWISE);
            //debug << cube.asString();
            
            ++timesRotated;
            if(timesRotated > 3) {
                debug << "Canceling last moves:";
                CubeAlgorithm::cancelLastMoves(cube, 4);
                debug << cube.asString();
                
                debug << "Flipping cube clockwise y 90 degrees:";
                CubeAlgorithm::doMove(cube, FLIP_Y_CLOCKWISE_90);
                debug << cube.asString();
                
                timesRotated = 0;
            }
        } else {
            match = true;
        }
    }
    
    if (isCandidateForSwap(UPPER_CORNERS[0], cube)) {
        cornerMoveType = CornerMoveType::PUT_SOLVABE_DOWN;
    } else if (LOWER_CORNERS[0].hasColorOnAnySide(Color::WHITE, cube)) {
        cornerMoveType = CornerMoveType::EXTRACT_UNSOLVABLE_UP;
    }
}

void FirstLayerCorners::rotate(Cube &cube) {
    int maxAllowedMoves = cornerMoveType == CornerMoveType::EXTRACT_UNSOLVABLE_UP ? 1 : 6;
    
    while (maxAllowedMoves && LOWER_CORNERS[0].countFullyMatchedSides(cube) < 3) {
        debug << cube.asString();
        debug << "Fully matched: " << LOWER_CORNERS[0].countFullyMatchedSides(cube);
        CubeAlgorithm::doMoves(cube, RIGHTY);
        --maxAllowedMoves;
    }
}

bool FirstLayerCorners::isCandidateForSwap(Corner corner, Cube cube) {
    return corner.hasColorOnAnySide(cube.getSideLeadingColor(FRONT), cube) &&
           corner.hasColorOnAnySide(cube.getSideLeadingColor(RIGHT), cube) &&
           corner.hasColorOnAnySide(cube.getSideLeadingColor(DOWN), cube);
}

void SecondLayerEdges::findPositionBeforeRotation(Cube &cube) {
    int rotations = 0;
    currentSwap = Swap::NOTHING;

    while (currentSwap == Swap::NOTHING) {

        if (sideSolved(cube) || rotations >= 3) {
            debug << "Nothing to do, side is already solved. Rotating 90 clockwise over y.";
            CubeAlgorithm::doMove(cube, FLIP_Y_CLOCKWISE_90);
            debug << cube.asString();
            rotations = 0;
            continue;
        }

        currentSwap = findSwap(cube);
        
        debug << "Current swap: " << currentSwap;

        if (currentSwap == Swap::NOTHING) {
            CubeAlgorithm::doMove(cube, ROTATE_UP_CLOCKWISE);
            debug << "After U rotation: ";
            debug << cube.asString();
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

    if (SECOND_LAYER_LEFT_EDGE.countFullyMatchedSides(cube) < 2) {
        if (!SECOND_LAYER_LEFT_EDGE.hasColorOnAnySide(Color::YELLOW, cube)
            && THIRD_LAYER_FRONT_EDGE.hasColorOnAnySide(Color::YELLOW, cube)) {
            return Swap::LEFT_FRONT_EDGE;
        }
    } else {
        return Swap::NOTHING;
    }

    if (SECOND_LAYER_RIGHT_EDGE.countFullyMatchedSides(cube) < 2) {
        if (!SECOND_LAYER_RIGHT_EDGE.hasColorOnAnySide(Color::YELLOW, cube)
            && THIRD_LAYER_FRONT_EDGE.hasColorOnAnySide(Color::YELLOW, cube)) {
            return Swap::RIGHT_FRONT_EDGE;
        }
    } else {
        return Swap::NOTHING;
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
    replaceAllInStringStream(ss, "U,U,U,y,U", "y");
}

void YellowDot::rotate(Cube & cube) {
    CubeAlgorithm::doMove(cube, ROTATE_FRONT_CLOCKWISE);
    CubeAlgorithm::doMoves(cube, RIGHTY);
    CubeAlgorithm::doMove(cube, ROTATE_FRONT_COUNTER_CLOCKWISE);
}

void YellowLine::findInitialPosition(Cube & cube) {
    for (int i = 0; i < 2; ++i) {
        if (!isYellowLine(cube)) {
            CubeAlgorithm::doMove(cube, ROTATE_UP_CLOCKWISE);
        }
    }
}

bool YellowLine::isYellowLine(Cube cube) {
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[UP];
    return (side[1][0] == side[1][2]) && (side[1][0] == side[1][1])
            && (side[1][0] == YELLOW);
}

void YellowLine::rotate(Cube & cube) {
    CubeAlgorithm::doMove(cube, ROTATE_FRONT_CLOCKWISE);
    CubeAlgorithm::doMoves(cube, RIGHTY);
    CubeAlgorithm::doMove(cube, ROTATE_FRONT_COUNTER_CLOCKWISE);
}

void YellowArc::findInitialPosition(Cube & cube) {
    for (int i = 0; i < 3; ++i) {
        if (!isYellowArc(cube)) {
            CubeAlgorithm::doMove(cube, ROTATE_UP_CLOCKWISE);
        }
    }
}

bool YellowArc::isYellowArc(Cube cube) {
    array <array<Color, Cube::SIZE>, Cube::SIZE> side = cube.cube[UP];
    return (side[1][1] == side[1][2]) && (side[1][1] == side[2][1])
            && (side[1][1] == YELLOW);
}

void YellowArc::rotate(Cube & cube) {
    CubeAlgorithm::doMove(cube, FLIP_Z_CLOCKWISE_90);
    CubeAlgorithm::doMove(cube, ROTATE_BACK_CLOCKWISE);
    CubeAlgorithm::doMoves(cube, RIGHTY);
    CubeAlgorithm::doMove(cube, ROTATE_BACK_COUNTER_CLOCKWISE);
    CubeAlgorithm::doMove(cube, FLIP_Z_COUNTER_CLOCKWISE_90);
}

void PositionLastLayerCorners::findInitialPosition(Cube &cube) {
    findOptimalLastLayerRotation(cube);
    findOptimalCubeFlip(cube);
}

void PositionLastLayerCorners::findOptimalLastLayerRotation(Cube &cube) {
    int currentMatch = 0;
    int bestMatch = 0;
    int bestMatchOnTurn = 0;

    for (int i = 0; i < 4; ++i) {
        array<int, 4> matchedCorners = countUpperCornersInRightPlace(cube);

        for_each(matchedCorners.begin(), matchedCorners.end(),
                [&](int c) {
                    currentMatch += c / 3; }
        );
        
//        debug << "On best match i=" << i << ", currentMatch: " << currentMatch;
//        cube.printCube();

        if (currentMatch > bestMatch) {
            bestMatch = currentMatch;
            bestMatchOnTurn = i;
        }
        
        if (bestMatch == 4) {
            alreadySolved = true;
        }
        
        currentMatch = 0;
        CubeAlgorithm::doMove(cube, ROTATE_UP_CLOCKWISE);
    }

    cancelLastMoves(cube, 4 - bestMatchOnTurn);
}

void PositionLastLayerCorners::findOptimalCubeFlip(Cube &cube) {
    while (!alreadySolved) {
        if (UPPER_CORNERS[0].countPartiallyMatchedSides(cube) == 3) {
            CubeAlgorithm::doMove(cube, FLIP_Y_CLOCKWISE_90);
            continue;
        }
        
        if (UPPER_CORNERS[1].countPartiallyMatchedSides(cube) == 3 && 
                UPPER_CORNERS[2].countPartiallyMatchedSides(cube) == 3) {
            CubeAlgorithm::doMove(cube, FLIP_Y_CLOCKWISE_90);
            continue;
        }
        
        break;
    }
}

void PositionLastLayerCorners::rotate(Cube &cube) {
//    debug << "Before rotate on PositionLastLayerCorners: ";
//    cube.printCube();
    
    if (alreadySolved) {
        debug << "Looks like cube already has last layer corners in position";
        return;
    }
    
    int repeat = 0;
        
    if (UPPER_CORNERS[1].countPartiallyMatchedSides(cube) < 3) {
        repeat = 1;
    } else if (UPPER_CORNERS[2].countPartiallyMatchedSides(cube) < 3) {
        repeat = 2;
    }
    
    for(int i=0; i < repeat; ++i) {
        CubeAlgorithm::doMoves(cube, CubeAlgorithm::RIGHTY, 3);
        CubeAlgorithm::doMove(cube, FLIP_Y_CLOCKWISE_90);
        CubeAlgorithm::doMoves(cube, CubeAlgorithm::LEFTY, 3);
    }
    
    findOptimalLastLayerRotation(cube);
}

array<int, 4> PositionLastLayerCorners::countUpperCornersInRightPlace(Cube cube) {
    array<int, 4> corners = {
        UPPER_CORNERS[0].countPartiallyMatchedSides(cube),
        UPPER_CORNERS[1].countPartiallyMatchedSides(cube),
        UPPER_CORNERS[2].countPartiallyMatchedSides(cube),
        UPPER_CORNERS[3].countPartiallyMatchedSides(cube)
    };

    return corners;
}

void PositionLastLayerCorners::shorten(stringstream &ss) {
    replaceAllInStringStream(ss, "U,U,U,U,U", "U");
}

void PermuteLastLayerCorners::rotate(Cube &cube) {
    orientLowerCubletsYellowDown(cube);
    findOptimalFirstLayerRotation(cube);
}

void PermuteLastLayerCorners::orientLowerCubletsYellowDown(Cube &cube) {
    for(int i=0; i<4; ++i) {
        while(!hasLowerFrontRightCornerFacingYellowDown(cube)) {
            CubeAlgorithm::doMoves(cube, CubeAlgorithm::RIGHTY);
        }
        if (i != 3) {
            CubeAlgorithm::doMove(cube, ROTATE_DOWN_COUNTER_CLOCKWISE);
        }
    }
}

void PermuteLastLayerCorners::findOptimalFirstLayerRotation(Cube &cube) {
    int optimalMatchOnTurn = 0;

    for (int i = 0; i < 4; ++i) {
        int cornerPiecesInPlace = 0;
        for_each(LOWER_CORNERS.begin(), LOWER_CORNERS.end(), 
                [&](Corner corner) {
                   cornerPiecesInPlace += corner.countFullyMatchedSides(cube);
                });
                
        if (cornerPiecesInPlace == 12) {
            optimalMatchOnTurn = i;
            break;
        }
        
        CubeAlgorithm::doMove(cube, ROTATE_DOWN_COUNTER_CLOCKWISE);
    }
    
    cancelLastMoves(cube, 3 - optimalMatchOnTurn);
}

bool PermuteLastLayerCorners::hasLowerFrontRightCornerFacingYellowDown(Cube cube) {
    CubePosition corner = LOWER_CORNERS[0].getCubePosition(Side::DOWN);
    return cube.getColor(corner) == Color::YELLOW;
}

void PositionLastLayerEdges::rotate(Cube& cube) {
    findOptimalLastLayerRotation(cube);

    while (countSolvedUpperEdges(cube) < 4) {
        CubeAlgorithm::doMoves(cube, CubeAlgorithm::RIGHTY);
        CubeAlgorithm::doMoves(cube, CubeAlgorithm::LEFTY);
        CubeAlgorithm::doMoves(cube, CubeAlgorithm::RIGHTY, 5);
        CubeAlgorithm::doMoves(cube, CubeAlgorithm::LEFTY, 5);
        
        findOptimalLastLayerRotation(cube);
    }
}

void PositionLastLayerEdges::findOptimalLastLayerRotation(Cube &cube) {
    for (int i = 0; i < 4; ++i) {           
        if (countSolvedUpperCorners(cube) == 4) {
            break;
        }
                
        CubeAlgorithm::doMove(cube, ROTATE_UP_CLOCKWISE);
    }
    
    array<Side, 4> sides = {FRONT, RIGHT, BACK, LEFT};
    
    int flipToSolvedSide = 0;
    
    for (int i=0; i<sides.size(); ++i) {
        if (cube.isSideCompleted(sides[i])) {
            flipToSolvedSide = i;
            break;
        }
    }
    
    CubeAlgorithm::doMoves(cube, 
            vector<string>{FLIP_Y_CLOCKWISE_90}, flipToSolvedSide);
}


int PositionLastLayerEdges::countSolvedUpperEdges(Cube cube) {
    int solved = 0;
    
    for_each(UPPER_EDGES.begin(), UPPER_EDGES.end(), [&](Cublet cublet) {
        solved += (cublet.countFullyMatchedSides(cube) == 2) ? 1 : 0;
    });

    return solved;
}

int PositionLastLayerEdges::countSolvedUpperCorners(Cube cube) {
    int solved = 0;
    
    for_each(UPPER_CORNERS.begin(), UPPER_CORNERS.end(), [&](Cublet cublet) {
        solved += (cublet.countFullyMatchedSides(cube) == 3) ? 1 : 0;
    });

    return solved;
}