#define CAMERA_H
#define PI 3.141592

#ifdef __linux
    #ifndef __gl_h_
        #include <GL/gl.h>
    #endif

    #ifndef __glu_h_
        #include <GL/glu.h>
    #endif
#elif __APPLE__
    #ifndef __gl_h_
        #include <OpenGL/GL.h>
    #endif

    #ifndef __glu_h_
        #include <OpenGL/GLU.h>
    #endif
#endif

#ifndef PERSON_H
#include "Person.h"
#endif

#include <math.h>

class Camera
{
public:
    Person * person;

    Camera(Person * p);

    void syncWithPerson();
};
