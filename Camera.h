#pragma once

#ifdef __linux
    #ifndef __gl_h_
        #include <GL/gl.h>
    #endif

    #ifndef __glu_h_
        #include <GL/glu.h>
    #endif
#elif __APPLE__ && __MACH__
    #ifndef __gl_h_
        #include <OpenGL/GL.h>
    #endif

    #ifndef __glu_h_
        #include <OpenGL/GLU.h>
    #endif
#endif

#include "Person.h"
#include <math.h>

class Camera
{
public:
    Person * person;

    Camera(Person * p);

    void syncWithPerson();
};
