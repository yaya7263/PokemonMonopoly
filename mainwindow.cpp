#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QPixMap>
#include <QLabel>
//#include "game.h"
// NAME: YANG YANG

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setLocations();
    player1 = new QLabel(this);
    player2 = new QLabel(this);
    for (int i = 0; i < 40; i++){
        pictures[i] = new QLabel(this);
        pictures[i]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter | Qt::AlignTop); //center images
        pictureLabels[i] = new QLabel(this);
        pictureLabels[i]->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter | Qt::AlignTop);
        pictureLabels[i]->raise();
    }
    setLabels(); // this sets the names of the properties etc
    renderGame(); // Renders the graphics of the game
    qsrand(time(NULL)); // this will be used to randomize dice rolls
    qDebug() << "begin";

    // start the game with number of Players as well as Number of humans
    QtCharts::QLineSeries* player1Graph = new QtCharts::QLineSeries;
    player1Graph->append(0,3);
    player1Graph->append(2,4);
    chart1 = new QtCharts::QChart();
    chart1->legend()->hide();
    chart1->addSeries(player1Graph);
    chart1->createDefaultAxes();
    chart1->setTitle("player1 exp over time");
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart1);
    chartView->setRenderHint(QPainter::Antialiasing);
    QGraphicsView * view = ui->graphicsView;
    view->setSceneRect(0,0,100,100);
    scene = new QGraphicsScene;
    view->setScene(scene);
    scene->addItem(chart1);
    QtCharts::QLineSeries* player2Graph = new QtCharts::QLineSeries;
    rollDice = ui->pushButton;
    playerMove = ui->pushButton_4;
    gameStart = ui->pushButton_2;
    nextTurn = ui->pushButton_3;
    continueButton = ui->continue_2;
    continueButton->hide();
    purchaseButton = ui->pushButton_5;
    dice1Label = ui->dice_1;
    dice2Label = ui->dice_2;
    p1Properties = ui->properties1;
    p2Properties = ui->properties2;
    location = ui->location;
    avail = ui->avail;
    rentPrice = ui->rentPrice;
    totalExp = ui->totalExp;
    challenge1 = ui->challenge1;
    challenge2 = ui->challenge2;
    properties1 = ui->totalprop1;
    properties2 = ui->totalprop2;
    infoBox = ui->textEdit;
    infoBox->setText("Information Box");
/* apparently youtube links don't work this way, will further research it*/
    // help from http://doc.qt.io/qt-5/audiooverview.html
    player = new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile("C:/Users/Tears/Downloads/Pokemon.mp3"));

    connect(gameStart, SIGNAL (released()), this, SLOT (handleStart()));
    connect(rollDice, SIGNAL (released()), this, SLOT (handleDice()));
    connect(playerMove, SIGNAL (released()), this, SLOT (handleMove()));
    connect(nextTurn, SIGNAL (released()), this, SLOT (handleTurn()));
    connect(purchaseButton, SIGNAL (released()), this, SLOT (handlePurchase()));
    connect(continueButton, SIGNAL (released()), this, SLOT (handleCloseGif()));
// Think I realized this too late, but I have an unnecessary layer of abstraction for monopoly and MainWindow.
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleStart(){
    numberPlayers = ui->lineEdit->text().toInt();
    numberHumans = ui->lineEdit_2->text().toInt();
    int aiPlayers = numberPlayers - numberHumans;
    if (aiPlayers == 2) {
        ai[0] = true;
        ai[1] = true;
    } else if (aiPlayers == 1){
        ai[1] = true;
    } else{
        ai[0] = false;
        ai[1] = false;
    }
    infoBox->setText(ui->lineEdit->text() + " Players " + QString::number(aiPlayers) + " AI ");
// using singleton of Game
    currentGame = &monopoly::GetInstance(numberPlayers, numberHumans);

    if(ai[0] == true){ //if ai
        qDebug() << " AI first ";
        ui->currentPlayer->setText("Current AI: " + QString::number(currentPlayer+1));
        Sleep(2000);
        handleDice();
        Sleep(2000);
        handleMove();
        handleTurn(); // go to next person's turn
    } else {
        qDebug() << " Human first ";
        ui->currentPlayer->setText("Current Player: " + QString::number(currentPlayer+1));
    }

    //start the song
    player->setVolume(50);
    player->play();
}

