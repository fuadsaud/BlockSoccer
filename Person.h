#pragma once

#include "Includes.h"

#include "Color.h"
#include "Point.h"
#include "Object.h"
#include "Parallelepiped.h"

class Person : public Object {
public:
    Person(Point* initialPosition, Color* c,
           float m = Object::DEFAULT_MOVEMENT_AMOUNT);

    void render();

    Color* color;

private:
    void renderFoot();
    void renderLeg();
    void renderBody();
    void renderArm(const int leftOrRight);
};
