#ifndef ONLINEMANAGER_H
#define ONLINEMANAGER_H

#include <QObject>

class OnlineManager : public QObject
{
    Q_OBJECT
public:
    explicit OnlineManager(QObject *parent = nullptr);

signals:
};

#endif // ONLINEMANAGER_H
