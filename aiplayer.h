#ifndef AIPLAYER_H
#define AIPLAYER_H
#include "player.h"

class aiPlayer : public player
{
public:
    aiPlayer(int i);
    int takeTurn(square* currentSquare ) override;
};

#endif // AIPLAYER_H
