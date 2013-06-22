#include "Game.h"

Game::Game() { }

void Game::nextRound()
{
    currentRound = new Scene(this);
}

Scene * Game::getCurrentRound()
{
    return currentRound;
}

void Game::endRound(bool success) {
    rounds ++;

    if (success) score ++;

    if (rounds == MAX_ROUNDS) exit(0); // TODO game over
    else nextRound();
}

int Game::getScore() {
    return score;
}
