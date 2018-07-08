#include "tetrixboard.h"
#include <QDebug>
TetrixBoard::TetrixBoard(QWidget *parent)
    : QFrame(parent)
{

}
void TetrixBoard::start()
{
    qDebug()<<"board start";
}

void TetrixBoard::pause()
{
    qDebug()<<"board pause";
}
