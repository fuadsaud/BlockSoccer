#pragma once

#include "Includes.h"

#include "Ball.h"
#include "Person.h"
#include "Camera.h"

class Game;

class Scene
{
public:
    const static float PLAYER_MOVEMENT_AMOUNT = 0.11;

    Scene(Game* g);

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
    bool freeze;

    void drawScenario();

    void adversaryTeamBehavior();
    void ballBehavior();
    void collisionMonitor();
    void end(bool success);
    void showData();
    void putTextInWindow(char*s, float x, float y);

    Game * game;
};

#include "Game.h"
