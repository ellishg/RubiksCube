//
//  solver.cpp
//  Rubiks
//
//  Created by Ellis Sparky Hoag on 12/23/14.
//  Copyright (c) 2014 Ellis Sparky Hoag. All rights reserved.
//

#include "Rubiks.h"


void Rubiks::solveCube()    {
    
    /*
     *  Step 1: Create awesome algorithm that takes the current cube state
     *          and creates an array of moves to solve the cube
     *  Step 2: Set a flag to let the loop function know to use moves from
     *          the moves array
     */
    
    clock_t time = clock();
    
    if (solvingCube) {
        return;
    }
    //  Step 2!
    solvingCube = true;
    
    
    //  Step 1!
    /*
     *  We will accomplish one goal at a time.
     *  Lets try brute force to accomplish our goal.
     *      Copy current cubeState
     *      Enter recursive function to find moves to accomplish goals
     *      with x steps
     *          if it did work push moves and update tmpCubeState
     *      move on to next goal
     */
    
    uint32_t * tmpCubeState = new uint32_t[6];
    uint32_t * cubeStateGoal = new uint32_t[6];
    
    std::list<moveAndDirection> tmpMovesStack;
    
    clock_t t;
    
    for (int i = 0; i < 6; i++) {
        tmpCubeState[i] = cubeState[i];
    }
    
    //LOOK HERE IF YOU WANT TO ADJUST THE LIMITS OF THE SOLVER!!!!!!
    
    //Lets iterate through our goals
    //A full solution takes way to long right now
    //Iterating i to NUM_GOALS will solve the whole cube
    //               4 will solve the first layer
    //               8 will solve first and second layers
    //               12 will solve courners
    //               14 finishes up the rest
    for (int i = 0; i < 4; i++) {
        const uint8_t * currentGoal = layerGoals[i];
        //const uint8_t * currentGoal = ortegaGoal[i];
        
        cubeStateGoal = makeCubeState(currentGoal);
        
        int steps = 0;
        
        bool result = false;
        
        t = clock();
        
        while (!result && ++steps <= GODS_NUMBER) {
            
            //computing 7 steps takes about a minute as of right now
            //computing 8 steps may take 10 minutes
            
            tmpMovesStack.clear();
            
            result = accomplishGoal(tmpCubeState, cubeStateGoal, steps, tmpMovesStack, -1, false, false);
            
            //printf("%i, ", steps);
        }
        
        t = clock() - t;
        
        if (result != true) {
            printf("Could not accomplish goal %i!\n", i);
            
        }
        else    {
            printf("Accomplished goal %i! (%i moves, %f seconds)\n", i, (int)tmpMovesStack.size(), (float)t / CLOCKS_PER_SEC);
            while (!tmpMovesStack.empty()) {
                
                moveRubiksCube(tmpMovesStack.back().face, tmpMovesStack.back().direction, tmpCubeState);
                
                movesStack.push_front(tmpMovesStack.back());
                tmpMovesStack.pop_back();
            }
        }
    }
    
    //Lets try to complete the second layer

    
    bool tryAgain = true;
    
    bool loop = true;
    
    bool correctCubies[4] = {false, false, false, false};
    
    while (loop) {
        
        if (cubeStatesAreEqual(tmpCubeState, makeCubeState(secondLayerDGoal))) {
            break;
        }
        
        tryAgain = false;
        
        for (int face = 1; face < 5; face++) {
        
            //try to place one edge piece
            bool result = placeEdge(tmpCubeState, (RUBIKS_CUBE_FACE)face, tmpMovesStack, false);
            
            if (result == true) {
                correctCubies[face - 1] = true;
                tryAgain = true;
                //lets update our cubeState
                while (!tmpMovesStack.empty()) {
                    moveRubiksCube(tmpMovesStack.back().face, tmpMovesStack.back().direction, tmpCubeState);
                    
                    movesStack.push_front(tmpMovesStack.back());
                    tmpMovesStack.pop_back();

                }
            }
        }
        
        if (tryAgain == false) {
            loop = false;
            for (int i = 0; i < 4; i++) {
                if (correctCubies[i] == false) {
                    loop = true;
                    //preform algorithm here
                    placeEdge(tmpCubeState, (RUBIKS_CUBE_FACE)(i + 1), tmpMovesStack, true);
                    //lets update our cubeState
                    while (!tmpMovesStack.empty()) {
                        moveRubiksCube(tmpMovesStack.back().face, tmpMovesStack.back().direction, tmpCubeState);
                        
                        movesStack.push_front(tmpMovesStack.back());
                        tmpMovesStack.pop_back();
                        
                    }
                    break;
                }
            }
        }
    }
    
    //Lets make yellow cross
    
    if (!cubeStatesAreEqual(tmpCubeState, makeCubeState(yellowCrossGoal))) {
        
        int steps = 5;
        
        bool result = false;
        
        t = clock();
        
        std::list<moveAndDirection> extraMovesStack;
        
        while (!result && ++steps <= GODS_NUMBER) {
            
            //computing 7 steps takes about a minute as of right now
            //computing 8 steps may take 10 minutes
            
            tmpMovesStack.clear();
            
            if (steps > 6) {
                //we need to preform this algorithm
                
                //printf("Preformed algorithm!\n");

                for (int i = 0; i < 12; i++)    {
                    moveAndDirection move;
                    
                    move.face = (RUBIKS_CUBE_FACE)yellowCrossMove[2 * i];
                    move.direction = (RUBIKS_CUBE_MOVE_DIRECTION)yellowCrossMove[2 * i + 1];
                    
                    moveRubiksCube(move.face, move.direction, tmpCubeState);
                    
                    extraMovesStack.push_front(move);
                    
                    steps = 1;
                }
            }
            
            result = accomplishGoal(tmpCubeState, makeCubeState(yellowCrossGoal), steps, tmpMovesStack, -1, false, false);
            
            //printf("%i, ", steps);
        }
        
        t = clock() - t;
        
        if (result != true) {
            printf("Could not accomplish yellow cross!\n");
            
        }
        else    {
            printf("Accomplished yellow cross! (%i initial moves + %i moves, %f seconds)\n", (int)extraMovesStack.size(), (int)tmpMovesStack.size(), (float)t / CLOCKS_PER_SEC);
            while (!extraMovesStack.empty()) {
                //moveRubiksCube(extraMovesStack.back().face, extraMovesStack.back().direction, tmpCubeState);
                
                tmpMovesStack.push_back(extraMovesStack.front());
                extraMovesStack.pop_front();
            }
            while (!tmpMovesStack.empty()) {
                
                moveRubiksCube(tmpMovesStack.back().face, tmpMovesStack.back().direction, tmpCubeState);
                
                movesStack.push_front(tmpMovesStack.back());
                tmpMovesStack.pop_back();
            }
        }
    }
    
    //Now lets permutate corners
    
    if (!permutateCorners(tmpCubeState, movesStack)) {
        printf("Unable to permutate corners!\n");
    }
    
    
    //Now lets impliment brute force on orientation algorithm
    
    cubeStateGoal = makeCubeState(orientatedCornersGoal);
    
    int steps = 0;
    
    bool result = false;
    
    t = clock();
    
    while (!result && ++steps <= GODS_NUMBER) {
        
        //computing 7 steps takes about a minute as of right now
        //computing 8 steps may take 10 minutes
        
        tmpMovesStack.clear();
        
        result = accomplishGoal(tmpCubeState, cubeStateGoal, steps, tmpMovesStack, -1, true, false);
        
        //printf("%i, ", steps);
    }
    
    t = clock() - t;
    
    if (result != true) {
        printf("Could not accomplish oriented corners goal!\n");
        
    }
    else    {
        printf("Accomplished goal! (%i moves, %f seconds)\n", (int)tmpMovesStack.size(), (float)t / CLOCKS_PER_SEC);
        while (!tmpMovesStack.empty()) {
            
            moveRubiksCube(tmpMovesStack.back().face, tmpMovesStack.back().direction, tmpCubeState);
            
            movesStack.push_front(tmpMovesStack.back());
            tmpMovesStack.pop_back();
        }
    }
    
    
    //Finaly orientate edges!
    
    cubeStateGoal = makeCubeState(finalGoal);
    
    steps = 0;
    
    result = false;
    
    t = clock();
    
    while (!result && ++steps <= GODS_NUMBER) {
        
        //computing 7 steps takes about a minute as of right now
        //computing 8 steps may take 10 minutes
        
        tmpMovesStack.clear();
        
        result = accomplishGoal(tmpCubeState, cubeStateGoal, steps, tmpMovesStack, -1, false, true);
        
        //printf("%i, ", steps);
    }
    
    t = clock() - t;
    
    if (result != true) {
        printf("Could not accomplish final goal!\n");
        
    }
    else    {
        printf("Accomplished final goal! (%i moves, %f seconds)\n", (int)tmpMovesStack.size(), (float)t / CLOCKS_PER_SEC);
        while (!tmpMovesStack.empty()) {
            
            moveRubiksCube(tmpMovesStack.back().face, tmpMovesStack.back().direction, tmpCubeState);
            
            movesStack.push_front(tmpMovesStack.back());
            tmpMovesStack.pop_back();
        }
    }

    //Lets clean up our moves!
    
    std::list<moveAndDirection> tmpMoves = movesStack;
    
    movesStack.clear();
    
    int newDirection;
    
    while (!tmpMoves.empty())   {
        
        moveAndDirection prevMove = tmpMoves.back();
        tmpMoves.pop_back();
        
        if (tmpMoves.back().face == prevMove.face) {
            newDirection = (prevMove.direction + tmpMoves.back().direction) % 4;
            if (newDirection == 0) {
                //useless move
                tmpMoves.pop_back();
                continue;
            }
            else    {
                prevMove.direction = (RUBIKS_CUBE_MOVE_DIRECTION)newDirection;
                tmpMoves.pop_back();
            }
        }
        movesStack.push_front(prevMove);
    }
    
    printf("%lu moves in %f seconds!\n", movesStack.size(), (float)(clock() - time) / CLOCKS_PER_SEC);
    
}

