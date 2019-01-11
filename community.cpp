#include "community.h"

//Community is Adventure
Community::Community()
{

}

int Community::runCard(player* currentPlayer) {
    int dice = qrand() % (2);
    if (dice){
        currentPlayer->location -= 3;
    } else {
        currentPlayer->money += 200;
    }
    return dice;
}
