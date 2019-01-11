#include "game.h"

Game::Game(int playerz, int humanz)
{
    players = playerz;
    humans = humanz;
    qDebug() << "creating new game";
    qDebug() << players;

}

