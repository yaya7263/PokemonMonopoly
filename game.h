#ifndef GAME_H
#define GAME_H
#include <QDebug>
// Singleton
class Game
{
public:
    int players;
    int humans;
    static Game& GetInstance(int players, int humans) {
        static Game* instance = 0;
        if (instance == 0)
            instance = new Game(players, humans);

        return *instance;
    }
    Game() {};
private:
    Game(int, int);

};

#endif // GAME_H