uint32_t * Rubiks::makeCubeState(const uint8_t * goal)  {
    
    uint32_t * cubeState = new uint32_t[6];
    
    for (int i = 0; i < 6; i++) {
        //each side
        cubeState[i] = 0;
        for (int j = 0; j < 9; j++) {
            //each cubie face
            cubeState[i] += goal[j + i * 9] << (j * 3);
        }
    }
    
    return cubeState;
}

bool Rubiks::accomplishGoal(uint32_t * location, uint32_t * destination, int steps, std::list<moveAndDirection> & moves, int lastMovedFace, bool useCornerAlgorithm, bool useEdgesAlgorithm)    {
    
    //first we need to test if we have reached our destination
    
    if (cubeStatesAreEqual(location, destination)) {
        //Base case
        //We have accomplished our goal!
        //printf("steps: %i\n", steps);
        return true;
    }
    else if (steps == 0)    {
        //We have not accomplished our goal :(
        return false;
    }
    
    int numMoves = 6;
    
    if (useCornerAlgorithm || useEdgesAlgorithm) {
        numMoves = 3;
    }
    
    for (int i = 0; i < numMoves; i++) {
        //Try rotating this face
        
        //need to avoid moving the same side twice
        if (i == lastMovedFace && !useCornerAlgorithm && !useEdgesAlgorithm) {
            continue;
        }
        
        bool finishLoop = false;
        
        for (int j = 1; j <= 3 && !finishLoop; j++) {
            //in this direction
            
            uint32_t * tmpCubeState = new uint32_t[6];
            
            for (int k = 0; k < 6; k++) {
                tmpCubeState[k] = location[k];
            }
            
            if (useCornerAlgorithm) {
                if (i == 0) {
                    //move bottom face
                    moveRubiksCube(BOTTOM, (RUBIKS_CUBE_MOVE_DIRECTION)j, tmpCubeState);
                }
                else if (i == 1)    {
                    //right hand move
                    for (int k = 0; k < 8; k++) {
                        moveRubiksCube((RUBIKS_CUBE_FACE)orientateCornersRightHand[2 * k], (RUBIKS_CUBE_MOVE_DIRECTION)orientateCornersRightHand[2 * k + 1], tmpCubeState);
                    }
                    finishLoop = true;
                }
                else    {
                    //left hand move
                    for (int k = 0; k < 8; k++) {
                        moveRubiksCube((RUBIKS_CUBE_FACE)orientateCornersLeftHand[2 * k], (RUBIKS_CUBE_MOVE_DIRECTION)orientateCornersLeftHand[2 * k + 1], tmpCubeState);
                    }
                    finishLoop = true;
                }
            }
            else if (useEdgesAlgorithm) {
                if (i == 0) {
                    //move bottom face
                    moveRubiksCube(BOTTOM, (RUBIKS_CUBE_MOVE_DIRECTION)j, tmpCubeState);
                }
                else if (i == 1)    {
                    //right hand move
                    for (int k = 0; k < 9; k++) {
                        moveRubiksCube((RUBIKS_CUBE_FACE)orientateEdgesA[2 * k], (RUBIKS_CUBE_MOVE_DIRECTION)orientateEdgesA[2 * k + 1], tmpCubeState);
                    }
                    finishLoop = true;
                }
                else    {
                    //left hand move
                    for (int k = 0; k < 9; k++) {
                        moveRubiksCube((RUBIKS_CUBE_FACE)orientateEdgesB[2 * k], (RUBIKS_CUBE_MOVE_DIRECTION)orientateEdgesB[2 * k + 1], tmpCubeState);
                    }
                    finishLoop = true;
                }
            }
            else    {
                moveRubiksCube((RUBIKS_CUBE_FACE)i, (RUBIKS_CUBE_MOVE_DIRECTION)j, tmpCubeState);
            }
            
            bool result = accomplishGoal(tmpCubeState, destination, steps - 1, moves, i, useCornerAlgorithm, useEdgesAlgorithm);
            
            if (result == true) {
                
                moveAndDirection tmpMove;
                
                if (useCornerAlgorithm)    {
                    if (i == 0) {
                        tmpMove.face = BOTTOM;
                        tmpMove.direction = (RUBIKS_CUBE_MOVE_DIRECTION)j;
                        moves.push_back(tmpMove);
                    }
                    else if (i == 1)  {
                        //last move first
                        for (int k = 7; k >= 0; k--) {
                            tmpMove.face = (RUBIKS_CUBE_FACE)orientateCornersRightHand[2 * k];
                            tmpMove.direction = (RUBIKS_CUBE_MOVE_DIRECTION)orientateCornersRightHand[2 * k + 1];
                            moves.push_back(tmpMove);
                        }
                    }
                    else    {
                        for (int k = 7; k >= 0; k--) {
                            tmpMove.face = (RUBIKS_CUBE_FACE)orientateCornersLeftHand[2 * k];
                            tmpMove.direction = (RUBIKS_CUBE_MOVE_DIRECTION)orientateCornersLeftHand[2 * k + 1];
                            moves.push_back(tmpMove);
                        }
                    }
                }
                else if (useEdgesAlgorithm)    {
                    if (i == 0) {
                        tmpMove.face = BOTTOM;
                        tmpMove.direction = (RUBIKS_CUBE_MOVE_DIRECTION)j;
                        moves.push_back(tmpMove);
                    }
                    else if (i == 1)  {
                        //last move first
                        for (int k = 8; k >= 0; k--) {
                            tmpMove.face = (RUBIKS_CUBE_FACE)orientateEdgesA[2 * k];
                            tmpMove.direction = (RUBIKS_CUBE_MOVE_DIRECTION)orientateEdgesA[2 * k + 1];
                            moves.push_back(tmpMove);
                        }
                    }
                    else    {
                        for (int k = 8; k >= 0; k--) {
                            tmpMove.face = (RUBIKS_CUBE_FACE)orientateEdgesB[2 * k];
                            tmpMove.direction = (RUBIKS_CUBE_MOVE_DIRECTION)orientateEdgesB[2 * k + 1];
                            moves.push_back(tmpMove);
                        }
                    }
                }
                else {
                    //We have a solution!
                    //Lets note our moves
                    tmpMove.face = (RUBIKS_CUBE_FACE)i;
                    tmpMove.direction = (RUBIKS_CUBE_MOVE_DIRECTION)j;
                    
                    moves.push_back(tmpMove);
                }
                return true;
            }
        }
    }
    
    return false;   //this should never excecute
}

