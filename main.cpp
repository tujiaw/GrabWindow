#include "mainwindow.h"
#include "grabwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GrabWidget grabWidget;
    grabWidget.show();
//    MainWindow w;
//    w.show();

    return a.exec();
}