void MainWindow::handleCloseGif() {
    continueButton->hide();
    gifLabel->hide();
    // update where they are
    int playerLocation = currentGame->players[currentPlayer]->location;
    player1Exp = currentGame->players[0]->money;
    player2Exp = currentGame->players[1]->money;
    if (currentPlayer == 0){
        player1->setGeometry(xLocations[playerLocation],yLocations[playerLocation],75,75);
        ui->label_41->setText("Player 1 Exp: " + QString::number(player1Exp));
    } else {
        if ((10 < playerLocation && playerLocation < 20) || (30 < playerLocation && playerLocation < 40)) {// this means on the side lines and thus different position
            qDebug() << "testing";
            player2->setGeometry(xLocations[playerLocation]+75,yLocations[playerLocation],75,75);
        }
        else {
            player2->setGeometry(xLocations[playerLocation],yLocations[playerLocation]+75,75,75);
        }
        ui->label_42->setText("Player 2 Exp: " + QString::number(player2Exp));
    }

}
void MainWindow::handleDice() {
    dice1 = qrand() % (6) + 1;
    dice2 = qrand() % (6) + 1;
    dice1Label->setText("Roll: "+ QString::number(dice1));
    dice2Label->setText("Roll: "+ QString::number(dice2));
    totalRoll = dice1 + dice2;

}

void MainWindow::handlePurchase(){  // subtract from Exp when making purchase. currentPlayer uses 0 for player1 and 1 for player 2 etc.
    int currentLocation = currentGame->players[currentPlayer]->location;
    if(currentPlayer == 0){
        int pricez = currentGame->tiles[currentLocation]->price;
        currentGame->tiles[currentLocation]->currentRent = currentGame->tiles[currentLocation]->initialRent; // set the rent, so no longer free
        int rentz = currentGame->tiles[currentLocation]->currentRent;
        currentGame->tiles[currentLocation]->owner = 0;
        currentGame->players[currentPlayer]->money -= pricez;
        player1Exp = currentGame->players[currentPlayer]->money;
        ui->label_41->setText("Player 1 Exp: " + QString::number(player1Exp));
        infoBox->setText("You caught Pokemon at Location: " + QString::number(currentLocation) + " who gains " + QString::number(rentz)
                         + " EXP per battle ");

        currentGame->players[currentPlayer]->takeTurn(currentGame->tiles[currentLocation]);
        QVector<int> ownedProperty = currentGame->players[currentPlayer]->properties;
        QString properties = " ";  // grab all the properties and display it
        for (int i = 0; i < ownedProperty.size(); i++){
            properties += QString::number(ownedProperty[i]) + ", ";
        }
        p1Properties->setText("Player 1 owned Locations: " + properties);
        p1prop++;
        properties1->setText("Player 1 Total Prop: " + QString::number(p1prop));
    }
    else if(currentPlayer == 1){
        int pricez = currentGame->tiles[currentLocation]->price;
        currentGame->tiles[currentLocation]->currentRent = currentGame->tiles[currentLocation]->initialRent; // set the rent, so no longer free
        int rentz = currentGame->tiles[currentLocation]->currentRent;
        currentGame->tiles[currentLocation]->owner = 1;
        currentGame->players[currentPlayer]->money -= pricez;
        player2Exp = currentGame->players[currentPlayer]->money;
        ui->label_42->setText("Player 2 Exp: " + QString::number(player2Exp));
        infoBox->setText("You caught Pokemon at Location: " + QString::number(currentLocation) + " who gains " + QString::number(rentz)
                         + " EXP per battle ");
        currentGame->players[currentPlayer]->takeTurn(currentGame->tiles[currentLocation]);
        QVector<int> ownedProperty = currentGame->players[currentPlayer]->properties;
        QString properties = " ";  // grab all the properties and display it
        for (int i = 0; i < ownedProperty.size(); i++){
            properties += QString::number(ownedProperty[i]) + ", ";
        }
        p2Properties->setText("Player 2 owned Locations: " + properties);
        p2prop++;
        properties2->setText("Player 2 Total Prop: " + QString::number(p2prop));
    }
}


