#pragma once

#ifdef __linux
    #ifndef __gl_h_
        #include <GL/gl.h>
    #endif
    #ifndef __glu_h_
        #include <GL/glu.h>
    #endif
    #ifndef __GLUT_H__
        #include <GL/glut.h>
    #endif
#elif __APPLE__ && __MACH__
    #ifndef __gl_h_
        #include <OpenGL/GL.h>
    #endif
    #ifndef __glu_h_
        #include <OpenGL/GLU.h>
    #endif
    #ifndef __GLUT_H__
        #include <GLUT/GLUT.h>
    #endif
#endif

#include "Person.h"
#include "Camera.h"
#include <vector>
#include <stdlib.h>

class Scene
{
public:
    static const int PLAYER_MOVEMENT_AMOUNT = 5;

    Scene();

    void init();
    void display();
    void keyboard(const char key, int x, int y);

    void moveOpponents();
    void passiveMotion(int x, int y);

private:
    Person * player;
    Camera * camera;
    Person * goalKepper;
    std::vector<Person> opponents;

    void drawScenario();
};
