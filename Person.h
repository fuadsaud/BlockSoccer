#pragma once

#include "Includes.h"

#include "Point.h"
#include "Object.h"
#include "Parallelepiped.h"

class Person : public Object {
public:
    Person(float m = Object::DEFAULT_MOVEMENT_AMOUNT);
    Person(Point * initialPosition, float m = Object::DEFAULT_MOVEMENT_AMOUNT);

    void render();

private:
    void renderFoot();
    void renderLeg();
    void renderBody();
    void renderArm(const int leftOrRight);
};
