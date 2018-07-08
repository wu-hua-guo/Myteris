#ifndef TETRISWINDOW_H
#define TETRISWINDOW_H

#include <QMainWindow>

class TetrisWindow : public QMainWindow
{
    Q_OBJECT

public:
    TetrisWindow(QWidget *parent = 0);
    ~TetrisWindow();
};

#endif // TETRISWINDOW_H
