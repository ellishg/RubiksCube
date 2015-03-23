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


#include "Definitions.h"

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

class Rubiks {
    
    uint32_t * cubeState;
    
public:
    
    Rubiks();
    
    uint32_t * getRubiksCubeColorArray();
    
    uint32_t * getSolvedCube();
    
    void moveRubiksCube(RUBIKS_CUBE_FACE FACE, RUBIKS_CUBE_MOVE_DIRECTION DIRECTION);
    
    uint32_t moveFaceClockwise(uint32_t face);
    
    uint32_t switchSquares(uint32_t face, int squareAIndex, int squareBIndex);
    
    void switchRow(uint32_t * cubeState, RUBIKS_CUBE_FACE FACE);
    
    void switchSquaresDifferentFace(RUBIKS_CUBE_FACE FACE_A, int squareAIndex, RUBIKS_CUBE_FACE FACE_B, int squareBIndex);
    
    double x_rot, y_rot, z_rot;
    
    bool cubieIsInFace(int cubie, RUBIKS_CUBE_FACE FACE, int * x, int * y, int * z);
};

#endif /* defined(__Rubiks__Rubiks__) */
