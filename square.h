#ifndef SQUARE_H
#define SQUARE_H
#include <string>

using namespace std;

class square
{
public:
    square(int color, int pricez, int rent, int location, int owner);
    int color;
    int price;
    int initialRent;
    int location;
    int owner;
    int houses;
    int currentRent;
};

#endif // SQUARE_H
