//
//  main.cpp
//  Rubiks
//
//  Created by Ellis Sparky Hoag on 8/4/14.
//  Copyright (c) 2014 Ellis Sparky Hoag. All rights reserved.
//

#include "World.h"

World::World()  {
    
    isRunning = true;
    
    windowWidth = 600;
    
    windowHeight = 600;
    
    faceIsRotating = false;
    
    rotationTime = TURN_TIME;
    
    rubiksCubeIsShuffling = false;
}

int main(int argc, const char * argv[])
{
    
    srand((unsigned int)time(nullptr));
    
    World world;
    
    if (!world.initSDLWindowAndContext()) {
        return -1;
    }
    
    world.initGL();
    
    //Uint32 ticks = SDL_GetTicks();
    
    while (world.isRunning) {
        
        world.OnEvent();
        
        world.OnLoop();
        
        world.OnRender();
    }
    
    return 0;
}

