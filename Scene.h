#pragma once

#include "Includes.h"

#include "Ball.h"
#include "Person.h"
#include "Camera.h"

class Scene
{
public:
    const static float PLAYER_MOVEMENT_AMOUNT = 0.11;

    Scene();

    void init();
    void display();

    void background();

    void keyboard(const char key, int x, int y);
    void passiveMotion(int x, int y);


private:
    Person * player;
    Camera * camera;
    Ball * ball;
    Person * goalKepper;
    std::vector<Person> opponents;

    void drawScenario();

    void adversaryTeamBehavior();
    void ballBehavior();
    void collisionMonitor();
};
