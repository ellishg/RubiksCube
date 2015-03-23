//
//  Definitions.h
//  Rubiks
//
//  Created by Ellis Sparky Hoag on 8/4/14.
//  Copyright (c) 2014 Ellis Sparky Hoag. All rights reserved.
//

#ifndef Rubiks_Definitions_h
#define Rubiks_Definitions_h

#define CUBIE_SEPARATION 1.05f
#define BLACK 0.0f
#define TURN_TIME 200


/*enum RUBIKS_CUBIE_TYPE   {
    CENTER, //six centers
    EDGE,   //12 edges
    CORNER  //eight corners
};*/

enum RUBIKS_CUBIE_COLORS    {
    WHITE = 0b000,
    RED = 0b001,
    BLUE = 0b010,
    ORANGE = 0b011,
    GREEN = 0b100,
    YELLOW = 0b101
};

static const float cubieVertices[4 * 6 * 3] = {
    /*
     *  vertices are defined face by face so each face can be a different color
     */
    
    -0.5, 0.5, -0.5,    //Top face
    -0.5, 0.5, 0.5,
    0.5, 0.5, 0.5,
    0.5, 0.5, -0.5,
    
    -0.5, 0.5, 0.5,    //Front
    -0.5, -0.5, 0.5,
    0.5, -0.5, 0.5,
    0.5, 0.5, 0.5,
    
    0.5, 0.5, 0.5,    //Right
    0.5, -0.5, 0.5,
    0.5, -0.5, -0.5,
    0.5, 0.5, -0.5,
    
    0.5, 0.5, -0.5,    //Back
    0.5, -0.5, -0.5,
    -0.5, -0.5, -0.5,
    -0.5, 0.5, -0.5,
    
    -0.5, 0.5, -0.5,    //Left Face
    -0.5, -0.5, -0.5,
    -0.5, -0.5, 0.5,
    -0.5, 0.5, 0.5,
    
    -0.5, -0.5, -0.5,      //Bottom
    0.5, -0.5, -0.5,
    0.5, -0.5, 0.5,
    -0.5, -0.5, 0.5
};

//static const char/*GLubyte*/ cubieIndices[6 * 4] = {
//    0, 1, 2, 3,
//    0, 3, 4, 7,
//    0, 7, 6, 1,
//    1, 6, 5, 2,
//    2, 5, 4, 3,
//    4, 5, 6, 7
//};

static const float cubieColors[18] = {
    1, 1, 1,    //White
    1, 0, 0,    //Red
    0, 0, 1,    //Blue
    1, 0.5, 0,  //Orange
    0, 1, 0,    //Green
    1, 1, 0     //Yellow
};

static const int mapFaceToCubie[6 * 28] = {
    /*
     *  6 element in a cubie
     *  every element represents a place to find the color for that face
     *  the element is the square of the rubiksState
     * -1 represents black
     */
    
    
    // bottom layer
    -1,
    -1,
    -1,
    0,
    0,
    6,
    
    -1,
    -1,
    -1,
    1,
    -1,
    7,
    
    -1,
    -1,
    2,
    2,
    -1,
    8,
    
    -1,
    -1,
    -1,
    -1,
    3,
    3,
    
    -1,
    -1,
    -1,
    -1,
    -1,
    4,
    
    -1,
    -1,
    5,
    -1,
    -1,
    5,
    
    -1,
    6,
    -1,
    -1,
    6,
    0,
    
    -1,
    7,
    -1,
    -1,
    -1,
    1,
    
    -1,
    8,
    8,
    -1,
    -1,
    2,
    
    //--------//
    //middle face
    -1,
    -1,
    -1,
    3,
    1,
    -1,
    
    -1,
    -1,
    -1,
    4,
    -1,
    -1,
    
    -1,
    -1,
    1,
    5,
    -1,
    -1,
    
    -1,
    -1,
    -1,
    -1,
    4,
    -1,
    
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    
    -1,
    -1,
    4,
    -1,
    -1,
    -1,
    
    -1,
    3,
    -1,
    -1,
    7,
    -1,
    
    -1,
    4,
    -1,
    -1,
    -1,
    -1,
    
    -1,
    5,
    7,
    -1,
    -1,
    -1,
    
    //--------//
    //top face
    0,
    -1,
    -1,
    6,
    2,
    -1,
    
    1,
    -1,
    -1,
    7,
    -1,
    -1,
    
    2,
    -1,
    0,
    8,
    -1,
    -1,
    
    3,
    -1,
    -1,
    -1,
    5,
    -1,
    
    4,
    -1,
    -1,
    -1,
    -1,
    -1,
    
    5,
    -1,
    3,
    -1,
    -1,
    -1,
    
    6,
    0,
    -1,
    -1,
    8,
    -1,
    
    7,
    1,
    -1,
    -1,
    -1,
    -1,
    
    8,
    2,
    6,
    -1,
    -1,
    -1
};

#endif
