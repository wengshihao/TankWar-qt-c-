#include "wall.h"

Wall::Wall()
{
    m_Wall.load(WALL_PATH);//加载墙壁图片

    //初始化墙壁位置
    m_WallX=0;
    m_WallY=0;

    m_WallRect.setWidth(m_Wall.width());
    m_WallRect.setHeight(m_Wall.height());
    m_WallRect.moveTo(m_WallX,m_WallY);

    m_free=true;

}

void Wall::setWallPosition(int x, int y)
{
    if(m_free)return;
    m_WallX=x;
    m_WallY=y;
    m_WallRect.moveTo(m_WallX,m_WallY);
}
