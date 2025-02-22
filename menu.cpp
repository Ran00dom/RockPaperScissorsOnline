#include "menu.h"

Menu::Menu(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *LayoutMain = new QVBoxLayout(this);
    Play = new QPushButton("Create",this);
    Leave = new QPushButton("Leave",this);
    Settings = new QPushButton("Settings",this);
    PlayerInfo = new PlayerBar(this);
    Find = new QPushButton("Find", this);

    LayoutMain->addWidget(Play);
    Leave->setVisible(false);
    LayoutMain->addWidget(Leave);
    LayoutMain->addWidget(Find);
    LayoutMain->addWidget(Settings);
    LayoutMain->addWidget(PlayerInfo);
    LayoutMain->setStretch(0, 5);

    connect(Play, &QPushButton::clicked, this, &Menu::pressConnect);
    connect(Leave, &QPushButton::clicked, this, &Menu::pressLeave);
}

void Menu::pressConnect()
{
    Play->setVisible(false);
    Leave->setVisible(true);
    Find->setVisible(false);
}
void Menu::pressLeave()
{
    Leave->setVisible(false);
    Play->setVisible(true);
    Find->setVisible(true);
}
