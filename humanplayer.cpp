#include "humanplayer.h"


humanPlayer::humanPlayer(int i)
: player(i)  // call parent constructor
{

}
int humanPlayer::takeTurn(square* currentSquare){
    properties.append(currentSquare->location);
    return 0; // the return is for AI, this just appends to array of owned properties
    // we only get when person presses buy, bad coupling by me
}