void MainWindow::handleMove() {
    qDebug() << "Moving" ;
    int currentLocation;
    if (currentPlayer == 0){ // update the location
        int player1Location = currentGame->players[currentPlayer]->location;
        player1Location = (player1Location + totalRoll)%40;
        currentLocation = player1Location;
        currentGame->players[currentPlayer]->location = currentLocation;
        player1->setGeometry(xLocations[currentLocation],yLocations[currentLocation],75,75);
    }
    else if (currentPlayer == 1){
        int player2Location = currentGame->players[currentPlayer]->location;
        player2Location = (player2Location + totalRoll)%40;
        currentLocation = player2Location;
        currentGame->players[currentPlayer]->location = currentLocation;
        if ((10 < player2Location && player2Location < 20) || (30 < player2Location && player2Location < 40)) {// this means on the side lines and thus different position
            qDebug() << "testing";
            player2->setGeometry(xLocations[player2Location]+75,yLocations[player2Location],75,75);
        }
        else {
            player2->setGeometry(xLocations[player2Location],yLocations[player2Location]+75,75,75);
        }
    }

    location->setText("At location " + QString::number(currentLocation)); // display current location
    int availability = currentGame->tiles[currentLocation]->owner;
    int price = currentGame->tiles[currentLocation]->currentRent;
    if (availability == -1)
        avail->setText("Catchable");
    else {
        avail->setText("Not Catchable");
    }
    rentPrice->setText("Current Rent: " + QString::number(price));
    if(currentLocation == 0) {
        // this is Go
        currentGame->players[currentPlayer]->money += 200;
        expTotal += 200;
    }
    else if (currentLocation == 2 || currentLocation == 17 || currentLocation == 33) {
        // this is Community Chest
        p1challenges++; // display total amount of adventures so far
        challenge1->setText("Total Adventures: " + QString::number(p1challenges));
        int roll = Community::runCard(currentGame->players[currentPlayer]); // this will update the player
        if (roll){
            infoBox->setText("Snorlax blocking path, move back 3 spaces");
          //  currentGame->players[currentPlayer]->location -= 3;
            displayGif(0);
        } else {
            infoBox->setText("Discovered rarecandy. Exp + 200");
           // currentGame->players[currentPlayer]->money += 200;
            expTotal += 200;
            displayGif(1);
        }
    }
    else if (currentLocation == 7 || currentLocation == 22 || currentLocation == 36){
        // this is Chance
        p2challenges++;
        challenge2->setText("Total Challenges: " + QString::number(p2challenges));
        int roll = Community::runCard(currentGame->players[currentPlayer]); // this will update the player
        if (roll){
            infoBox->setText("Victorious Battle! +100 EXP");
          //  currentGame->players[currentPlayer]->money += 100;
            expTotal += 100;
            displayGif(2);
        } else {
            infoBox->setText("LOST Battle to Red. -200 EXP");
          //  currentGame->players[currentPlayer]->money -= 200;
            expTotal -= 200;
            displayGif(3);
        }
    }
    else if (currentLocation == 10){
        // this is Just Visiting or At Jail
        infoBox->setText("You see a dizzy pikachu... Nothing happens");
    }
    else if (currentLocation == 20){
        // this is free parking
        currentGame->players[currentPlayer]->money +=300;
        displayGif(4);
        infoBox->setText("Pokemon Daycare. + 300 exp");
        expTotal += 300;
    }
    else if (currentLocation == 30){
        // this is go to Jail
        currentGame->players[currentPlayer]->location = 10;
        displayGif(5);
        infoBox->setText("Knocked out by Officer Jenny! Dizzied!");
    }
    else if (currentLocation == 4){
        // this is income Tax
        infoBox->setText("Team Rocket attacks! -10% exp");
        currentGame->players[currentPlayer]->money = currentGame->players[currentPlayer]->money - .1*currentGame->players[currentPlayer]->money;
    }
    else if (currentLocation == 38){
        // this is luxury tax
        infoBox->setText("Team Rocket from Above! -100 EXP");
        currentGame->players[currentPlayer]->money -= 100;
    }
    else{
        int currentOwner = currentGame->tiles[currentLocation]->owner;
        int currentRent = currentGame->tiles[currentLocation]->currentRent;
        if ((currentPlayer != currentOwner) && (currentOwner != -1)) {// this means its owned by someone
            currentGame->players[currentPlayer]->money -= currentRent; // give rent to the owner
            currentGame->players[currentOwner]->money += currentRent;

            player1Exp = currentGame->players[0]->money; // update the UI
            ui->label_41->setText("Player 1 Exp: " + QString::number(player1Exp));

            player2Exp = currentGame->players[1]->money;
            ui->label_42->setText("Player 2 Exp: " + QString::number(player2Exp));

            infoBox->setText("Player " + QString::number(currentPlayer+1) + " loses " + QString::number(currentRent) + " EXP to Player: " + QString::number(currentOwner + 1));
        } else if (currentOwner == -1) { // this means it can be purchased
            if(ai[currentPlayer]) {
                square* currentSquare = currentGame->tiles[currentLocation];
                int buy = currentGame->players[currentPlayer]->takeTurn(currentSquare);
                if (buy) {
                    int pricez = currentGame->tiles[currentLocation]->price;
                    currentGame->tiles[currentLocation]->currentRent = currentGame->tiles[currentLocation]->initialRent; // set the rent, so no longer free
                    int rentz = currentGame->tiles[currentLocation]->currentRent;
                    currentGame->tiles[currentLocation]->owner = currentPlayer;
                    currentGame->players[currentPlayer]->money -= pricez;
                    if (currentPlayer == 0) {
                        player1Exp = currentGame->players[currentPlayer]->money;
                        ui->label_41->setText("Player 1 Exp: " + QString::number(player1Exp));
                    } else{
                        player2Exp = currentGame->players[currentPlayer]->money;
                        ui->label_42->setText("Player 2 Exp: " + QString::number(player2Exp));
                    }
                    infoBox->setText("AI caught Pokemon at Location: " + QString::number(currentLocation) + " who gains " + QString::number(rentz)
                                     + " EXP per battle ");
                    QVector<int> ownedProperty = currentGame->players[currentPlayer]->properties;
                    for (int i = 0 ; i < ownedProperty.size(); i++){
                        qDebug()<<ownedProperty[i];
                    }
                }
                else {
                    infoBox->setText("AI: " + QString::number(currentPlayer) + " decides to not buy location: " +  QString::number(currentLocation));

                }
            } else {
                int propertyPrice = currentGame->tiles[currentLocation]->price;
                infoBox->setText("Would you like to catch this Pokemon? You will lose "
                                 + QString::number(propertyPrice) + " EXP ");
            }
        }
    }
    if (currentPlayer == 0) {
        player1Exp = currentGame->players[currentPlayer]->money;
        ui->label_41->setText("Player 1 Exp: " + QString::number(player1Exp));
    } else{
        player2Exp = currentGame->players[currentPlayer]->money;
        ui->label_42->setText("Player 2 Exp: " + QString::number(player2Exp));
    }
    totalExp->setText(" Total EXP in Game (including owned Locations: " + QString::number(expTotal));
}
void MainWindow::handleTurn(){
    qDebug() << "next Turn";
    currentPlayer = (currentPlayer+1)%numberPlayers;
    ui->currentPlayer->setText("Current Player: " + QString::number(currentPlayer+1));
    if (ai[currentPlayer]) { // ai takes turn differently
        ui->currentPlayer->setText("Current AI: " + QString::number(currentPlayer+1));
        Sleep(2000);
        handleDice();
        Sleep(2000);
        handleMove();
        handleTurn(); // go to next person's turn
    }
    //currentGame->nextTurn();
}

