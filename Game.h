#pragma once

#include "Includes.h"

#include "Scene.h"

class Game {
public:
    const static int MAX_ROUNDS = 3;

    Game();

    void start();
    void nextRound();
    void endRound(bool success);

    Scene* getCurrentRound();
    int getScore();

private:
    int rounds;
    int score;

    Scene* currentRound;
};
