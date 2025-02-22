#include "playerbar.h"
#include <QDebug>
#include <QDir>


PlayerBar::PlayerBar(QWidget *parent)
    : QWidget{parent}
{
    playerImage = new QPixmap();
    name = new QLabel("Player1", this);

    image = new QLabel(this);
    icon = new QIcon();
    QHBoxLayout *layoutMain = new QHBoxLayout(this);
    if (!playerImage->load(":/resource/img/Image/BaseImagePlayer.png"))
        playerImage->load(":/resource/img/Image/BaseImagePlayer.png");

    image->setPixmap(playerImage->scaled(50, 50, Qt::KeepAspectRatio));
    layoutMain->addWidget(image);
    layoutMain->addWidget(name);
}

PlayerBar::~PlayerBar()
{
    delete playerImage;
}
