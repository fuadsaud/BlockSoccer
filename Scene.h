#pragma once

#include "Includes.h"

#include "Scenario.h"
#include "Ball.h"
#include "Person.h"
#include "Camera.h"

class Game;

class Scene {
public:
    const static float PLAYER_MOVEMENT_AMOUNT = 1;

    Scene(Game* g);

    void init(Camera* c);
    void display();

    void background();

    void keyboard(const char key, int x, int y);
    void passiveMotion(int x, int y);

private:
    Game* game;
    Scenario* scenario;
    Person* player;
    Camera* camera;
    Ball* ball;
    Person* goalKepper;
    std::vector<Person> opponents;

    void adversaryTeamBehavior();
    void ballBehavior();
    void collisionMonitor();
    void end(bool success);
};

#include "Game.h"
