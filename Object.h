#pragma once

#include "Includes.h"

#include "Point.h"
#include "Parallelepiped.h"

class Object
{
public:
    const static int FRONT = 1;
    const static int BACK  = 2;
    const static int LEFT  = 3;
    const static int RIGHT = 4;

    Object();
    Object(Point * initialPosition);

    float getDirectionAngle();
    Point * getPosition();

    void lookAt(Point* to);

    void rotate(float amount);
    void move(const int direction, float amount);

    void render();

    float getRadius();

    bool collidingWith(Object o);

    float getShift();

protected:
    void setDirectionAngle(float angle);


    Point * position;

    float directionAngle;

    float radius;
};
