#include <QApplication>
#include <QTextCodec>

#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);


    MainWidget w;
    w.show();

    return a.exec();
}
