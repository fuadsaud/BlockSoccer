#pragma once

#include "Includes.h"

#include "Scene.h"

class Game
{
public:
    const static int MAX_ROUNDS = 3;

    Game();

    void start();
    void nextRound();
    Scene * getCurrentRound();

private:
    int rounds;

    Scene * currentRound;
};
