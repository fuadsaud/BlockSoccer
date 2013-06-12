#pragma once

#include "Includes.h"

#include "Ball.h"
#include "Person.h"
#include "Camera.h"

class Scene
{
public:
    static const int PLAYER_MOVEMENT_AMOUNT = 5;

    Scene();

    void init();
    void display();

    void animate();

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
};
