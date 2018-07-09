#ifndef TETRISWINDOW_H
#define TETRISWINDOW_H
#include <QFrame>
#include <QtWidgets>
#include <QWidget>
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>
#include "tetrixboard.h"
//QT_BEGIN_NAMESPACE
//class QLCDNumber;
//class QLabel;
//class QPushButton;
//QT_END_NAMESPACE





class TetrisWindow : public QWidget
{
    Q_OBJECT

public:
    TetrisWindow(QWidget *parent = 0);
    ~TetrisWindow();
public slots:
     void resizeEvent(QResizeEvent *);//界面大小改变事件
private:
    QLabel *createLabel(const QString &text);

    TetrixBoard *board;
    QLabel *nextPieceLabel;
    QLCDNumber *scoreLcd;
    QLCDNumber *levelLcd;
    QLCDNumber *linesLcd;
    QPushButton *startButton;
    QPushButton *quitButton;
    QPushButton *pauseButton;

};

#endif // TETRISWINDOW_H
