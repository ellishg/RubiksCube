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
    
    clock_t t;
    
    for (int i = 0; i < 6; i++) {
        tmpCubeState[i] = cubeState[i];
    }
    
    //Lets iterate through our goals
    //A full solution takes way to long right now
    //iterating i to NUM_GOALS will solve the whole cube
    //              4 will solve the first layer
    //              8 will solve first and second layers
    //              12 will solve courners
    for (int i = 0; i < 4; i++) {
        const uint8_t * currentGoal = layerGoals[i];
        //const uint8_t * currentGoal = ortegaGoal[i];
        
        cubeStateGoal = makeCubeState(currentGoal);
        
        int steps = 0;
        
        std::list<moveAndDirection> tmpMovesStack;
        
        bool result = false;
        
        t = clock();
        
        while (!result && ++steps <= GODS_NUMBER) {
            
            //computing 7 steps takes about a minute as of right now
            //computing 8 steps may take 10 minutes
            
            tmpMovesStack.clear();
            
            result = accomplishGoal(tmpCubeState, cubeStateGoal, steps, tmpMovesStack, -1);
            
            printf("%i, ", steps);
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

bool Rubiks::accomplishGoal(uint32_t * location, uint32_t * destination, int steps, std::list<moveAndDirection> & moves, int lastMovedFace)    {
    
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
    
    for (int i = 0; i < 6; i++) {
        //Try rotating this face
        
        //need to avoid moving the same side twice
        if (i == lastMovedFace) {
            continue;
        }
        
        for (int j = 1; j <= 3; j++) {
            //in this direction
            
            
            uint32_t * tmpCubeState = new uint32_t[6];
            
            for (int k = 0; k < 6; k++) {
                tmpCubeState[k] = location[k];
            }
            
            moveRubiksCube((RUBIKS_CUBE_FACE)i, (RUBIKS_CUBE_MOVE_DIRECTION)j, tmpCubeState);
            
            bool result = accomplishGoal(tmpCubeState, destination, steps - 1, moves, i);
            
            if (result == true) {
                //We have a solution!
                //Lets note our moves
                moveAndDirection tmpMove;
                tmpMove.face = (RUBIKS_CUBE_FACE)i;
                tmpMove.direction = (RUBIKS_CUBE_MOVE_DIRECTION)j;
                
                moves.push_back(tmpMove);
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

bool Rubiks::placeEdge(uint32_t * cState, RUBIKS_CUBE_FACE face, bool rightHand, std::list<moveAndDirection> & moves)    {
    
    /*
     *  We need to append to the back (bottom) of the list our algorithm
     *  for placing the correct courner in its place.
     *  First we need to find our piece.
     *  Then position that piece in its place in preperation for our algorithm.
     *  Then adjust our skeleton algorithm to be right/left handed and with
     *  respect to the correct face.
     */
    
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
        
        uint8_t faceBottomColor = cState[BOTTOM] >> ((2 * i + 1) * 3) & 0b111;
        
        if (faceBottomColor == face || faceBottomColor == secondaryFace) {
            //we have a potential match for our cubie
            
            int squareNumber = 2 * i + 1;
            
            if (squareNumber == 1) {
                squareNumber = 7;
            }
            else if (squareNumber == 7) {
                squareNumber = 1;
            }
            
            uint8_t faceSideColor = cState[i + 1] >> (squareNumber * 3) & 0b111;
            
            if (faceSideColor == face || faceSideColor == secondaryFace) {
                //This is our piece!
                //Lets position it
                
                if (faceBottomColor == face) {
                    //uuhhhhhhhhh....
                }
                else    {
                    
                }
            }
        }
    }
    
    //We have not found our piece on the bottom layer and we have given up....
    return false;
}
