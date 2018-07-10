#include <QtWidgets>

#include "tetrixboard.h"
class QDebug;
//! [0]
TetrixBoard::TetrixBoard(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    isStarted = false;
    isPaused = false;
    grid = false;
    clearBoard();

    nextPiece.setRandomShape();
}
//! [0]

//! [1]
void TetrixBoard::setNextPieceLabel(QLabel *label)
{
    nextPieceLabel = label;
}
//! [1]

//! [2]
QSize TetrixBoard::sizeHint() const
{
    QSize size=QSize(BoardWidth * 15 + frameWidth() * 2,
                     BoardHeight * 15 + frameWidth() * 2);
    //qDebug()<<"sizeHint:"<<size;
    return size;
}

QSize TetrixBoard::minimumSizeHint() const
//! [2] //! [3]
{
    return QSize(BoardWidth * 5 + frameWidth() * 2,
                 BoardHeight * 5 + frameWidth() * 2);
}
//! [3]

//! [4]
void TetrixBoard::start()
{
    if (isPaused)
        return;

    isStarted = true;
    isWaitingAfterLine = false;
    numLinesRemoved = 0;
    numPiecesDropped = 0;
    score = 0;
    level = 1;
    clearBoard();

    emit linesRemovedChanged(numLinesRemoved);
    emit scoreChanged(score);
    emit levelChanged(level);

    newPiece();
    timer.start(timeoutTime(), this);
}
//! [4]

//! [5]
void TetrixBoard::pause()
{
    if (!isStarted)
        return;

    isPaused = !isPaused;
    if (isPaused) {
        timer.stop();
    } else {
        timer.start(timeoutTime(), this);
    }
    update();
    //! [5] //! [6]
}

void TetrixBoard::isGrid()
{
    grid = !grid;
    update();
}
//! [6]

//! [7]
void TetrixBoard::paintEvent(QPaintEvent *event)
{
//    static int i=0;
    //qDebug()<<tr("paintEvent %1").arg(i++);
    QFrame::paintEvent(event);

    QPainter painter(this);
    QRect rect = contentsRect();
//! [7]

//    if (isPaused) {
//        painter.drawText(rect, Qt::AlignCenter, tr("Pause"));
//        return;
//    }

//! [8]
    int boardTop = rect.bottom() - BoardHeight*squareHeight();

    for (int y = 0; y < BoardHeight; ++y) {
        for (int x = 0; x < BoardWidth; ++x) {
            TetrixShape shape = shapeAt(x, y);
            if (shape != NoShape)
                drawSquare(painter, rect.left() + x * squareWidth(),
                           boardTop + y * squareHeight(), shape);
        }
//! [8] //! [9]
    }

//! [9]

//! [10]
    if (curPiece.shape() != NoShape) {
        for (int i = 0; i < 4; ++i) {
            int x = curX + curPiece.x(i);
            int y = curY + curPiece.y(i);
            drawSquare(painter, rect.left() + x * squareWidth(),
                       boardTop + y * squareHeight(),
                       curPiece.shape());
        }
//! [10] //! [11]
    }
    if(grid)
    {
        drawBoardGrid(painter,rect);
    }
//! [11] //! [12]
}



//! [12]

//! [13]
void TetrixBoard::keyPressEvent(QKeyEvent *event)
{

    if (!isStarted || isPaused || curPiece.shape() == NoShape) {
        QFrame::keyPressEvent(event);
        return;
    }
//! [13]

//! [14]
    switch (event->key()) {
    case Qt::Key_Left:
        tryMove(curPiece, curX - 1, curY);
        break;
    case Qt::Key_A:
        tryMove(curPiece, curX - 1, curY);
        break;

    case Qt::Key_Right:
        tryMove(curPiece, curX + 1, curY);
        break;
    case Qt::Key_D:
        tryMove(curPiece, curX + 1, curY);
        break;

    case Qt::Key_Down:
        tryMove(curPiece.rotatedRight(), curX, curY);
        break;
    case Qt::Key_S:
        oneLineDown();
        break;

    case Qt::Key_Up:
        tryMove(curPiece.rotatedLeft(), curX, curY);
        break;
    case Qt::Key_W:
        tryMove(curPiece.rotatedLeft(), curX, curY);
        break;

    case Qt::Key_Space:
        dropDown();
        break;

    default:
        QFrame::keyPressEvent(event);
    }
//! [14]
}

//! [15]
void TetrixBoard::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {
        if (isWaitingAfterLine) {
            isWaitingAfterLine = false;
            newPiece();
            timer.start(timeoutTime(), this);
        } else {
            oneLineDown();
        }
    } else {
        QFrame::timerEvent(event);
//! [15] //! [16]
    }
//! [16] //! [17]
}
//! [17]

//! [18]
void TetrixBoard::clearBoard()
{
    for (int i = 0; i < BoardHeight * BoardWidth; ++i)
        board[i] = NoShape;
}
//! [18]

//! [19]
void TetrixBoard::dropDown()
{
    int dropHeight = 0;
    int newY = curY;
    while (newY < BoardHeight) {
        if (!tryMove(curPiece, curX, newY + 1))
            break;
        ++newY;
        ++dropHeight;
    }
    pieceDropped(dropHeight);
//! [19] //! [20]
}
//! [20]

