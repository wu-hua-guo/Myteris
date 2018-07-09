#include "tetriswindow.h"
#include "tetrixboard.h"
#include <QLabel>
#include <QLCDNumber>
//#include "tetrixboard.h"

TetrisWindow::TetrisWindow(QWidget *parent)
    : QWidget(parent)
{

    board = new TetrixBoard;
    //! [0]

    nextPieceLabel = new QLabel;
    nextPieceLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    nextPieceLabel->setAlignment(Qt::AlignCenter);
    board->setNextPieceLabel(nextPieceLabel);

    // !init LCDNumber
    scoreLcd = new QLCDNumber(5);
    scoreLcd->setSegmentStyle(QLCDNumber::Filled);

    levelLcd = new QLCDNumber(2);
    levelLcd->setSegmentStyle(QLCDNumber::Filled);
    linesLcd = new QLCDNumber(2);
    linesLcd->setSegmentStyle(QLCDNumber::Filled);
    // !init button
    startButton = new QPushButton(tr("&开始"));
    startButton->setFocusPolicy(Qt::NoFocus);
    quitButton = new QPushButton(tr("&退出"));
    quitButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton(tr("&暂停"));
    pauseButton->setFocusPolicy(Qt::NoFocus);

    connect(startButton,SIGNAL(clicked(bool)),board,SLOT(start()));
    connect(quitButton,SIGNAL(clicked(bool)),qApp,SLOT(quit()));
    connect(pauseButton,SIGNAL(clicked(bool)),board,SLOT(pause()));

    connect(board, SIGNAL(scoreChanged(int)), scoreLcd, SLOT(display(int)));
    connect(board, SIGNAL(levelChanged(int)), levelLcd, SLOT(display(int)));
    connect(board, SIGNAL(linesRemovedChanged(int)),linesLcd, SLOT(display(int)));
    //! [5]

    QGridLayout *layout= new QGridLayout;
    layout->addWidget(board,0,1,6,1);
    layout->addWidget(nextPieceLabel,1,0);
    // ! add label
    layout->addWidget(createLabel(tr("下一个方块")),0,0);
    layout->addWidget(createLabel(tr("等级")),2,0);
    layout->addWidget(createLabel(tr("分数")),0,2);
    layout->addWidget(createLabel(tr("消除行数")),2,2);
//    layout->setColumnStretch(0,2);
//    layout->setColumnStretch(1,8);
//    layout->setColumnStretch(2,2);
    // ! add lcd
    layout->addWidget(scoreLcd,1,2);
    layout->addWidget(levelLcd,3,0);
    layout->addWidget(linesLcd,3,2);
    // ! add button
    layout->addWidget(startButton,4,0);
    layout->addWidget(quitButton,4,2);
    layout->addWidget(pauseButton,5,2);

    this->setLayout(layout);
    this->setWindowTitle(tr("俄罗斯方块游戏"));
    //this->resize(400,370);

    board->resize(board->BoardWidth*15+2,board->BoardHeight*15+2);

    qDebug()<<"1";
    qDebug()<<this->size();

}

TetrisWindow::~TetrisWindow()
{

}
// 大小改变之后，固定大小
void TetrisWindow::resizeEvent(QResizeEvent *)
{
    setFixedSize(this->size());
}

QLabel *TetrisWindow::createLabel(const QString &text)
{
    QLabel *lbl = new QLabel(text);
    lbl->setAlignment(Qt::AlignHCenter|Qt::AlignBottom);
    return lbl;
}
