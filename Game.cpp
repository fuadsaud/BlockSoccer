#include "Game.h"

Game::Game() {
    score = rounds = 0;
}

void Game::nextRound() {
 currentRound = new Scene(this);
}

Scene* Game::getCurrentRound() {
    return currentRound;
}

void Game::endRound(bool success) {
    rounds++;

    if (success) score++;

    if (rounds == MAX_ROUNDS) exit(0); // TODO game over
    else nextRound();
}

int Game::getScore() {
    return score;
}

int Game::getRounds() {
    return rounds;
}
