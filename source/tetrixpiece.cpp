#include "tetrixpiece.h"

TetrixPiece::TetrixPiece()
{

}

void TetrixPiece::setShape(TetrixShape shape)
{
    static int coordsTable[8][4][2] {
        { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },//
        { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },//ZShape
        { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },//SShape
        { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },//LineShape
        { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },//TShape
        { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },//SquareShape
        { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },//LShape
        { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } }//MirroredLShape
    };


}
