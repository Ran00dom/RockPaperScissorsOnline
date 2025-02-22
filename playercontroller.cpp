#include "playercontroller.h"
#include <QDebug>
PlayerController::PlayerController(int &argc, char **argv)
    : QApplication{argc, argv}
{
    mainWindow = new Window();
    mainWindow->show();
    socket = new QUdpSocket(this);
    qDebug() << "Listen socket " << socket->bind(755);
    findPlayers();

    connect(socket, &QUdpSocket::readyRead, this, &PlayerController::readMessage);
    //connect(mainWindow->lobbyMenu->list, &QListWidget::doubleClicked, this, &PlayerController::findPlayers);
    connect(mainWindow->mainMenu->Find, &QPushButton::clicked, this, &PlayerController::findPlayers);
    connect(this, &PlayerController::updateServerList, mainWindow->lobbyMenu, &LobbyList::addLobby);
    connect(mainWindow->mainMenu->Play, &QPushButton::clicked, this, &PlayerController::startLobby);
    connect(mainWindow->mainMenu->Leave, &QPushButton::clicked, this, &PlayerController::leaveLobby);
    connect(this, &PlayerController::startFindPlayers, mainWindow->lobbyMenu, &LobbyList::clearLobbyList);
}

void PlayerController::findPlayers()
{
    serverLists.clear();
    emit startFindPlayers();
    QByteArray dgram;
    QDataStream out(&dgram, QIODevice::WriteOnly);
    out << QString("LOBBY_FIND");
    socket->writeDatagram(dgram.data(), dgram.size(), QHostAddress::Broadcast, 755);
}


void PlayerController::readMessage()
{

    QByteArray datagram;
    datagram.resize(socket->pendingDatagramSize());
    QHostAddress *address = new QHostAddress();
    socket->readDatagram(datagram.data(), datagram.size(), address);
    QString message;

    qDebug() << *address;
    if (*address == socket->localAddress())
        qDebug() << "Self! ";
    else
        qDebug() << "Message! ";

    QDataStream in(&datagram, QIODevice::ReadOnly);
    in >> message;
    qDebug() << message;
    if (message == "LOBBY_FIND" && Host && !GameStart){
        qDebug() << "Message return!";
        qDebug() << QHostAddress(socket->AnyIPProtocol);
        QByteArray dgram;
        QDataStream out(&dgram, QIODevice::WriteOnly);
        out << QString("ACTIVE_LOBBY");
        out << QString("UserName");
        out << socket->IPv4Protocol;
        socket->writeDatagram(dgram.data(), dgram.size(), *address, 755);
    }

    if (message == "ACTIVE_LOBBY"){
        QString name;
        in >> name;
        qDebug() << "Name " + name;
        serverLists[name] = *address;
        emit updateServerList(address->toString(), name);
    }

    if (message == "CONNECT") {

    }
}

void PlayerController::leaveLobby()
{
    Host = 0;
    GameStart = 0;
    socket->disconnectFromHost();
    socket->bind(755);
}
