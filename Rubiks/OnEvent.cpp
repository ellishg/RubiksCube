//
//  OnEvent.cpp
//  Rubiks
//
//  Created by Ellis Sparky Hoag on 8/4/14.
//  Copyright (c) 2014 Ellis Sparky Hoag. All rights reserved.
//

#include "World.h"

void World::OnEvent()   {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                OnKeyDown(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                OnKeyUp(event.key.keysym.sym);
                break;
            default:
                break;
        }
    }
}

void World::OnKeyDown(SDL_Keycode sym)   {
    
    int rotInc = 15;
    
    switch (sym) {
        case SDLK_ESCAPE:
            isRunning = false;
            break;
        case SDLK_0:
            rotateFace(TOP);
            break;
        case SDLK_1:
            rotateFace(FRONT);
            break;
        case SDLK_2:
            rotateFace(RIGHT);
            break;
        case SDLK_3:
            rotateFace(BACK);
            break;
        case SDLK_4:
            rotateFace(LEFT);
            break;
        case SDLK_5:
            rotateFace(BOTTOM);
            break;
        case SDLK_UP:
            rubiks.x_rot += rotInc;
            break;
        case SDLK_DOWN:
            rubiks.x_rot -= rotInc;
            break;
        case SDLK_LEFT:
            rubiks.y_rot += rotInc;
            break;
        case SDLK_RIGHT:
            rubiks.y_rot -= rotInc;
            break;
        case SDLK_m:
            rubiksCubeIsShuffling = true;
            break;
        default:
            break;
    }
}

void World::OnKeyUp(SDL_Keycode sym) {
    
    switch (sym) {
        default:
            break;
    }
}
