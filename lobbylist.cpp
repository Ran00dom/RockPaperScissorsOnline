#include "lobbylist.h"

LobbyList::LobbyList(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *LayoutMain = new QVBoxLayout(this);
    list = new QListWidget(this);
    LayoutMain->addWidget(list);
}

LobbyList::~LobbyList()
{

}

void LobbyList::addLobby(QString address, QString name)
{
    QListWidgetItem *item = new QListWidgetItem();
    item->setText(name + " | " + address);
    item->setData(1, QVariant(address));
    list->addItem(item);
}

void LobbyList::clearLobbyList()
{
    list->clear();
}




