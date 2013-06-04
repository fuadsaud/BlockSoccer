#pragma once

#include "Person.h"
#include "Camera.h"
#include <vector>
#include <stdlib.h>

class Scene
{
public:
    Scene();

    void init();
    void display();
    void keyboardAction(const char key, int x, int y);

    void moveOpponents();

private:
    Person * player;
    Camera * camera;
    std::vector<Person> opponents;

    void drawScenario();
};
