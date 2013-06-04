#pragma once

#include "Person.h"
#include "Camera.h"

class Scene
{
public:
    Scene();

    void init();
    void display();
    void keyboardAction(const char key, int x, int y);

private:
    Person * player;
    Camera * camera;
};
