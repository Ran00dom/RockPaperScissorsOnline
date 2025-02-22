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
    QHostAddress *address;


    bool Host = 0;
    bool GameStart = 0;
    QString TypeSelect;
    QString TypeEmeny;
    bool ready = false;
    bool readyEnemy = false;


public:
    explicit PlayerController(int &argc, char **argv);
    void findPlayers();
    void readMessage();
    void startLobby() {Host = 1;};
    void leaveLobby();
    bool connectToHost(const QModelIndex&);
    QString getUserName();

    void selectRock() {ready = true; TypeSelect = "Rock"; readyMessage();};
    void selectPaper() {ready = true; TypeSelect = "Paper"; readyMessage();};
    void selectScissors() {ready = true; TypeSelect = "Scissors"; readyMessage();};

    void readyMessage();
    void itemMessage();
signals:
    void connectionFailed(QString);
    void updateServerList(QString address, QString name);
    void startFindPlayers();
};

#endif // PLAYERCONTROLLER_H
