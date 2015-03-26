//
//  OnRender.cpp
//  Rubiks
//
//  Created by Ellis Sparky Hoag on 8/4/14.
//  Copyright (c) 2014 Ellis Sparky Hoag. All rights reserved.
//

#include "World.h"

void World::OnRender()  {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //static double x = 0;
    
//
//    glLoadIdentity();
//    
//    glTranslated(0, sin(x/1000), -20);
//    
//    glScaled(.5, .5, 1);
//    
//    glRotated(x++, 1, 1, 1);
//    
//    glColor3d(1, 1, 0);
//    
//    glEnableClientState(GL_VERTEX_ARRAY);
//    //glEnableClientState(GL_COLOR_ARRAY);
//    
//    GLfloat colors[72];
//    
//    for (int i = 0; i < 72; i++) {
//        colors[i] = (int)(i / 24);
//    }
//    
//    glVertexPointer(3, GL_FLOAT, 0, cubieVertices);
//    //glColorPointer(3, GL_FLOAT, 0, colors);
//    
//    //glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubieIndices);
//    glDrawArrays(GL_QUADS, 0, 24);
//    
//    glDisableClientState(GL_VERTEX_ARRAY);
//    //glDisableClientState(GL_COLOR_ARRAY);
//    
    
    
    glLoadIdentity();
    
    glTranslated(0, 0, -28);
    
    //glScaled(0.9f, 0.9f, 0.9f);
    
    glRotated(rubiks.x_rot, 1, 0, 0);
    glRotated(rubiks.y_rot, 0, 1, 0);
    glRotated(rubiks.z_rot, 0, 0, 1);
    
    uint32_t * rubiksColorArray;
    
    rubiksColorArray = rubiks.getRubiksCubeColorArray();
    
    for (int cubie = 0; cubie < 27; cubie++) {
        if (cubie == 13) {//center cube can be skipped
            continue;
        }
        
        GLfloat cubieColorArray[72];
        
        /*for (int i = 0; i < 72; i++) {
            cubieColorArray[i] = 1.f;
        }*/
        
        for (int face = 0; face < 6; face++) {
            //have a cubie
            //for each face 0 - 5 on that cubie
                //find the coordinate for cubeState by using mapFaceToCubie
                //get a color from rubiksColorArray
                //set cubieColorArray to that color
            //Done!
            
            int cubeStateCoordinate = mapFaceToCubie[face + cubie * 6];
            
            //std::cout << cubeStateCoordinate << ", ";
            
            uint32_t color;
            
            if (cubeStateCoordinate != -1) {
                color = rubiksColorArray[cubeStateCoordinate + face * 9];
                
                //std::cout << cubeStateCoordinate << ": " << color << "\n";
                
                for (int i = 0; i < 4; i++) {
                    cubieColorArray[3 * (i + 4 * face)] = cubieColors[((int)color) * 3];
                    cubieColorArray[3 * (i + 4 * face) + 1] = cubieColors[((int)color) * 3 + 1];
                    cubieColorArray[3 * (i + 4 * face) + 2] = cubieColors[((int)color) * 3 + 2];
                }
            }
            else    {
                for (int i = 0; i < 4; i++) {
                    cubieColorArray[3 * (i + 4 * face)] = BLACK;
                    cubieColorArray[3 * (i + 4 * face) + 1] = BLACK;
                    cubieColorArray[3 * (i + 4 * face) + 2] = BLACK;
                }
            }
            /*for (int i = 0; i < 4; i++) {
                cubieColorArray[0 + i * 4] = 1;
                cubieColorArray[1 + i * 4] = 0;
                cubieColorArray[2 + i * 4] = 0;
            }*/
        }
        
//        if (cubie % 3 != 1 && (int)(cubie % 9) / 3 != 1 && (int)cubie / 9 != 1) {
//            
//            //corner
//            
//        }
//        else if (cubie != 4 && cubie != 10 && cubie != 12 && cubie != 14 && cubie != 16 && cubie != 22) {
//            
//            //edge
//            
//        }
//        else    {
//            //center
//        }
        
        
        glPushMatrix();
        
        if (faceIsRotating) {
        
            int x_rot, y_rot, z_rot;
            
            int finalAngle;
            int factor = 1;
            
            switch (directionToRotate) {
                case CLOCKWISE:
                    finalAngle = 90;
                    break;
                case HALF_TURN:
                    finalAngle = 180;
                    break;
                case COUNTERCLOCKWISE:
                    finalAngle = 90;
                    factor = -1;
                    break;
                default:
                    break;
            }
            
            if (rubiks.cubieIsInFace(cubie, faceToRotate, &x_rot, &y_rot, &z_rot)) {
                glRotated(finalAngle * (SDL_GetTicks() - startRotateTime) / (double)TURN_TIME, factor * x_rot, factor * y_rot, factor * z_rot);
            }
        }
        
        glTranslated(((cubie % 3) - 1) * CUBIE_SEPARATION, ((int)(cubie / 9) - 1) * CUBIE_SEPARATION, ((int)((cubie % 9) / 3) - 1) * CUBIE_SEPARATION);

        
        //glScaled(1, 1, 1);
        
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        
        glVertexPointer(3, GL_FLOAT, 0, cubieVertices);
        glColorPointer(3, GL_FLOAT, 0, cubieColorArray);
        
        //glDrawElements(GL_QUADS, 72, GL_UNSIGNED_BYTE, cubieIndices);
        glDrawArrays(GL_QUADS, 0, 24);
        
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);

        glPopMatrix();
    }
    
    SDL_GL_SwapWindow(sdlWindow);
}
