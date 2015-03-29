//
//  World.h
//  Rubiks
//
//  Created by Ellis Sparky Hoag on 8/4/14.
//  Copyright (c) 2014 Ellis Sparky Hoag. All rights reserved.
//

#ifndef __Rubiks__World__
#define __Rubiks__World__

#include <stdio.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "Rubiks.h"
#include "Definitions.h"


class World {
    
    uint32_t windowWidth;
    
    uint32_t windowHeight;
    
    SDL_Window * sdlWindow;
    
    SDL_GLContext glContext;
    
    SDL_Event event;
    
    Rubiks rubiks;
    
    uint32_t startRotateTime;
    
    RUBIKS_CUBE_FACE faceToRotate;
    
    RUBIKS_CUBE_MOVE_DIRECTION directionToRotate;
    
    void rotateFace(RUBIKS_CUBE_FACE FACE, RUBIKS_CUBE_MOVE_DIRECTION direction);
    
    bool faceIsRotating;
    
    int rotationTime;
    
    bool rubiksCubeIsShuffling;
    
public:
    
    World();
    
    bool initSDLWindowAndContext();
    
    void initGL();
    
    void OnEvent();
    
    void OnKeyUp(SDL_Keycode sym);
    
    void OnKeyDown(SDL_Keycode sym);
    
    void OnLoop();
    
    void OnRender();
    
    bool OnCleanup();
    
    bool isRunning;
};

#endif /* defined(__Rubiks__World__) */
