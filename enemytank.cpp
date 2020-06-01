#include "enemytank.h"
#include "config.h"
EnemyTank::EnemyTank()
{
    //敌人图片
    m_enemyUP.load(ENEMY_TANK_UP_PATH);
    m_enemyDown.load(ENEMY_TANK_DOWN_PATH);
    m_enemyLeft.load(ENEMY_TANK_LEFT_PATH);
    m_enemyRight.load(ENEMY_TANK_RIGHT_PATH);

    //初始化位置
    m_enemyX=0;
    m_enemyY=0;

    //矩形框
    m_Rect.setWidth(m_enemyUP.width());
    m_Rect.setHeight(m_enemyUP.height());
    m_Rect.moveTo(m_enemyX,m_enemyY);

    m_free=1;//设为空闲

    m_Enemy_Second=0;

    m_Enemy_Shot_Second=0;

}

void EnemyTank::setEnemyPosition(int x, int y)
{
    if(m_free)return;//空闲
    m_enemyX=x;
    m_enemyY=y;
    m_Rect.moveTo(m_enemyX,m_enemyY);
}

void EnemyTank::setEnemyDir(int newdir)
{
    dir=newdir;
}

void EnemyTank::shoot(int diraim)
{
    //发射子弹
    for(int i=0;i<BULLET_NUM;i++)//寻找空闲子弹
    {
        if(m_enemyBullets[i].m_free==true)//子弹空闲则发射
        {
            m_enemyBullets[i].m_free=false;//设置子弹为使用中
            m_enemyBullets[i].bulletDir=diraim;//设置子弹方向为坦克方向

            //设置子弹发射位置
            m_enemyBullets[i].m_X=m_enemyX+m_Rect.width()*0.5-5;
            m_enemyBullets[i].m_Y=m_enemyY+m_Rect.height()*0.5-3;

            break;

        }
    }
}
