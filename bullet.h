#ifndef BULLET_H
#define BULLET_H
#include "config.h"
#include<QPixmap>
class Bullet
{
public:
    Bullet();

    //更新子弹坐标
    void setBulletPosition();

public:
    //子弹图片
    QPixmap m_BulletUP;
    QPixmap m_BulletDown;
    QPixmap m_BulletLeft;
    QPixmap m_BulletRight;

    //子弹方向
    int bulletDir;

    //子弹坐标
    int m_X;
    int m_Y;

    //子弹速度
    int m_speed;

    //子弹是否在使用中
    bool m_free;

    //子弹边框
    QRect m_RectUP;
    //QRect m_RectDown;
    //QRect m_RectLeft;
    //QRect m_RectRight;
};

#endif // BULLET_H
