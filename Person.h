#pragma once

#include "Includes.h"

#include "Color.h"
#include "Point.h"
#include "Object.h"
#include "Cuboid.h"

class Person : public Object {
public:
    Person(Point* initialPosition,
           Color* shirts, Color* shorts,
           float m = Object::DEFAULT_MOVEMENT_AMOUNT);

    void render();

    Color* shirtColor;
    Color* shortsColor;

private:
    void renderFoot();
    void renderLeg();
    void renderBody();
    void renderArm(const int leftOrRight);
};
