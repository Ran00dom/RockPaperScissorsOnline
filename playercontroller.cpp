#include "playercontroller.h"
#include <QDebug>

#define PORT int(755)

PlayerController::PlayerController(int &argc, char **argv)
    : QApplication{argc, argv}
{
    mainWindow = new Window();
    mainWindow->show();
    socket = new QUdpSocket(this);
    qDebug() << "Listen socket " << socket->bind(PORT);
    findPlayers();

    connect(socket, &QUdpSocket::readyRead, this, &PlayerController::readMessage);

    connect(mainWindow->lobbyMenu->list, &QListWidget::doubleClicked, this, &PlayerController::connectToHost);
    connect(mainWindow->mainMenu->Find, &QPushButton::clicked, this, &PlayerController::findPlayers);
    connect(this, &PlayerController::updateServerList, mainWindow->lobbyMenu, &LobbyList::addLobby);
    connect(mainWindow->mainMenu->Play, &QPushButton::clicked, this, &PlayerController::startLobby);
    connect(mainWindow->mainMenu->Leave, &QPushButton::clicked, this, &PlayerController::leaveLobby);
    connect(this, &PlayerController::startFindPlayers, mainWindow->lobbyMenu, &LobbyList::clearLobbyList);

    connect(mainWindow->gameWindow, &GameWindow::selectRock, this, &PlayerController::selectRock);
    connect(mainWindow->gameWindow, &GameWindow::selectPaper, this, &PlayerController::selectPaper);
    connect(mainWindow->gameWindow, &GameWindow::selectScissors, this, &PlayerController::selectScissors);
}

void PlayerController::findPlayers()
{
    emit startFindPlayers();
    QByteArray dgram;
    QDataStream out(&dgram, QIODevice::WriteOnly);
    out << QString("LOBBY_FIND");
    socket->writeDatagram(dgram.data(), dgram.size(), QHostAddress::Broadcast, PORT);
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
        socket->writeDatagram(dgram.data(), dgram.size(), *address, PORT);
    }

    if (message == "ACTIVE_LOBBY"){
        QString name;
        in >> name;
        qDebug() << "Name " + name;
        emit updateServerList(address->toString(), name);
    }

    if (message == "CONNECT" && Host && !GameStart) {
        if (socket->state() == QAbstractSocket::ConnectedState) {
            qDebug() << "Already connected to a server.";
        }
        else{
            socket->connectToHost(*address, PORT);
            if (!socket->waitForConnected(1)) {
                qDebug() << "Connection timed out.";
            }
            else{
                this->address = address;
                GameStart = 1;
                mainWindow->openGameWindow(true);
            }
        }
    }

    if (message == "DISCONNECT" && GameStart)
        leaveLobby();

    if (message == "READY") {
        readyEnemy = true;
        if (ready)
            itemMessage();
    }

    if (message == "ITEM") {
        QString Item;
        in >> Item;
        if (Item == TypeSelect)
            mainWindow->gameWindow->showResult(Item, 0);
        if ((Item == "Rock" && TypeSelect == "Paper") || (Item == "Paper" && TypeSelect == "Scissors") || (Item == "Scissors" && TypeSelect == "Rock"))
            mainWindow->gameWindow->showResult(Item, 1);
        if ((Item == "Paper" && TypeSelect == "Rock") || (Item == "Scissors" && TypeSelect == "Paper") || (Item == "Rock" && TypeSelect == "Scissors"))
            mainWindow->gameWindow->showResult(Item, -1);
    }
}

void PlayerController::leaveLobby()
{
    Host = 0;
    GameStart = 0;
    QByteArray dgram("DISCONNECT");
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(dgram);
    } else {
        qDebug() << "Socket is not connected!";
    }
    socket->disconnectFromHost();
    socket->bind(PORT);
    mainWindow->openGameWindow(false);
}

bool PlayerController::connectToHost(const QModelIndex& index)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        qDebug() << "Already connected to a server.";
        return false;
    }
    qDebug() << QHostAddress(index.data(1).toString());
    qDebug() << index.data(1).toString();
    socket->connectToHost(QHostAddress(index.data(1).toString()), PORT);
    if (!socket->waitForConnected(1)) {
        qDebug() << "Connection timed out.";
        return false;
    }

    connect(socket, &QUdpSocket::errorOccurred, this, [this](QAbstractSocket::SocketError error) {
        qDebug() << "Connection error: " << socket->errorString();
        emit connectionFailed(socket->errorString());
    });

    GameStart = 1;

    QByteArray dgram;
    QDataStream out(&dgram, QIODevice::WriteOnly);
    out << QString("CONNECT");
    out << QString("UserName");
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(dgram);
    } else {
        qDebug() << "Socket is not connected!";
    }
    mainWindow->openGameWindow(true);
    return true;
}

void PlayerController::readyMessage()
{
    QByteArray dgram("READY");
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->writeDatagram(dgram.data(), dgram.size(), *address, PORT);
    } else {
        qDebug() << "Socket is not connected!";
    }

    if (readyEnemy)
        itemMessage();
}

void PlayerController::itemMessage()
{
    QByteArray dgram;
    QDataStream out(&dgram, QIODevice::WriteOnly);
    out << QString("ITEM");
    out << TypeSelect;
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(dgram);
    } else {
        qDebug() << "Socket is not connected!";
    }
}
