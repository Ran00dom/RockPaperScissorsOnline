QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += network
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gamewindow.cpp \
    lobbylist.cpp \
    main.cpp \
    menu.cpp \
    onlinemanager.cpp \
    playerbar.cpp \
    playercontroller.cpp \
    window.cpp

HEADERS += \
    gamewindow.h \
    lobbylist.h \
    menu.h \
    onlinemanager.h \
    playerbar.h \
    playercontroller.h \
    window.h

FORMS +=

TRANSLATIONS += \
    RockPaperScissorsOnline_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resurce.qrc
