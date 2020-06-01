#ifndef STONE_H
#define STONE_H

#include <config.h>
#include<QPixmap>
#include<QRect>
class Stone
{
public:
    Stone();
    void setStonePosition(int x,int y);
public:
    QPixmap m_stone;

    //墙壁坐标
    int m_X;
    int m_Y;

    QRect m_Rect;//墙壁边框

    bool m_free;//是否空闲
};

#endif // STONE_H
