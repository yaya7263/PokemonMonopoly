#include "square.h"

using namespace std;

square::square(int color, int pricez, int rent, int location, int owner)
    : color (color),
      price (pricez),
      initialRent (rent),
      location(location),
      owner (owner),
      houses (0),
      currentRent (0)
{
}
