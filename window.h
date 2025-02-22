#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QImage>
#include "menu.h"
#include "lobbylist.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Window;
}

QT_END_NAMESPACE

class Window : public QWidget
{
    Q_OBJECT

    QImage *timer;
    QImage *first_player;
    QImage *second_player;

public:
    LobbyList *lobbyMenu;
    Menu *mainMenu;
    explicit Window(QWidget *parent = nullptr);
    ~Window();

};
#endif // WINDOW_H
