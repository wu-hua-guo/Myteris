#ifndef TETRIXPIECE_H
#define TETRIXPIECE_H
#include <vector>
/**
* @brief         枚举方块形状
* @author        zqw
* @dateTime      2018-07-08  22:15:51
*/
enum TetrixShape{NoShape, ZShape, SShape, LineShape, TShape, SquareShape,
                 LShape, MirroredLShape };
class TetrixPiece
{
public:
    using doubleInt=int[4][2];
    TetrixPiece();
    void setShape(TetrixShape shape);
private:
    TetrixShape pieceShape;
    int coords[4][2];
};

#endif // TETRIXPIECE_H
