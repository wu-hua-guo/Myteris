#include "tetriswindow.h"
#include <QApplication>
#include <stdlib.h>
#include <QTime>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TetrisWindow w;
    w.show();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    return a.exec();
}
