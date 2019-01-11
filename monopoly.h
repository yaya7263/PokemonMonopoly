
#include <QDebug>
#include "player.h"
#include "humanplayer.h"
#include "aiplayer.h"
#include "square.h"

// Singleton
class monopoly
{
public:
    int numPlayers;
    int humans;
    int whoseTurn;
    player* players[4];
    static monopoly& GetInstance(int players, int humans) {
        static monopoly* instance = NULL;
        if (instance == NULL)
            instance = new monopoly(players, humans);

        return *instance;
    }
    square* tiles[40];
    monopoly() {}
    void initializeTiles();
    void initializePlayers();
    void nextTurn();
    int getLocation(int);
private:
    monopoly(int players,int humans);
};
