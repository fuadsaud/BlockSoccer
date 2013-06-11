#pragma once

#include "Includes.h"

#include "Point.h"
#include "Parallelepiped.h"

class Person
{
public:
    const static int FRONT = 1;
    const static int BACK  = 2;
    const static int LEFT  = 3;
    const static int RIGHT = 4;

    Person();
    Person(Point * initialPosition);

    float getDirectionAngle();
    Point * getPosition();

    void lookAt(Point* to);

    void rotate(float amount);
    void move(const int direction, int amount);

    void render();

private:
    Point * position;

    float directionAngle;

    void setDirectionAngle(float angle);

    void renderFoot();
    void renderLeg();
    void renderBody();
    void renderArm(const int leftOrRight);
};
