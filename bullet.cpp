#include "bullet.h"
#include "config.h"
Bullet::Bullet()
{
    //加载子弹图片
    m_BulletUP.load(BULLETUP_PATH);
    m_BulletDown.load(BULLETDOWN_PATH);
    m_BulletLeft.load(BULLETLEFT_PATH);
    m_BulletRight.load(BULLETRIGHT_PATH);

    //子弹坐标
    m_X=0;
    m_Y=0;

    //子弹状态
    m_free=true;

    //子弹速度
    m_speed=BULLET_SPEED;

    //子弹边框
    m_RectUP.setWidth(m_BulletUP.width());
    m_RectUP.setHeight(m_BulletUP.height());
    m_RectUP.moveTo(m_X,m_Y);

    /*
    m_RectDown.setWidth(m_BulletDown.width());
    m_RectDown.setHeight(m_BulletDown.height());
    m_RectDown.moveTo(m_X,m_Y);

    m_RectLeft.setWidth(m_BulletLeft.width());
    m_RectLeft.setHeight(m_BulletLeft.height());
    m_RectLeft.moveTo(m_X,m_Y);

    m_RectRight.setWidth(m_BulletRight.width());
    m_RectRight.setHeight(m_BulletRight.height());
    m_RectRight.moveTo(m_X,m_Y);
    */
}

void Bullet::setBulletPosition()
{
    if(m_free)return;//子弹空闲

    //子弹移动
    if(bulletDir==1)
    {
        m_Y-=m_speed;
        m_RectUP.moveTo(m_X,m_Y);
    }
    if(bulletDir==2)
    {
        m_Y+=m_speed;
        m_RectUP.moveTo(m_X,m_Y);
    }
    if(bulletDir==3)
    {
        m_X-=m_speed;
        m_RectUP.moveTo(m_X,m_Y);
    }
    if(bulletDir==4)
    {
        m_X+=m_speed;
        m_RectUP.moveTo(m_X,m_Y);
    }

    //子弹位置超出窗口则重置为空闲子弹
    if(m_Y<0||m_Y>GAME_HEIGHT)m_free=true;
    if(m_X<0||m_X>GAME_WIDTH)m_free=true;
}
