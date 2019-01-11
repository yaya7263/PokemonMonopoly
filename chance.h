#ifndef CHANCE_H
#define CHANCE_H
#include "player.h"

class Chance
{
public:
    Chance();
    static int runCard(player* currentPlayer);
};

#endif // CHANCE_H
