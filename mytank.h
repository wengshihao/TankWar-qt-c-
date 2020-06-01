#ifndef MYTANK_H
#define MYTANK_H

#include<QPixmap>
#include<QRect>
#include "bullet.h"

class MyTank
{
public:
    MyTank();

    //发射炮弹
    void shoot(int diraim);

    //设置坦克位置
    void setTankPosition(int x,int y);

    //移动方向
    void setdir(int dirs);

    //初始化坦克坐标，用于复活
    void initMytankPosition();
public:
    //坦克图片
    QPixmap m_mytank1;
    QPixmap m_mytank2;
    QPixmap m_mytank3;
    QPixmap m_mytank4;
    //坦克坐标
    int m_mytankX;
    int m_mytankY;
    int lives;

    //坦克边框
    QRect m_mytankRect;

    //每步移动距离
    int step=1;

    //移动方向
    int dir=1;

    //是否移动
    bool ismove;

    //弹夹
    Bullet m_bullets[BULLET_NUM];

    //玩家坦克时间戳
    int mytank_second;


    //是否存活
    bool isalive;
};

#endif // MYTANK_H
