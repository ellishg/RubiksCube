//
//  Definitions.h
//  Rubiks
//
//  Created by Ellis Sparky Hoag on 8/4/14.
//  Copyright (c) 2014 Ellis Sparky Hoag. All rights reserved.
//

#ifndef Rubiks_Definitions_h
#define Rubiks_Definitions_h

#define CUBIE_SEPARATION 1.055f
#define BLACK 0.0f
#define TURN_TIME 300
#define FAST_TURN_TIME 100
#define GODS_NUMBER 20


/*enum RUBIKS_CUBIE_TYPE   {
    CENTER, //six centers
    EDGE,   //12 edges
    CORNER  //eight corners
};*/

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

enum RUBIKS_CUBIE_COLORS    {
    WHITE = 0b000,
    RED = 0b001,
    BLUE = 0b010,
    ORANGE = 0b011,
    GREEN = 0b100,
    YELLOW = 0b101,
    WILDCARD = 0b111
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

/*
 *  We need to create a sequence of steps or goals for the solver.
 *  Each goal will define a cubeState needed where but with a wildcard = 0b111
 *  It will be in a list list of colors and later turned into a cubeState-like variable
 *
 *  Goal 1: Top layer complete and everything else wildcard.
 *  Goal 2: Top and Middle layer complete.
 *  Goal 3: Finished cube.
 */

static const uint8_t smallBlockGoal[6 * 9] =    {
    WHITE, WHITE, WILDCARD,
    WHITE, WHITE, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD,
    
    WILDCARD, WILDCARD, WILDCARD,
    WILDCARD, RED, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD,
    
    WILDCARD, WILDCARD, WILDCARD,
    WILDCARD, BLUE, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD,
    
    WILDCARD, WILDCARD, WILDCARD,
    WILDCARD, ORANGE, WILDCARD,
    ORANGE, ORANGE, WILDCARD,
    
    WILDCARD, WILDCARD, GREEN,
    WILDCARD, GREEN, GREEN,
    WILDCARD, WILDCARD, WILDCARD,
    
    WILDCARD, WILDCARD, WILDCARD,
    WILDCARD, YELLOW, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD

};

static const uint8_t firstAGoal[6 * 9] =    {
    WHITE, WHITE, WILDCARD,
    WHITE, WHITE, WILDCARD,
    WHITE, WHITE, WILDCARD,
    
    RED, RED, WILDCARD,
    WILDCARD, RED, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD,
    
    WILDCARD, WILDCARD, WILDCARD,
    WILDCARD, BLUE, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD,
    
    WILDCARD, WILDCARD, WILDCARD,
    WILDCARD, ORANGE, WILDCARD,
    ORANGE, ORANGE, WILDCARD,
    
    WILDCARD, WILDCARD, GREEN,
    WILDCARD, GREEN, GREEN,
    WILDCARD, WILDCARD, GREEN,
    
    WILDCARD, WILDCARD, WILDCARD,
    WILDCARD, YELLOW, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD
    
};

static const uint8_t firstBGoal[6 * 9] =    {
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WILDCARD,
    
    RED, RED, WILDCARD,
    WILDCARD, RED, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD,
    
    BLUE, WILDCARD, WILDCARD,
    BLUE, BLUE, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD,
    
    WILDCARD, WILDCARD, WILDCARD,
    WILDCARD, ORANGE, WILDCARD,
    ORANGE, ORANGE, ORANGE,
    
    WILDCARD, WILDCARD, GREEN,
    WILDCARD, GREEN, GREEN,
    WILDCARD, WILDCARD, GREEN,
    
    WILDCARD, WILDCARD, WILDCARD,
    WILDCARD, YELLOW, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD
    
};

static const uint8_t firstGoal[6 * 9] = {

    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    
    RED, RED, RED,
    WILDCARD, RED, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD,
    
    BLUE, WILDCARD, WILDCARD,
    BLUE, BLUE, WILDCARD,
    BLUE, WILDCARD, WILDCARD,
    
    WILDCARD, WILDCARD, WILDCARD,
    WILDCARD, ORANGE, WILDCARD,
    ORANGE, ORANGE, ORANGE,
    
    WILDCARD, WILDCARD, GREEN,
    WILDCARD, GREEN, GREEN,
    WILDCARD, WILDCARD, GREEN,
    
    WILDCARD, WILDCARD, WILDCARD,
    WILDCARD, YELLOW, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD
};

static const uint8_t secondLayerAGoal[6 * 9] = {
    
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    
    RED, RED, RED,
    RED, RED, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD,
    
    BLUE, WILDCARD, WILDCARD,
    BLUE, BLUE, WILDCARD,
    BLUE, WILDCARD, WILDCARD,
    
    WILDCARD, WILDCARD, WILDCARD,
    WILDCARD, ORANGE, WILDCARD,
    ORANGE, ORANGE, ORANGE,
    
    WILDCARD, WILDCARD, GREEN,
    WILDCARD, GREEN, GREEN,
    WILDCARD, GREEN, GREEN,
    
    WILDCARD, WILDCARD, WILDCARD,
    WILDCARD, YELLOW, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD
};

static const uint8_t secondLayerBGoal[6 * 9] = {
    
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    
    RED, RED, RED,
    RED, RED, RED,
    WILDCARD, WILDCARD, WILDCARD,
    
    BLUE, WILDCARD, WILDCARD,
    BLUE, BLUE, WILDCARD,
    BLUE, BLUE, WILDCARD,
    
    WILDCARD, WILDCARD, WILDCARD,
    WILDCARD, ORANGE, WILDCARD,
    ORANGE, ORANGE, ORANGE,
    
    WILDCARD, WILDCARD, GREEN,
    WILDCARD, GREEN, GREEN,
    WILDCARD, GREEN, GREEN,
    
    WILDCARD, WILDCARD, WILDCARD,
    WILDCARD, YELLOW, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD
};

static const uint8_t secondLayerCGoal[6 * 9] = {
    
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    
    RED, RED, RED,
    RED, RED, RED,
    WILDCARD, WILDCARD, WILDCARD,
    
    BLUE, BLUE, WILDCARD,
    BLUE, BLUE, WILDCARD,
    BLUE, BLUE, WILDCARD,
    
    WILDCARD, WILDCARD, WILDCARD,
    WILDCARD, ORANGE, ORANGE,
    ORANGE, ORANGE, ORANGE,
    
    WILDCARD, WILDCARD, GREEN,
    WILDCARD, GREEN, GREEN,
    WILDCARD, GREEN, GREEN,
    
    WILDCARD, WILDCARD, WILDCARD,
    WILDCARD, YELLOW, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD
};

static const uint8_t secondLayerDGoal[6 * 9] = {
    
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    
    RED, RED, RED,
    RED, RED, RED,
    WILDCARD, WILDCARD, WILDCARD,
    
    BLUE, BLUE, WILDCARD,
    BLUE, BLUE, WILDCARD,
    BLUE, BLUE, WILDCARD,
    
    WILDCARD, WILDCARD, WILDCARD,
    ORANGE, ORANGE, ORANGE,
    ORANGE, ORANGE, ORANGE,
    
    WILDCARD, GREEN, GREEN,
    WILDCARD, GREEN, GREEN,
    WILDCARD, GREEN, GREEN,
    
    WILDCARD, WILDCARD, WILDCARD,
    WILDCARD, YELLOW, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD
};

static const uint8_t cornersAGoal[6 * 9] = {
    
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    
    RED, RED, RED,
    RED, RED, RED,
    RED, WILDCARD, WILDCARD,
    
    BLUE, BLUE, WILDCARD,
    BLUE, BLUE, WILDCARD,
    BLUE, BLUE, WILDCARD,
    
    WILDCARD, WILDCARD, WILDCARD,
    ORANGE, ORANGE, ORANGE,
    ORANGE, ORANGE, ORANGE,
    
    WILDCARD, GREEN, GREEN,
    WILDCARD, GREEN, GREEN,
    GREEN, GREEN, GREEN,
    
    YELLOW, WILDCARD, WILDCARD,
    WILDCARD, YELLOW, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD
};

static const uint8_t cornersBGoal[6 * 9] = {
    
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    
    RED, RED, RED,
    RED, RED, RED,
    RED, WILDCARD, RED,
    
    BLUE, BLUE, WILDCARD,
    BLUE, BLUE, WILDCARD,
    BLUE, BLUE, BLUE,
    
    WILDCARD, WILDCARD, WILDCARD,
    ORANGE, ORANGE, ORANGE,
    ORANGE, ORANGE, ORANGE,
    
    WILDCARD, GREEN, GREEN,
    WILDCARD, GREEN, GREEN,
    GREEN, GREEN, GREEN,
    
    YELLOW, WILDCARD, YELLOW,
    WILDCARD, YELLOW, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD
};

static const uint8_t cornersCGoal[6 * 9] = {
    
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    
    RED, RED, RED,
    RED, RED, RED,
    RED, WILDCARD, RED,
    
    BLUE, BLUE, BLUE,
    BLUE, BLUE, WILDCARD,
    BLUE, BLUE, BLUE,
    
    ORANGE, WILDCARD, ORANGE,
    ORANGE, ORANGE, ORANGE,
    ORANGE, ORANGE, ORANGE,
    
    GREEN, GREEN, GREEN,
    WILDCARD, GREEN, GREEN,
    GREEN, GREEN, GREEN,
    
    YELLOW, WILDCARD, YELLOW,
    WILDCARD, YELLOW, WILDCARD,
    YELLOW, WILDCARD, YELLOW
};

static const uint8_t edgesAGoal[6 * 9] = {
    
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    
    RED, RED, RED,
    RED, RED, RED,
    RED, RED, RED,
    
    BLUE, BLUE, BLUE,
    BLUE, BLUE, WILDCARD,
    BLUE, BLUE, BLUE,
    
    ORANGE, WILDCARD, ORANGE,
    ORANGE, ORANGE, ORANGE,
    ORANGE, ORANGE, ORANGE,
    
    GREEN, GREEN, GREEN,
    WILDCARD, GREEN, GREEN,
    GREEN, GREEN, GREEN,
    
    YELLOW, YELLOW, YELLOW,
    WILDCARD, YELLOW, WILDCARD,
    YELLOW, WILDCARD, YELLOW
};

static const uint8_t edgesBGoal[6 * 9] = {
    
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    
    RED, RED, RED,
    RED, RED, RED,
    RED, RED, RED,
    
    BLUE, BLUE, BLUE,
    BLUE, BLUE, WILDCARD,
    BLUE, BLUE, BLUE,
    
    ORANGE, ORANGE, ORANGE,
    ORANGE, ORANGE, ORANGE,
    ORANGE, ORANGE, ORANGE,
    
    GREEN, GREEN, GREEN,
    WILDCARD, GREEN, GREEN,
    GREEN, GREEN, GREEN,
    
    YELLOW, YELLOW, YELLOW,
    WILDCARD, YELLOW, WILDCARD,
    YELLOW, YELLOW, YELLOW
};

static const uint8_t finalGoal[6 * 9] = {
    
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    
    RED, RED, RED,
    RED, RED, RED,
    RED, RED, RED,
    
    BLUE, BLUE, BLUE,
    BLUE, BLUE, BLUE,
    BLUE, BLUE, BLUE,
    
    ORANGE, ORANGE, ORANGE,
    ORANGE, ORANGE, ORANGE,
    ORANGE, ORANGE, ORANGE,
    
    GREEN, GREEN, GREEN,
    GREEN, GREEN, GREEN,
    GREEN, GREEN, GREEN,
    
    YELLOW, YELLOW, YELLOW,
    YELLOW, YELLOW, YELLOW,
    YELLOW, YELLOW, YELLOW
};

static uint8_t yellowCrossGoal[6 * 9] = {
    
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    
    RED, RED, RED,
    RED, RED, RED,
    WILDCARD, WILDCARD, WILDCARD,
    
    BLUE, BLUE, WILDCARD,
    BLUE, BLUE, WILDCARD,
    BLUE, BLUE, WILDCARD,
    
    WILDCARD, WILDCARD, WILDCARD,
    ORANGE, ORANGE, ORANGE,
    ORANGE, ORANGE, ORANGE,
    
    WILDCARD, GREEN, GREEN,
    WILDCARD, GREEN, GREEN,
    WILDCARD, GREEN, GREEN,
    
    WILDCARD, YELLOW, WILDCARD,
    YELLOW, YELLOW, YELLOW,
    WILDCARD, YELLOW, WILDCARD
};

static const uint8_t orientatedCornersGoal[6 * 9] = {
    
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    WHITE, WHITE, WHITE,
    
    RED, RED, RED,
    RED, RED, RED,
    RED, WILDCARD, RED,
    
    BLUE, BLUE, BLUE,
    BLUE, BLUE, WILDCARD,
    BLUE, BLUE, BLUE,
    
    ORANGE, WILDCARD, ORANGE,
    ORANGE, ORANGE, ORANGE,
    ORANGE, ORANGE, ORANGE,
    
    GREEN, GREEN, GREEN,
    WILDCARD, GREEN, GREEN,
    GREEN, GREEN, GREEN,
    
    YELLOW, YELLOW, YELLOW,
    YELLOW, YELLOW, YELLOW,
    YELLOW, YELLOW, YELLOW
};

#define NUM_LAYER_GOALS 14

static const uint8_t * layerGoals[NUM_LAYER_GOALS] {
    smallBlockGoal,
    firstAGoal,
    firstBGoal,
    firstGoal,
    secondLayerAGoal,
    secondLayerBGoal,
    secondLayerCGoal,
    secondLayerDGoal,
    cornersAGoal,
    cornersBGoal,
    cornersCGoal,
    edgesAGoal,
    edgesBGoal,
    finalGoal
};

static const uint8_t fourCornersGoal[6 * 9] =    {
    WHITE, WILDCARD, WHITE,
    WILDCARD, WHITE, WILDCARD,
    WHITE, WILDCARD, WHITE,
    
    RED, WILDCARD, RED,
    WILDCARD, RED, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD,
    
    BLUE, WILDCARD, WILDCARD,
    WILDCARD, BLUE, WILDCARD,
    BLUE, WILDCARD, WILDCARD,
    
    WILDCARD, WILDCARD, WILDCARD,
    WILDCARD, ORANGE, WILDCARD,
    ORANGE, WILDCARD, ORANGE,
    
    WILDCARD, WILDCARD, GREEN,
    WILDCARD, GREEN, WILDCARD,
    WILDCARD, WILDCARD, GREEN,
    
    WILDCARD, WILDCARD, WILDCARD,
    WILDCARD, YELLOW, WILDCARD,
    WILDCARD, WILDCARD, WILDCARD
};

static const uint8_t allCornersGoal[6 * 9] =    {
    WHITE, WILDCARD, WHITE,
    WILDCARD, WHITE, WILDCARD,
    WHITE, WILDCARD, WHITE,
    
    RED, WILDCARD, RED,
    WILDCARD, RED, WILDCARD,
    RED, WILDCARD, RED,
    
    BLUE, WILDCARD, BLUE,
    WILDCARD, BLUE, WILDCARD,
    BLUE, WILDCARD, BLUE,
    
    ORANGE, WILDCARD, ORANGE,
    WILDCARD, ORANGE, WILDCARD,
    ORANGE, WILDCARD, ORANGE,
    
    GREEN, WILDCARD, GREEN,
    WILDCARD, GREEN, WILDCARD,
    GREEN, WILDCARD, GREEN,
    
    YELLOW, WILDCARD, YELLOW,
    WILDCARD, YELLOW, WILDCARD,
    YELLOW, WILDCARD, YELLOW
};

#define NUM_ORTEGA_METHOD_GOALS 2

static const uint8_t * ortegaGoal[NUM_ORTEGA_METHOD_GOALS]    {
    fourCornersGoal,
    allCornersGoal
};

static const int secondLayerRightHandMove[7 * 2]  {
    
    /*
     *  Lets assume we are doing a right-handed move
     *  to place an edge and we are looking at the front (red)
     *  FACE, DIRECTION
     */
    
    FRONT, CLOCKWISE,
    BOTTOM, CLOCKWISE,
    FRONT, COUNTERCLOCKWISE,
    BOTTOM, COUNTERCLOCKWISE,
    RIGHT, COUNTERCLOCKWISE,
    BOTTOM, COUNTERCLOCKWISE,
    RIGHT, CLOCKWISE
};

static const int yellowCrossMove[6 * 2]  {
    
    FRONT, CLOCKWISE,
    BOTTOM, CLOCKWISE,
    LEFT, CLOCKWISE,
    BOTTOM, COUNTERCLOCKWISE,
    LEFT, COUNTERCLOCKWISE,
    FRONT, COUNTERCLOCKWISE
};

static const int switchRightCorners[8 * 2] {
    
    /*
     *  Switches two side corners on the right side
     */
    
    LEFT, CLOCKWISE,
    BOTTOM, COUNTERCLOCKWISE,
    RIGHT, COUNTERCLOCKWISE,
    BOTTOM, CLOCKWISE,
    LEFT, COUNTERCLOCKWISE,
    BOTTOM, COUNTERCLOCKWISE,
    RIGHT, CLOCKWISE,
};

static const int orientateCornersRightHand[8 * 2] {
    
    RIGHT, COUNTERCLOCKWISE,
    BOTTOM, COUNTERCLOCKWISE,
    RIGHT, CLOCKWISE,
    BOTTOM, COUNTERCLOCKWISE,
    RIGHT, COUNTERCLOCKWISE,
    BOTTOM, HALF_TURN,
    RIGHT, CLOCKWISE,
    BOTTOM, HALF_TURN
};

static const int orientateCornersLeftHand[8 * 2] {
    
    LEFT, CLOCKWISE,
    BOTTOM, CLOCKWISE,
    LEFT, COUNTERCLOCKWISE,
    BOTTOM, CLOCKWISE,
    LEFT, CLOCKWISE,
    BOTTOM, HALF_TURN,
    LEFT, COUNTERCLOCKWISE,
    BOTTOM, HALF_TURN
};

static const int orientateEdgesA[9 * 2]  {
    
    LEFT, HALF_TURN,
    BOTTOM, CLOCKWISE,
    FRONT, CLOCKWISE,
    BACK, COUNTERCLOCKWISE,
    LEFT, HALF_TURN,
    FRONT, COUNTERCLOCKWISE,
    BACK, CLOCKWISE,
    BOTTOM, CLOCKWISE,
    LEFT, HALF_TURN
};

static const int orientateEdgesB[9 * 2]  {
    
    LEFT, HALF_TURN,
    BOTTOM, COUNTERCLOCKWISE,
    FRONT, CLOCKWISE,
    BACK, COUNTERCLOCKWISE,
    LEFT, HALF_TURN,
    FRONT, COUNTERCLOCKWISE,
    BACK, CLOCKWISE,
    BOTTOM, COUNTERCLOCKWISE,
    LEFT, HALF_TURN
};

#endif
