#ifndef PLAYER_H
#define PLAYER_H
#include "square.h"
#include <QVector>
class player
{
public:
    player(int number);
    int playerNumber;
    int money;
    int location;
    QVector<int> properties;
    int status;
    virtual int takeTurn(square* currentSquare ) = 0 ;
};

#endif // PLAYER_H
