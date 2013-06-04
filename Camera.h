#define CAMERA_H
#define PI 3.141592

#ifndef __gl_h_
#include <OpenGL/GL.h>
#endif

#ifndef __glu_h_
#include <OpenGL/GLU.h>
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

    void look();
};
