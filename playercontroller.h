#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "qapplication.h"
#include "window.h"
#include <QObject>
#include <QUdpSocket>
#include <QMap>
#include <QHostAddress>
#include <QByteArray>
#include <QtNetwork>

class PlayerController : public QApplication
{
    Q_OBJECT
    Window *mainWindow;
    QUdpSocket *socket;
    QMap<QString, QHostAddress> serverLists;
    bool Host = 0;
    bool GameStart = 0;

public:
    explicit PlayerController(int &argc, char **argv);
    void findPlayers();
    void readMessage();
    void startLobby() {Host = 1;};
    void leaveLobby();

signals:
    void updateServerList(QString addres, QString name);
    void startFindPlayers();
};

#endif // PLAYERCONTROLLER_H