void MainWindow::loadImages() {

}

void MainWindow::displayGif(int roll) {
    continueButton->show();
    gifLabel->setGeometry(240, 215,600,300);
    gifLabel ->setMovie(gifs[roll]);
    gifLabel->show();
    gifs[roll]->start();
}

void MainWindow::setLabels() {
    pictureLabels[0]->setText("GO");
    pictureLabels[1]->setText("Bulbasaur 60");
    pictureLabels[2]->setText("ADVENTURE");
    pictureLabels[3]->setText("Venasaur 60");
    pictureLabels[4]->setText("Lose 10% EXP");
    pictureLabels[5]->setText("Pikachus 200");
    pictureLabels[6]->setText("Charmander 100");
    pictureLabels[7]->setText("CHALLENGE");
    pictureLabels[8]->setText("Charmeleon 100");
    pictureLabels[9]->setText("Charizard 120");
    pictureLabels[10]->setText("DIZZIED");
    pictureLabels[11]->setText("Squirtle 140");
    pictureLabels[12]->setText("Pokeflutes 150");
    pictureLabels[13]->setText("Wartortle 140");
    pictureLabels[14]->setText("Blastoise 160");
    pictureLabels[15]->setText("Pikachus 200");
    pictureLabels[16]->setText("Eevee 180");
    pictureLabels[17]->setText("ADVENTURE");
    pictureLabels[18]->setText("Ninetails 180");
    pictureLabels[19]->setText("BlueFox 200");
    pictureLabels[20]->setText("Loose EXP");
    pictureLabels[21]->setText("Abra 220");
    pictureLabels[22]->setText("CHALLENGE");
    pictureLabels[23]->setText("Kadabra 220");
    pictureLabels[24]->setText("Alakazam 240");
    pictureLabels[25]->setText("Pikachus 200");
    pictureLabels[26]->setText("Machop 260");
    pictureLabels[27]->setText("Machoke 260");
    pictureLabels[28]->setText("Pokeflutes 150");
    pictureLabels[29]->setText("Machamp 280");
    pictureLabels[30]->setText("GO TO DIZZIED");
    pictureLabels[31]->setText("Articuno 300");
    pictureLabels[32]->setText("Zapdos 300");
    pictureLabels[33]->setText("ADVENTURE");
    pictureLabels[34]->setText("Moltres 320");
    pictureLabels[35]->setText("Pikachus 200");
    pictureLabels[36]->setText("Challenge");
    pictureLabels[37]->setText("Mew 350");
    pictureLabels[38]->setText("Lose 100 EXP");
    pictureLabels[39]->setText("MewTwo 400");

    for (int i = 0; i < 40; i++){
        pictureLabels[i]->setGeometry(xLocations[i], yLocations[i],70,10);
    }
}
// here we find the locations each square
void MainWindow::setLocations() {
    xLocations[0] = 825;
    yLocations[0] = 825;
    for (int i = 1; i < 10; i++) {
        xLocations[i] = xLocations[i-1] - 75;
        yLocations[i] = 825;
    }
    xLocations[10] = xLocations[9] - 155;
    yLocations[10] = 825;

    for (int i =11; i < 20; i++){
        xLocations[i] = xLocations[i-1];
        yLocations[i] = yLocations[i-1] - 75;
    }
    xLocations[20] = xLocations[19];
    yLocations[20] = yLocations[19] - 150;

    xLocations[21] = xLocations[20] + 150;
    yLocations[21] = yLocations[20];
    for (int i = 22; i< 31; i++){
        xLocations[i] = xLocations[i-1] + 75;
        yLocations[i] = yLocations[i-1];
    }
    xLocations[31] = xLocations[30];
    yLocations[31] = yLocations[30] + 150;

    for (int i = 32; i < 40; i++){
        xLocations[i] = xLocations[i-1];
        yLocations[i] = yLocations[i-1]+ 75;
    }


}

