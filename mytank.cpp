#include "mytank.h"
#include "config.h"
#include<QPainter>
MyTank::MyTank()
{
    //加载玩家图片
    m_mytank1.load(MY_TANK1_PATH);
    m_mytank2.load(MY_TANK2_PATH);
    m_mytank3.load(MY_TANK3_PATH);
    m_mytank4.load(MY_TANK4_PATH);
    //初始化坦克坐标
    m_mytankX=(GAME_WIDTH-m_mytank1.width())*0.3;
    m_mytankY=GAME_HEIGHT-m_mytank1.height();

    //初始化矩形边框
    m_mytankRect.setWidth(m_mytank1.width());
    m_mytankRect.setHeight(m_mytank1.height());
    m_mytankRect.moveTo(m_mytankX,m_mytankY);

    ismove=false;//初始化不动

    isalive=true;
    lives=5;
    mytank_second=0;

}

void MyTank::shoot(int diraim)
{
    if(isalive==false)return;
    //发射子弹
    for(int i=0;i<BULLET_NUM;i++)//寻找空闲子弹
    {
        if(m_bullets[i].m_free==true)//子弹空闲则发射
        {
            m_bullets[i].m_free=false;//设置子弹为使用中
            m_bullets[i].bulletDir=diraim;//设置子弹方向为坦克方向

            //设置子弹发射位置
            m_bullets[i].m_X=m_mytankX+m_mytankRect.width()*0.5-5;
            m_bullets[i].m_Y=m_mytankY+m_mytankRect.height()*0.5-3;

            break;

        }
    }
}

void MyTank::setTankPosition(int x, int y)
{
    m_mytankX=x;
    m_mytankY=y;
    m_mytankRect.moveTo(m_mytankX,m_mytankY);
}

void MyTank::setdir(int dirs)
{
    dir=dirs;
}

void MyTank::initMytankPosition()
{
    m_mytankX=(GAME_WIDTH-m_mytank1.width())*0.3;
    m_mytankY=GAME_HEIGHT-m_mytank1.height();
    m_mytankRect.moveTo(m_mytankX,m_mytankY);
}