//! [21]
void TetrixBoard::oneLineDown()
{
    if (!tryMove(curPiece, curX, curY + 1))
        pieceDropped(0);
}
//! [21]

//! [22]
void TetrixBoard::pieceDropped(int dropHeight)
{
    for (int i = 0; i < 4; ++i) {
        int x = curX + curPiece.x(i);
        int y = curY + curPiece.y(i);
        shapeAt(x, y) = curPiece.shape();
    }

    ++numPiecesDropped;
    if (numPiecesDropped % 25 == 0) {
        ++level;
        timer.start(timeoutTime(), this);
        emit levelChanged(level);
    }

    score += dropHeight + 7;
    emit scoreChanged(score);
    removeFullLines();

    if (!isWaitingAfterLine)
        newPiece();
//! [22] //! [23]
}
//! [23]

//! [24]
void TetrixBoard::removeFullLines()
{
    int numFullLines = 0;

    for (int y = 0; y < BoardHeight; ++y) {
        bool lineIsFull = true;

        for (int x = 0; x < BoardWidth; ++x) {
            if (shapeAt(x, y) == NoShape) {
                lineIsFull = false;
                break;
            }
        }

        if (lineIsFull) {
//! [24] //! [25]
            ++numFullLines;
            for (int k = y; k > 0; --k) {
                for (int x = 0; x < BoardWidth; ++x)
                    shapeAt(x, k) = shapeAt(x, k - 1);
            }
//! [25] //! [26]
            for (int x = 0; x < BoardWidth; ++x)
                shapeAt(x, 0) = NoShape;
        }
//! [26] //! [27]
    }
//! [27]

//! [28]
    if (numFullLines > 0) {
        numLinesRemoved += numFullLines;
        score += 10 * numFullLines;
        emit linesRemovedChanged(numLinesRemoved);
        emit scoreChanged(score);

        timer.start(500, this);
        isWaitingAfterLine = true;
        curPiece.setShape(NoShape);
        update();
    }
//! [28] //! [29]
}
//! [29]

//! [30]
void TetrixBoard::newPiece()
{
    curPiece = nextPiece;
    curX = BoardWidth / 2 -2;
    curY = -curPiece.minY();
    qDebug()<<curY;

    if (!tryMove(curPiece, curX, curY)) {
        curPiece.setShape(NoShape);
        timer.stop();
        isStarted = false;
        return;
    }
    nextPiece.setRandomShape();
    showNextPiece();
//! [30] //! [31]
}
//! [31]

//! [32]
void TetrixBoard::showNextPiece()
{
    if (!nextPieceLabel)
        return;

    int dx = nextPiece.maxX() - nextPiece.minX() + 1;
    int dy = nextPiece.maxY() - nextPiece.minY() + 1;

    QPixmap pixmap(dx * squareWidth(), dy * squareHeight());
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), nextPieceLabel->palette().background());

    for (int i = 0; i < 4; ++i) {
        int x = nextPiece.x(i) - nextPiece.minX();
        int y = nextPiece.y(i) - nextPiece.minY();
        drawSquare(painter, x * squareWidth(), y * squareHeight(),
                   nextPiece.shape());
    }
    nextPieceLabel->setPixmap(pixmap);
//! [32] //! [33]
}
//! [33]

//! [34]
bool TetrixBoard::tryMove(const TetrixPiece &newPiece, int newX, int newY)
{
    for (int i = 0; i < 4; ++i) {
        int x = newX + newPiece.x(i);
        int y = newY + newPiece.y(i);
        //qDebug()<<x<<y;
        if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
            return false;
        if (shapeAt(x, y) != NoShape)
            return false;
    }

//! [34]

//! [35]
    curPiece = newPiece;
    curX = newX;
    curY = newY;
    update();
    return true;
}
//! [35]

//! [36]
void TetrixBoard::drawSquare(QPainter &painter, int x, int y, TetrixShape shape)
{
    static const QRgb colorTable[8] = {
        0x000000, 0xCC6666, 0x66CC66, 0x6666CC,
        0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00
    };

    QColor color = colorTable[int(shape)];

    // !1 绘制一个边框宽度为1的矩形
    painter.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2,
                     color);

    painter.setPen(color.light());
    painter.drawLine(x, y + squareHeight() - 1, x, y);
    painter.drawLine(x, y, x + squareWidth() - 1, y);

    painter.setPen(color.dark());
    painter.drawLine(x + 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + squareHeight() - 1);
    painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + 1);
    // !1
}
//
void TetrixBoard::drawBoardGrid(QPainter &painter, QRect &rect)
{
    static QColor color=QColor(100,100,100).light();
    int boardTop = rect.bottom() - BoardHeight*squareHeight();
    painter.setPen(color);
    for(int x=0;x<=BoardWidth;++x)
    {
        painter.drawLine(rect.left()+x*squareHeight(), rect.top(),
                         rect.left()+x*squareHeight(), rect.height());
    }
    for (int y = 0; y <= BoardHeight; ++y) {
        painter.drawLine(rect.left(), boardTop + y * squareHeight(),
                         rect.right(), boardTop + y * squareHeight());
    }
}
//! [36]
