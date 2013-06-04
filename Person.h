#define PERSON_H

#ifndef __gl_h_
    #include <OpenGL/GL.h>
#endif

#ifndef POINT_H
    #include "Point.h"
#endif

#ifndef PARALLELEPIPED_H
    #include "Parallelepiped.h"
#endif

class Person {
private:
    Point * position;

    float directionAngle;

    void setDirectionAngle(float angle);

    void renderFoot();
    void renderLeg();
    void renderBody();
    void renderArm(const int leftOrRight);

public:
    Person();
    Person(Point * initialPosition);

    float getDirectionAngle();
    Point * getPosition();

    // void rotate(float angle);
    // void move(const int direction, int distance);

    void render();
};
