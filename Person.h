#pragma once

#include "Includes.h"

#include "Point.h"
#include "Object.h"
#include "Parallelepiped.h"

class Person : public Object {
public:
    Person();
    Person(Point * initialPosition);

    void render();

private:
    void renderFoot();
    void renderLeg();
    void renderBody();
    void renderArm(const int leftOrRight);
};
