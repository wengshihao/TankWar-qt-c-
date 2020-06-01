#ifndef ENEMYTANK_H
#define ENEMYTANK_H
#include<QPixmap>
#include<bullet.h>

class EnemyTank
{
public:
    EnemyTank();

    //更新敌人位置
    void setEnemyPosition(int x, int y);
    void setEnemyDir(int newdir);

    void shoot(int diraim);//敌人发射子弹
public:
    //敌人图片
    QPixmap m_enemyUP;
    QPixmap m_enemyDown;
    QPixmap m_enemyLeft;
    QPixmap m_enemyRight;

    //敌人坐标
    int m_enemyX;
    int m_enemyY;

    //敌人边框
    QRect m_Rect;

    //是否空闲
    bool m_free;

    //每步移动距离
    int step=1;

    //移动方向
    int dir=1;

    //拐弯时间戳
    int m_Enemy_Second;

    //发射时间戳
    int m_Enemy_Shot_Second;

    //弹夹
    Bullet m_enemyBullets[BULLET_NUM];

};

#endif // ENEMYTANK_H
