#include "window.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <playercontroller.h>

int main(int argc, char *argv[])
{
    PlayerController a(argc, argv);
    /*
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "RockPaperScissorsOnline_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    Window w;
    w.show();
    */
    return a.exec();
}
