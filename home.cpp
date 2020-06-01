#include "home.h"
#include "config.h"
Home::Home()
{
    m_myHome.load(MYHOME_PATH);
    m_enemyHome.load(ENEMYHOME_PATH);
    isalive=true;
    hp=8;
    m_HomeRect.setWidth(m_myHome.width());
    m_HomeRect.setHeight(m_myHome.height());
    bomb_timer=0;
}

void Home::setPosition(int x, int y)
{
    m_X=x;
    m_Y=y;
    m_HomeRect.moveTo(m_X,m_Y);
}


