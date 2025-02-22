#ifndef LOBBYLIST_H
#define LOBBYLIST_H

#include "qhostaddress.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QMap>
#include <QList>
#include <QListWidget>

class LobbyList: public QWidget
{
    Q_OBJECT

public:

    QListWidget *list;
    explicit LobbyList(QWidget *parent = nullptr);
    ~LobbyList();

    void addLobby(QString address, QString name);
    void clearLobbyList();
signals:
    void selectLobby(QString);
};

#endif // LOBBYLIST_H