// Load images here and set them to proper locations. However, some jpg formats won't load so I had to use some png
// also, places like 0, 10, 20, 30 are bigger, so I manually do those as well
// some pictures are 150x75 and others are 75x150, so two different kinds of forloops

void MainWindow::renderGame() {
    //load gifs here
    for (int i = 0; i < 4; i++){
        gifs[i] = new QMovie(":/img/pokemon/" + QString::number(i) + ".gif");
    }

    gifs[4] = new QMovie(":/gifs/pokemon/" + QString::number(20) + ".gif");
    gifs[5] = new QMovie(":/gifs/pokemon/" + QString::number(30) + ".gif");
    gifLabel = ui->movieLabel;


    // Load Player Images
//   player1 = ui->player_1;
   QPixmap goku(":/img/pokemon/goku.jpeg");
   player1->setStyleSheet(" border: 2px inset grey;");
   player1->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter | Qt::AlignBottom);
   player1->setPixmap(goku.scaled(75,75,Qt::KeepAspectRatio));;
   player1->setGeometry(xLocations[0],yLocations[0],75,75);
   player1->raise();

   //player2 = ui->player_2;
   QPixmap femaleTrainer(":/img/pokemon/femaleTrainer.jpeg");
   player2->setStyleSheet(" border: 2px inset grey;");
   player2->setPixmap(femaleTrainer.scaled(75,75,Qt::KeepAspectRatio));
   player2->setGeometry(xLocations[0],yLocations[0]+75,75,75);
   player2->raise();


   //load board
    QPixmap pix(":/img/pokemon/" + QString::number(0) +".jpg");
    pictures[0]->setStyleSheet(" border: 1px inset grey;");
    pictures[0]->setPixmap(pix.scaled(150,150,Qt::KeepAspectRatio));
    pictures[0]->setGeometry(xLocations[0], yLocations[0],150,150);

    for (int i = 1; i < 10; i++){
        QPixmap pix(":/img/pokemon/" + QString::number(i) +".jpg");
        pictures[i]->setStyleSheet(" border: 1px inset grey;");
        pictures[i]->setPixmap(pix.scaled(110,110,Qt::KeepAspectRatio));
        pictures[i]->setGeometry(xLocations[i], yLocations[i],75,150);
    }

    QPixmap pix2(":/img/pokemon/" + QString::number(2) +".png");
    pictures[2]->setStyleSheet(" border: 1px inset grey;");
    pictures[2]->setPixmap(pix2.scaled(110,110,Qt::KeepAspectRatio));
    pictures[2]->setGeometry(xLocations[2], yLocations[2],75,150);

    QPixmap pix3(":/img/pokemon/" + QString::number(10) +".jpg");
    pictures[10]->setStyleSheet(" border: 1px inset grey;");
    pictures[10]->setPixmap(pix3.scaled(150,150,Qt::KeepAspectRatio));
    pictures[10]->setGeometry(xLocations[10], yLocations[10],150,150);

    for (int i = 11; i < 20; i++){
        QPixmap pix(":/img/pokemon/" + QString::number(i) +".jpg");
        pictures[i]->setStyleSheet(" border: 1px inset grey;");
        pictures[i]->setPixmap(pix.scaled(110,110,Qt::KeepAspectRatio));
        pictures[i]->setGeometry(xLocations[i], yLocations[i],150,75);
    }

    QPixmap pix4(":/img/pokemon/" + QString::number(20) +".jpg");
    pictures[20]->setStyleSheet(" border: 1px inset grey;");
    pictures[20]->setPixmap(pix4.scaled(150,150,Qt::KeepAspectRatio));
    pictures[20]->setGeometry(xLocations[20], yLocations[20],150,150);

    for (int i = 21; i < 30; i++){
        QPixmap pix(":/img/pokemon/" + QString::number(i) +".jpg");
        pictures[i]->setStyleSheet(" border: 1px inset grey;");
        pictures[i]->setPixmap(pix.scaled(110,110,Qt::KeepAspectRatio));
        pictures[i]->setGeometry(xLocations[i], yLocations[i],75,150);
    }

    QPixmap pix5(":/img/pokemon/" + QString::number(30) +".jpg");
    pictures[30]->setStyleSheet(" border: 1px inset grey;");
    pictures[30]->setPixmap(pix5.scaled(150,150,Qt::KeepAspectRatio));
    pictures[30]->setGeometry(xLocations[30], yLocations[30],150,150);

    for (int i = 31; i < 40; i++){
        QPixmap pix(":/img/pokemon/" + QString::number(i) +".jpg");
        pictures[i]->setStyleSheet(" border: 1px inset grey;");
        pictures[i]->setPixmap(pix.scaled(110,110,Qt::KeepAspectRatio));
        pictures[i]->setGeometry(xLocations[i], yLocations[i],150,75);
    }

    QPixmap pix6(":/img/pokemon/" + QString::number(12) +".png");
    pictures[12]->setStyleSheet(" border: 1px inset grey;");
    pictures[12]->setPixmap(pix6.scaled(110,110,Qt::KeepAspectRatio));
    pictures[12]->setGeometry(xLocations[12], yLocations[12],150,75);

    QPixmap pix7(":/img/pokemon/" + QString::number(17) +".png");
    pictures[17]->setStyleSheet(" border: 1px inset grey;");
    pictures[17]->setPixmap(pix7.scaled(110,110,Qt::KeepAspectRatio));
    pictures[17]->setGeometry(xLocations[17], yLocations[17],150,75);

    QPixmap pix8(":/img/pokemon/" + QString::number(22) +".png");
    pictures[22]->setStyleSheet(" border: 1px inset grey;");
    pictures[22]->setPixmap(pix8.scaled(110,110,Qt::KeepAspectRatio));
    pictures[22]->setGeometry(xLocations[22], yLocations[22],75,150);

    QPixmap pix9(":/img/pokemon/" + QString::number(28) +".png");
    pictures[28]->setStyleSheet(" border: 1px inset grey;");
    pictures[28]->setPixmap(pix9.scaled(110,110,Qt::KeepAspectRatio));
    pictures[28]->setGeometry(xLocations[28], yLocations[28],75,150);

    QPixmap pix10(":/img/pokemon/" + QString::number(36) +".png");
    pictures[36]->setStyleSheet(" border: 1px inset grey;");
    pictures[36]->setPixmap(pix10.scaled(110,110,Qt::KeepAspectRatio));
    pictures[36]->setGeometry(xLocations[36], yLocations[36],150,75);

    QPixmap pix11(":/img/pokemon/" + QString::number(33) +".png");
    pictures[33]->setStyleSheet(" border: 1px inset grey;");
    pictures[33]->setPixmap(pix11.scaled(110,110,Qt::KeepAspectRatio));
    pictures[33]->setGeometry(xLocations[33], yLocations[33],150,75);

    QPixmap pix12(":/img/pokemon/" + QString::number(7) +".png");
    pictures[7]->setStyleSheet(" border: 1px inset grey;");
    pictures[7]->setPixmap(pix12.scaled(110,110,Qt::KeepAspectRatio));
    pictures[7]->setGeometry(xLocations[7], yLocations[7],75,150);





}