bool Rubiks::cubeStatesAreEqual(uint32_t * location, uint32_t * destination) {
    for (int j = 0; j < 9; j++) {
        //for each cubie face
        if (j == 4) {
            //this is the center cubie
            continue;
        }
        for (int i = 0; i < 6; i++) {
            //for each side
            uint8_t destinationCubie = (destination[i] >> (j * 3)) & 0b111;
            uint8_t locationCubie = (location[i] >> (j * 3)) & 0b111;
            
            if (destinationCubie != WILDCARD) {

                if (destinationCubie != locationCubie) {
                    //printf("i = %i, j = %i\na: %i, b: %i\n\n", i, j, destinationCubie, locationCubie);
                    return false;
                }
            }
        }
    }
    return true;
}

bool Rubiks::placeEdge(uint32_t * cState, RUBIKS_CUBE_FACE face, std::list<moveAndDirection> & moves, bool override)    {
    
    /*
     *  We need to append to the back (bottom) of the list our algorithm
     *  for placing the correct courner in its place.
     *  First we need to find our piece.
     *  Then position that piece in its place in preperation for our algorithm.
     *  Then adjust our skeleton algorithm to be right/left handed and with
     *  respect to the correct face.
     */
    
    bool rightHand = true;
    
    RUBIKS_CUBE_FACE secondaryFace = (RUBIKS_CUBE_FACE)(rightHand ? face + 1 : face - 1);
    
    if (secondaryFace == TOP) {
        secondaryFace = LEFT;
    }
    else if (secondaryFace == BOTTOM)   {
        secondaryFace = FRONT;
    }
    
    //Lets find our piece by checking the bottom layer
    //If it's not there then lets give up for now...
    
    for (int i = 0; i < 4; i++) {
        //for each edge on the bottom layer
        //the edge number is odd so it is 2 * i + 1
        
        int squareNumber;
        
        switch (i) {
            case 0:
                squareNumber = 1;
                break;
            case 1:
                squareNumber = 5;
                break;
            case 2:
                squareNumber = 7;
                break;
            default:
                squareNumber = 3;
                break;
        }
        
        uint8_t faceBottomColor = (cState[BOTTOM] >> (squareNumber * 3)) & 0b111;
        
        if (faceBottomColor == face || faceBottomColor == secondaryFace || override) {
            //we have a potential match for our cubie
            
            switch (i) {
                case 0:
                    squareNumber = 7;
                    break;
                case 1:
                    squareNumber = 5;
                    break;
                case 2:
                    squareNumber = 1;
                    break;
                default:
                    squareNumber = 3;
                    break;
            }
            
            uint8_t faceSideColor = (cState[i + 1] >> (squareNumber * 3)) & 0b111;
            
            if (faceSideColor == face || faceSideColor == secondaryFace || override) {
                //This is our piece!
                //Lets position it
                
                //uuhhhhhhhhh....
                //We may need to rotate the bottom so that
                //our piece is opposite to the face
                
                int distToHome = (int)face - (i + 1);
                
                if (distToHome == -3) {
                    distToHome = 1;
                }
                else if (distToHome == -2)  {
                    distToHome = 2;
                }
                else if (distToHome == -1)  {
                    distToHome = 3;
                }
                
                //distToHome is number of clockwise rotations we need
                //to make our piece on the face side
                //now we just need to add a half-turn or something
                
                int rotation;
                
                if (faceBottomColor == face) {
                    rotation = (distToHome + (int)HALF_TURN) % 4;
                }
                else    {
                    rotation = (distToHome + (int)COUNTERCLOCKWISE) % 4;
                    rightHand = false;
                }
                /*else    {
                    //This will never excecute
                    rotation = (distToHome + (int)CLOCKWISE) % 4;
                }*/
                
                //printf("%i, ", rotation);
                
                if (rotation != 0) {
                    //lets make our move!
                    moveAndDirection m;
                    m.face = BOTTOM;
                    m.direction = (RUBIKS_CUBE_MOVE_DIRECTION)rotation;
                    moves.push_front(m);
                }
                
                //return true;
                
                //Now lets do our algorithm!
                
                for (int k = 0; k < 7; k++) {
                    moveAndDirection m;
                    
                    m.direction = (RUBIKS_CUBE_MOVE_DIRECTION)secondLayerRightHandMove[2 * k + 1];
                    
                    if (!rightHand) {
                        if (m.direction == CLOCKWISE) {
                            m.direction = COUNTERCLOCKWISE;
                        }
                        else if (m.direction == COUNTERCLOCKWISE)    {
                            m.direction = CLOCKWISE;
                        }
                    }
                    
                    m.face = (RUBIKS_CUBE_FACE)secondLayerRightHandMove[2 * k];
                    
                    if (!rightHand) {
                        //We need to switch what faces we are rotating
                        switch (m.face) {
                            case FRONT:
                                m.face = RIGHT;
                                break;
                            case RIGHT:
                                m.face = FRONT;
                                break;
                            default:
                                break;
                        }
                    }
                    
                    if (m.face != TOP && m.face != BOTTOM) {
                        
                        m.face = (RUBIKS_CUBE_FACE)(m.face + face - 1);
                        
                        if (m.face == 5) {
                            m.face = FRONT;
                        }
                        else if (m.face == 0)  {
                            m.face = LEFT;
                        }
                    }
                    //printf("%i  :  %i\n", m.face, m.direction);
                    moves.push_front(m);
                }
                //We have completed our algorithm!
                return true;
            }
        }
    }
    //We have not found our piece on the bottom layer and we have given up....
    return false;
}

