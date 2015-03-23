//
//  OnLoop.cpp
//  Rubiks
//
//  Created by Ellis Sparky Hoag on 8/4/14.
//  Copyright (c) 2014 Ellis Sparky Hoag. All rights reserved.
//

#include "World.h"

void World::OnLoop()    {
    
    /*static int x = 0;
    
    if (!faceIsRotating) {
        switch (x++ % 4) {
            case 0:
                rotateFace(FRONT);
                break;
            case 1:
                rotateFace(RIGHT);
                break;
            case 2:
                rotateFace(BACK);
                break;
            case 3:
                rotateFace(LEFT);
                break;
            default:
                break;
        }
    }*/
    
    if (rubiksCubeIsShuffling && !faceIsRotating) {
        
        static int rotations = 0;
        
        rotateFace((RUBIKS_CUBE_FACE)(rand() % 6));
        
        if (rotations++ >= 60) {
            rubiksCubeIsShuffling = false;
            rotations = 0;
        }
    }
    
    if ((SDL_GetTicks() - startRotateTime > TURN_TIME) && faceIsRotating) {
        faceIsRotating = false;
        rubiks.moveRubiksCube(faceToRotate, CLOCKWISE);
    }
}

void World::rotateFace(RUBIKS_CUBE_FACE FACE) {
    
    if (!faceIsRotating) {
        faceIsRotating = true;
        
        startRotateTime = SDL_GetTicks();
        
        faceToRotate = FACE;
    }
}