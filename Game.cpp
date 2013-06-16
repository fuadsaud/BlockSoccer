#include "Game.h"

Game::Game()
{
    currentRound = new Scene();
}

void Game::nextRound()
{
    currentRound = new Scene();
}

Scene * Game::getCurrentRound()
{
    return currentRound;
}
