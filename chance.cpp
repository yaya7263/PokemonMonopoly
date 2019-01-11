#include "chance.h"

//Chance is Challenge
Chance::Chance()
{

}

int Chance::runCard(player* currentPlayer)  {
    int dice = qrand() % (2);
    if (dice){
        currentPlayer->money += 100;
    } else {
        currentPlayer->money -= 200;
    }
    return dice;
}
