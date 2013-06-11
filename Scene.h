#pragma once

#include "Includes.h"

#include "Ball.h"
#include "Person.h"
#include "Camera.h"
#include <vector>
#include <stdlib.h>

class Scene
{
public:
    static const int PLAYER_MOVEMENT_AMOUNT = 5;

    Scene();

    void init();
    void display();
    void keyboard(const char key, int x, int y);

    void moveOpponents();
    void passiveMotion(int x, int y);

private:
    Ball * ball;
    Person * player;
    Camera * camera;
    Person * goalKepper;
    std::vector<Person> opponents;

    void drawScenario();
};
