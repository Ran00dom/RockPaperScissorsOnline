#include "window.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *LayoutMain = new QHBoxLayout(this);
    gameWindow = new GameWindow(this);
    lobbyMenu = new LobbyList(this);
    mainMenu = new Menu(this);

    gameWindow->setVisible(false);

    LayoutMain->addWidget(lobbyMenu);
    LayoutMain->addWidget(gameWindow);
    LayoutMain->addWidget(mainMenu);
}

Window::~Window()
{

}

void Window::openGameWindow(bool open){
    if (open){
        gameWindow->setVisible(true);
        lobbyMenu->setVisible(false);
    }
    else{
        gameWindow->setVisible(false);
        lobbyMenu->setVisible(true);
    }
}
