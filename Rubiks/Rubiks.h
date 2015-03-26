//
//  Rubiks.h
//  Rubiks
//
//  Created by Ellis Sparky Hoag on 8/4/14.
//  Copyright (c) 2014 Ellis Sparky Hoag. All rights reserved.
//

#ifndef __Rubiks__Rubiks__
#define __Rubiks__Rubiks__

#include <iostream>
#include "assert.h"
#include <time.h>
#include <list>


#include "Definitions.h"

/*
 *  cubeState
 *  List of 6 integers 32 bits wide representing the state of the rubik's cube
 *  There are 6 colors that are each represented by a 3-bit-wide integer
 *  For example:
 *      cubeState[TOP] = _ _ _ / _ _ _ / _ _ _ / _ _ _ / _ _ _ / _ _ _ / _ _ _ / _ _ _ / _ _ _ / 
 *                      TopLeft/TopMid/TopRight/MidLeft/MidMid/MidRight/BotLeft/BotMid/BotRight/
 */


enum RUBIKS_CUBE_FACE {
    TOP = 0,
    FRONT = 1,
    RIGHT = 2,
    BACK = 3,
    LEFT = 4,
    BOTTOM = 5
};

enum RUBIKS_CUBE_MOVE_DIRECTION {
    CLOCKWISE = 1,
    HALF_TURN = 2,
    COUNTERCLOCKWISE = 3
};

struct moveAndDirection {
    RUBIKS_CUBE_FACE face;
    RUBIKS_CUBE_MOVE_DIRECTION direction;
};


class Rubiks {
    
public:
    
    Rubiks();
    
    uint32_t * cubeState;
    
    uint32_t * getRubiksCubeColorArray();
    
    uint32_t * getSolvedCube();
    
    void moveRubiksCube(RUBIKS_CUBE_FACE FACE, RUBIKS_CUBE_MOVE_DIRECTION DIRECTION, uint32_t * cState);
    
    uint32_t moveFaceClockwise(uint32_t face);
    
    uint32_t switchSquares(uint32_t face, int squareAIndex, int squareBIndex);
    
    void switchRow(uint32_t * cState, RUBIKS_CUBE_FACE FACE);
    
    void switchSquaresDifferentFace(RUBIKS_CUBE_FACE FACE_A, int squareAIndex, RUBIKS_CUBE_FACE FACE_B, int squareBIndex, uint32_t * cState);
    
    double x_rot, y_rot, z_rot;
        
    bool cubieIsInFace(int cubie, RUBIKS_CUBE_FACE FACE, int * x, int * y, int * z);
    
    void solveCube();
    
    std::list<moveAndDirection> movesStack;
    
    bool solvingCube;
    
    uint32_t * makeCubeState(const uint8_t * goal);
    
    bool accomplishGoal(uint32_t * location, uint32_t * destination, int steps, std::list<moveAndDirection> & moves, int lastMovedFace);
    
    bool cubeStatesAreEqual(uint32_t * location, uint32_t * destination);
    
    bool placeEdge(uint32_t * cState, RUBIKS_CUBE_FACE face, bool rightHand, std::list<moveAndDirection> & moves);
};

#endif /* defined(__Rubiks__Rubiks__) */
