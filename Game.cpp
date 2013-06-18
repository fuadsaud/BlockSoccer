#include "Game.h"

Game::Game()
{
    currentRound = new Scene(this);
}

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
    if (success) {
        score ++;
    }
    if (rounds == MAX_ROUNDS) {
        // TODO game over
        exit(0);
    } else {
        nextRound();
    }
}

int Game::getScore() {
    return score;
}
