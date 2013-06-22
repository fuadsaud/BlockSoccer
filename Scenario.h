#pragma once

#include "Includes.h"

class Scenario {
public:
    Scenario(float width);

    void render();

    float getWidth();
    float getLenght();
private:
    float width;
    float lenght;

    void renderGround();
    void renderLines();
    void renderGoal();
};