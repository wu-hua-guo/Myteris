#ifndef TETRIXBOARD_H
#define TETRIXBOARD_H
#include <QBasicTimer>
#include <QFrame>
#include <QPointer>

class TetrixBoard : public QFrame
{
    Q_OBJECT
public:
    TetrixBoard(QWidget *parent = 0);

signals:

public slots:
    void start();
    void pause();
};

#endif // TETRIXBOARD_H
