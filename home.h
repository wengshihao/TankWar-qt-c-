#ifndef HOME_H
#define HOME_H

#include "config.h"
#include<QPixmap>
#include<QRect>
class Home
{
public:
    Home();
    void setPosition(int x,int y);
public:
    bool isalive;
    int kind;
    int hp;
    QPixmap m_myHome;
    QPixmap m_enemyHome;
    int m_X;
    int m_Y;
    QRect m_HomeRect;
    int bomb_timer;//爆炸计时器
};

#endif // HOME_H
