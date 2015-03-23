//
//  OnInit.cpp
//  Rubiks
//
//  Created by Ellis Sparky Hoag on 8/4/14.
//  Copyright (c) 2014 Ellis Sparky Hoag. All rights reserved.
//

#include "World.h"

bool World::initSDLWindowAndContext() {
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return false;
    }
    
    if ((sdlWindow = SDL_CreateWindow("Rubik's Cube!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE)) == NULL) {
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        return false;
    }
    
    if ((glContext = SDL_GL_CreateContext(sdlWindow)) == NULL) {
        printf("SDL_GL_CreateContext failed: %s\n", SDL_GetError());
        return false;
    }
    
    return true;
}

void World::initGL()    {
    
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    
    //glFrustum(-windowWidth, windowWidth, -windowHeight, windowHeight, 1.f, 100.f);
    glFrustum(-1, 1, -1, 1, 10, 100);
    
    glClearColor(0.2f, 0.2f, 0.2f, 1);
    
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_CULL_FACE);
    
    glMatrixMode(GL_MODELVIEW);
}