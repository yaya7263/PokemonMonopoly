#include "monopoly.h"

using namespace std;

monopoly::monopoly(int playerz, int humanz)
{
    numPlayers = playerz; // initialize number of humans and players
    humans = humanz;
    qDebug() << "creating new game";

    initializeTiles();
    initializePlayers();
    whoseTurn = 0;

}

// polymorphic behavior of either ai or human taking turn
void monopoly::nextTurn(){
    //players[whoseTurn]->takeTurn(1);
    whoseTurn++;
    whoseTurn = whoseTurn%numPlayers; // reset to player 1
}
void monopoly::initializePlayers() {
    int i = 0;
    for (i;i< humans; i++){
        players[i] = new humanPlayer(i);
    }
    for (i;i< numPlayers;i ++){
        players[i] = new aiPlayer(i);
    }
}

int monopoly::getLocation(int player) {
    return players[player]->location;
}
/* first number will determine type
0 is Brown
1 is LightBlue
2 is Pink
3 is Orange
4 is Red
5 is Yellow
6 is Green
7 is Blue
8 is Go
9 is Community Chest
10 is Chance
11 is RailRoad
12 is Utility
13 is Just Visiting/Jail
14 is Free Parking
15 is Go To Jail
16 is Income Tax
17 is Luxury Tax
*/

void monopoly::initializeTiles() { // 99 means not part of the purchasable stuff
    tiles[0] = new square(8,0,0,0,99);
    tiles[1] = new square(0,60,2,1,-1);
    tiles[2] = new square(9,0,0,2,99);
    tiles[3] = new square(0,60,4,3,-1);
    tiles[4] = new square(16,0,0,4,99);
    tiles[5] = new square(11,200,25,5,-1);
    tiles[6] = new square(1,100,6,6,-1);
    tiles[7] = new square(10,0,0,7,99);
    tiles[8] = new square(1,100,6,8,-1);
    tiles[9] = new square(1,120,8,9,-1);
    tiles[10] = new square(13,0,0,10,99);
    tiles[11] = new square(2,140,10,11,-1);
    tiles[12] = new square(12,150,20,12,-1);
    tiles[13] = new square(2,140,10,13,-1);
    tiles[14] = new square(2,160,12,14,-1);
    tiles[15] = new square(11,200,25,15,-1);
    tiles[16] = new square(3,180,14,16,-1);
    tiles[17] = new square(9,0,0,17,99);
    tiles[18] = new square(3,180,14,18,-1);
    tiles[19] = new square(3,200,16,19,-1);
    tiles[20] = new square(13,0,0,20,99);
    tiles[21] = new square(4,220,18,21,-1);
    tiles[22] = new square(10,0,0,22,99);
    tiles[23] = new square(4,220,18,23,-1);
    tiles[24] = new square(4,240,20,23,-1);
    tiles[25] = new square(11,200,25,25,-1);
    tiles[26] = new square(5,260,22,26,-1);
    tiles[27] = new square(5,260,22,27,-1);
    tiles[28] = new square(12,150,20,28,-1);
    tiles[29] = new square(5,280,24,29,-1);
    tiles[30] = new square(15,0,0,30,99);
    tiles[31] = new square(6,300,26,31,-1);
    tiles[32] = new square(6,300,26,32,-1);
    tiles[33] = new square(9,0,0,33,99);
    tiles[34] = new square(6,320,28,34,-1);
    tiles[35] = new square(11,200,25,35,-1);
    tiles[36] = new square(10,0,0,36,99);
    tiles[37] = new square(7,350,35,37,-1);
    tiles[38] = new square(17,0,0,38,-1);
    tiles[39] = new square(7,400,50,39,-1);
    for (int i = 0; i < 40; i++){
        tiles[i]->initialRent = tiles[i]->initialRent*5;
    }
}
