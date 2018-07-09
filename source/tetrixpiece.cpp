#include <QtCore>

#include <stdlib.h>

#include "tetrixpiece.h"
#include <QDebug>
//! [0]
void TetrixPiece::setRandomShape()
{
    setShape(TetrixShape(qrand() % 7 + 1));
}
//! [0]

//! [1]
void TetrixPiece::setShape(TetrixShape shape)
{
    static const int coordsTable[8][4][2] = {
        { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },//
        { { 0, 1 },  { 1, 1 },   { 1, 2 },  { 2, 2 } },//ZShape
        { { 0, 2 },  { 1, 2 },   { 1, 1 },   { 2, 1 } },//SShape
        { { 1, 0 },  { 1, 1 },   { 1, 2 },   { 1, 3 } },//LineShape
        { { 0, 1 },  { 1, 1 },   { 1, 2 },   { 2, 1 } },//TShape
        { { 1, 1 },   { 1, 2 },   { 2, 1 },   { 2, 2 } },//SquareShape
        { { 1, 0 }, { 1, 1 },  { 1, 2 },   { 2, 2 } },//LShape
        { { 1, 2 },  { 2, 0 },  { 2, 1 },   { 2, 2 } }//MirroredLShape
    };

    for (int i = 0; i < 4 ; i++) {
        for (int j = 0; j < 2; ++j)
            coords[i][j] = coordsTable[shape][i][j];
    }
    pieceShape = shape;
//! [1] //! [2]
}
//! [2]

//! [3]
int TetrixPiece::minX() const
{
    int min = coords[0][0];
    for (int i = 1; i < 4; ++i)
        min = qMin(min, coords[i][0]);
    return min;
}

int TetrixPiece::maxX() const
//! [3] //! [4]
{
    int max = coords[0][0];
    for (int i = 1; i < 4; ++i)
        max = qMax(max, coords[i][0]);
    return max;
}
//! [4]

//! [5]
int TetrixPiece::minY() const
{
    int min = coords[0][1];
    for (int i = 1; i < 4; ++i)
        min = qMin(min, coords[i][1]);
    return min;
}

int TetrixPiece::maxY() const
//! [5] //! [6]
{
    int max = coords[0][1];
    for (int i = 1; i < 4; ++i)
        max = qMax(max, coords[i][1]);
    return max;
}
//! [6]

//! [7]逆时针
TetrixPiece TetrixPiece::rotatedLeft() const
{
    //qDebug()<<pieceShape<<"Left";
    if (pieceShape == SquareShape)
        return *this;

    TetrixPiece result;
    result.pieceShape = pieceShape;
    for (int i = 0; i < 4; ++i) {
        //x'=(x-x0)sin@+(y-y0)cos@+y0
        //y'=(x-x0)cos@+(y-y0)sin@+x0
        //x'=y
        //y'=3-x
        result.setX(i, y(i));
        result.setY(i, 3-x(i));
    }
//! [7]
    return result;
}

//! [9]
TetrixPiece TetrixPiece::rotatedRight() const
{
    qDebug()<<pieceShape<<"Right";
    if (pieceShape == SquareShape)
        return *this;

    TetrixPiece result;
    result.pieceShape = pieceShape;
    for (int i = 0; i < 4; ++i) {
        //x'=(x-x0)sin@+(y-y0)cos@+y0
        //y'=(x-x0)cos@+(y-y0)sin@+x0
        //x'=3-y
        //y'=x
        result.setX(i, 3-y(i));
        result.setY(i, x(i));
    }
//! [9]
    return result;
}
