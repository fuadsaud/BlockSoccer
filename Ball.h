#pragma once

#include "Includes.h"

#include "Person.h"
#include "Point.h"

class Ball
{
public:
    Ball();
    Ball(Person * p);

    void attach(Person * p);

    void move(const int direction, int amount);

    void render();

private:
    Person * player;

    Point * position;

};
