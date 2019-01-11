#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QLabel>
#include "square.h"
#include "monopoly.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTextEdit>
#include <QMovie>
#include "community.h"
#include "chance.h"
#include <windows.h>
#include <QVector>
#include <QChart>
#include <QLineSeries>
#include <QChartView>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void renderGame();
    void setLocations();
    void loadImages();
    void setLabels();
    void displayGif(int);
    int numberPlayers = 2;
    int numberHumans = 2;
    bool ai[4]; // whether or not the player is AI
    int dice1;
    int dice2;
    int totalRoll;
    int xLocations[40];
    int yLocations[40];
    int currentPlayer = 0;
    int player1Location =0;
    int player2Location =0;
    int player1Exp = 1500;
    int player2Exp = 1500;
    monopoly* currentGame;
    ~MainWindow();
private slots:
    void handleStart();
    void handleTurn();
    void handleDice();
    void handleMove();
    void handlePurchase();
    void handleCloseGif();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QPushButton *gameStart;
    QPushButton *rollDice;
    QPushButton *playerMove;
    QPushButton *nextTurn;
    QPushButton *purchaseButton;
    QPushButton *continueButton;
    QLabel *dice1Label;
    QLabel *dice2Label;
    QLabel *location;
    QLabel *avail;
    QLabel *rentPrice;
    QLabel *player1;
    QLabel *player2;
    QLabel *player3;
    QLabel *player4;
    QLabel *totalExp;
    int expTotal = 3000;
    QLabel *challenge1;
    int p1challenges = 0;
    QLabel *challenge2;
    int p2challenges =0;
    QLabel *properties1;
    int p1prop = 0;
    QLabel *properties2;
    int p2prop = 0;
    QLabel *p1Properties;
    QLabel *p2Properties;
    QMediaPlayer* player;
    QLabel *pictures[40];
    QLabel *pictureLabels[40];
    QtCharts::QLineSeries *player1Graph;
    QtCharts::QLineSeries *player2Graph;
    QtCharts::QChart *chart1;
    QtCharts::QChart *chart2;
    QTextEdit *infoBox;
    QMovie *gifs[6];
    QLabel *gifLabel;


};

#endif // MAINWINDOW_H