bool Rubiks::permutateCorners(uint32_t * cState, std::list<moveAndDirection> & moves)    {
    
    int cornerCubieIndexOrder[4 * 3]    {
        //Bottom face, Left face, Right face
        
        0, 6, 6,
        2, 8, 8,
        8, 2, 2,
        6, 0, 0
    };
    
    int faceIndexOrder[4 * 2]   {
        //Left face, right face
        4, 1,
        1, 2,
        2, 3,
        3, 4
    };
    
    /*RUBIKS_CUBIE_COLORS cubieIndexOrder[4 * 3]  {
        //Color order doesn't matter
        YELLOW, GREEN, RED, //5, 4, 1, = 20
        YELLOW, RED, BLUE,  //5, 1, 2, = 10
        YELLOW, BLUE, ORANGE,   //5, 2, 3, = 30
        YELLOW, ORANGE, GREEN   //5, 3, 4 = 60
    };*/
    
    int * currentPermutation = new int[4];
    
    for (int i = 0; i < 4; i++) {
        uint8_t bottomFace = (cState[BOTTOM] >> (cornerCubieIndexOrder[i * 3] * 3)) & 0b111;
        
        uint8_t leftFace = (cState[faceIndexOrder[i * 2]] >> (cornerCubieIndexOrder[i * 3 + 1] * 3)) & 0b111;

        uint8_t rightFace = (cState[faceIndexOrder[i * 2 + 1]] >> (cornerCubieIndexOrder[i * 3 + 2] * 3)) & 0b111;
        
        switch ((int)bottomFace * (int)leftFace * (int)rightFace) {
            case 20:
                currentPermutation[i] = 0;
                break;
            case 10:
                currentPermutation[i] = 1;
                break;
            case 30:
                currentPermutation[i] = 2;
                break;
            case 60:
                currentPermutation[i] = 3;
                break;
            default:
                printf("WTF!\nBottom Face: %i, Left Face: %i, Right Face: %i\n", bottomFace, leftFace, rightFace);
                break;
        }
    }
    
    for (int k = 0; k < 2; k++) {
        //run this a max of 2 times
        int switchIndex = -1;
        
        for (int i = 1; i < 4; i++) {
            //switch the numbers that have the greatest difference!
            int leftDiff = currentPermutation[i] - currentPermutation[(i - 1) % 4];
            int rightDiff = currentPermutation[(i + 1) % 4] - currentPermutation[i];
            
            if ((leftDiff != 1 && leftDiff != -3)
                && (rightDiff != 1 && rightDiff != -3)) {
                switchIndex = i;
                break;
            }
        }
        
        //we need to switch something
        
        if (switchIndex != -1) {
            //printf("Preformed Algorithm! %i\n", switchIndex);
        
            moveAndDirection move;
            
            moveAndDirection finalMove;
            
            finalMove.face = BOTTOM;
            
            move.face = BOTTOM;
            
            bool doNotMove = false;
            bool doNotFinalMove = false;
            
            switch (switchIndex) {
                case 0:
                    move.direction = CLOCKWISE;
                    finalMove.direction = CLOCKWISE;
                    break;
                case 1:
                    finalMove.direction = HALF_TURN;
                    doNotMove = true;
                    break;
                case 2:
                    move.direction = COUNTERCLOCKWISE;
                    finalMove.direction = COUNTERCLOCKWISE;
                    break;
                case 3:
                    move.direction = HALF_TURN;
                    doNotFinalMove = true;
                    break;
                default:
                    printf("WTF!\n");
                    break;
            }
            
            if (!doNotMove) {
                moves.push_front(move);
                moveRubiksCube(move.face, move.direction, cState);
            }
            
            for (int j = 0; j < 7; j++) {
                move.face = (RUBIKS_CUBE_FACE)switchRightCorners[2 * j];
                move.direction = (RUBIKS_CUBE_MOVE_DIRECTION)switchRightCorners[2 * j + 1];
                moves.push_front(move);
                moveRubiksCube(move.face, move.direction, cState);
            }
            
            if (!doNotFinalMove) {
                moves.push_front(finalMove);
                moveRubiksCube(finalMove.face, finalMove.direction, cState);
            }
            
            int tmp = currentPermutation[switchIndex];
            currentPermutation[switchIndex] = currentPermutation[(switchIndex + 1) % 4];
            currentPermutation[(switchIndex + 1) % 4] = tmp;
        }
    }
    
    if (currentPermutation[0] != 0) {
        moveAndDirection m;
        m.face = BOTTOM;
        m.direction = (RUBIKS_CUBE_MOVE_DIRECTION)currentPermutation[0];
        moves.push_front(m);
        moveRubiksCube(m.face, m.direction, cState);
    }
    
    return true;
}