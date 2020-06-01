#include "stone.h"

Stone::Stone()
{
    m_stone.load(STONE_PATH);//加载墙壁图片

    //初始化墙壁位置
    m_X=0;
    m_Y=0;

    m_Rect.setWidth(m_stone.width());
    m_Rect.setHeight(m_stone.height());
    m_Rect.moveTo(m_X,m_Y);

    m_free=true;
}

void Stone::setStonePosition(int x, int y)
{
    m_X=x;
    m_Y=y;
    m_Rect.moveTo(m_X,m_Y);
}
