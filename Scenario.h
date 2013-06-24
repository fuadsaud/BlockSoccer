#pragma once

#include "Includes.h"

#include "Point.h"

class Scenario {
public:
    Scenario(float width);

    void render();

    float getWidth();
    float getLenght();

    Point** getBoundaries();
private:
    float width;
    float lenght;

    void renderGround();
    void renderLines();
    void renderGoal();
};