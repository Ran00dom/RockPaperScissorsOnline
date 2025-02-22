#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPushButton>
#include "playerbar.h"
#include <QVBoxLayout>

class Menu : public QWidget
{
    Q_OBJECT
    PlayerBar *PlayerInfo;

public:
    QPushButton *Play;
    QPushButton *Leave;
    QPushButton *Settings;
    QPushButton *Find;
    explicit Menu(QWidget *parent = nullptr);
    void pressConnect();
    void pressLeave();
signals:
};

#endif // MENU_H
