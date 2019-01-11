#include "aiplayer.h"

aiPlayer::aiPlayer(int i)
    : player(i)  // call parent constructor
{

}

// return 1 if buy, return 0 if not buy
int aiPlayer::takeTurn(square* currentSquare){
    if (money < 600){
        return 0;
    } else { // 50 percent of buying otherwise
        int dice = qrand() % (2);
        if (dice){
            properties.append(currentSquare->location);
            return 1;
        } else {
            return 0;
        }
    }
    return 0;
}
