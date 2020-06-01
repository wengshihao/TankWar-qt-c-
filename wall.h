#ifndef WALL_H
#define WALL_H

#include <config.h>
#include<QPixmap>
#include<QRect>
class Wall
{
public:
    Wall();
    void setWallPosition(int x,int y);
public:
    QPixmap m_Wall;

    //墙壁坐标
    int m_WallX;
    int m_WallY;

    QRect m_WallRect;//墙壁边框

    bool m_free;//是否空闲
};

#endif // WALL_H
