#ifndef PLAYERBAR_H
#define PLAYERBAR_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QHBoxLayout>
#include <QIcon>

class PlayerBar : public QWidget
{
    Q_OBJECT

    QPixmap *playerImage;
    QLabel *image;
    QLabel *name;
    QIcon *icon;

public:
    explicit PlayerBar(QWidget *parent = nullptr);
    ~PlayerBar();
signals:
};

#endif // PLAYERBAR_H
