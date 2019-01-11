#include "player.h"

player::player(int number)
    : money(1500),
      location(0), // start with $1500 and at GO
      status(0), // 0 signifies not in jail, 1 in jail, 2 lost
      playerNumber(number)
{

}
