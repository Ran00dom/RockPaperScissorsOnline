#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QThread>

class GameWindow : public QWidget
{
    Q_OBJECT
    QLabel *rightReady, *leftReady;
    QLabel *itemLeft, *itemRight;
    QPixmap *imgLeft, *imgRight;
    QPushButton *Rock, *Paper, *Scissors;
    QLabel *winLable;
public:


    explicit GameWindow(QWidget *parent = nullptr);
    void resetGameWindow();
    void selectItem();
    void showResult(QString Item, int win);

    void _selectRock() {imgRight->load(":/resource/img/Image/Rock.png"); itemRight->setPixmap(*imgRight); rightReady->setText("Готов"); emit selectRock();};
    void _selectPaper() {imgRight->load(":/resource/img/Image/Paper.png"); itemRight->setPixmap(*imgRight); rightReady->setText("Готов"); emit selectPaper();};
    void _selectScissors() {imgRight->load(":/resource/img/Image/Scissors.png"); itemRight->setPixmap(*imgRight); rightReady->setText("Готов"); emit selectScissors();};

signals:
    void selectRock();
    void selectPaper();
    void selectScissors();
};

#endif // GAMEWINDOW_H
