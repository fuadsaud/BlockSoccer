#pragma once

#include "Includes.h"

#include "Person.h"
#include "Object.h"
#include "Point.h"

class Ball : public Object {
public:
    Ball();
    Ball(Person * p);

    void attach(Person * p);
    void detach();
    bool isAttached();

    void go();

    void render();

private:
    Person * player;
};
