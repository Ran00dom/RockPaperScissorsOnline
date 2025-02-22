#include "gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QWidget{parent}
{
    winLable = new QLabel("Игра началась", this);
    Rock = new QPushButton("Камень", this);
    Paper = new QPushButton("Бумага", this);
    Scissors = new QPushButton("Ножницы", this);

    rightReady = new QLabel("Не готов", this);
    leftReady = new QLabel("Не готов", this);

    itemLeft = new QLabel(this);
    itemRight = new QLabel(this);

    imgRight = new QPixmap();
    imgLeft = new QPixmap();

    imgRight->load(":/resource/img/Image/BaseImagePlayer.png");
    imgLeft->load(":/resource/img/Image/BaseImagePlayer.png");

    itemLeft->setPixmap(*imgLeft);
    itemRight->setPixmap(*imgRight);

    QVBoxLayout *mainBox = new QVBoxLayout(this);

    QHBoxLayout *buttonBox = new QHBoxLayout();
    buttonBox->addWidget(Rock);
    buttonBox->addWidget(Paper);
    buttonBox->addWidget(Scissors);

    QHBoxLayout *comandBox = new QHBoxLayout();

    QVBoxLayout *commandLeft = new QVBoxLayout();
    commandLeft->addWidget(itemLeft);
    commandLeft->addWidget(leftReady);

    QVBoxLayout *commandRight = new QVBoxLayout();
    commandRight->addWidget(itemRight);
    commandRight->addWidget(rightReady);

    comandBox->addLayout(commandLeft);
    comandBox->addLayout(commandRight);

    mainBox->addWidget(winLable);
    mainBox->addLayout(comandBox);
    mainBox->addLayout(buttonBox);

    connect(Rock, &QPushButton::clicked, this, &GameWindow::_selectRock);
    connect(Paper, &QPushButton::clicked, this, &GameWindow::_selectPaper);
    connect(Scissors, &QPushButton::clicked, this, &GameWindow::_selectScissors);

    connect(Rock, &QPushButton::clicked, this, &GameWindow::selectItem);
    connect(Paper, &QPushButton::clicked, this, &GameWindow::selectItem);
    connect(Scissors, &QPushButton::clicked, this, &GameWindow::selectItem);
}

void GameWindow::selectItem(){
    Rock->setVisible(false);
    Paper->setVisible(false);
    Scissors->setVisible(false);
}

void GameWindow::resetGameWindow(){
    winLable->setText("Игра началась");
    Rock->setVisible(true);
    Paper->setVisible(true);
    Scissors->setVisible(true);

    leftReady->setText("Не готов");
    rightReady->setText("Не готов");

    imgRight->load(":/resource/img/Image/BaseImagePlayer.png");
    imgLeft->load(":/resource/img/Image/BaseImagePlayer.png");

    itemLeft->setPixmap(*imgLeft);
    itemRight->setPixmap(*imgRight);
}

void GameWindow::showResult(QString Item, int win){
    if (Item == "Rock") {
        imgLeft->load(":/resource/img/Image/Rock.png");
    }
    if (Item == "Paper") {
        imgLeft->load(":/resource/img/Image/Paper.png");
    }
    if (Item == "Scissors") {
        imgLeft->load(":/resource/img/Image/Scissors.png");
    }
    itemLeft->setPixmap(*imgLeft);
    rightReady->setText("Готов");
    if (win == -1)
        winLable->setText("Вы проиграли!");
    else if (win == 1)
        winLable->setText("Вы победили!");
    else
        winLable->setText("Ничья!");
    QThread::sleep(3);
    resetGameWindow();
}
