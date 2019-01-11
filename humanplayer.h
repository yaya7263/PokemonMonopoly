#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"

class humanPlayer : public player
{
public:
    humanPlayer(int i);

    int takeTurn(square* currentSquare ) override;
};

#endif // HUMANPLAYER_H
