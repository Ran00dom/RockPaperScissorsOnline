#include "window.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *LayoutMain = new QHBoxLayout(this);
    //QVBoxLayout *LayoutMenu = new QVBoxLayout();

    lobbyMenu = new LobbyList(this);
    mainMenu = new Menu(this);

    LayoutMain->addWidget(lobbyMenu);
    LayoutMain->addWidget(mainMenu);

    //LayoutMain->addLayout(LayoutMenu);
}

Window::~Window()
{

}
